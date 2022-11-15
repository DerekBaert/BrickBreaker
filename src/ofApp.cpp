#include "ofApp.h"
#include "Paddle.h"

//--------------------------------------------------------------

// Paddle bounce mirrors bricks, still gets stuck however.
// Extras: Music 

// Font source: https://www.fontspace.com/pixeloid-font-f69232
// Centered True Type Font: https://github.com/armadillu/ofxCenteredTrueTypeFont/blob/master/src/ofxCenteredTrueTypeFont.h
// Hit, game over and winSound sounds: https://mixkit.co/free-sound-effects/game/ (no option to link individually)

void ofApp::setup()
{
	titleFont.load("pixel2.ttf", 75);
	titleFont.setLetterSpacing(1.5);
	gameFont.load("pixel2.ttf",20);

	// Calculating starting point for brick grid, and what 1/5 of the screen is for later calculations.
	brickStart = ofGetHeight() / 10;
	fifthOfScreen = brickStart / 2;

	// Setting up the variables for creating the paddle, and the speed of the paddle as well
	paddleSize = { 20,100 };
	Coordinates paddlePosition{ static_cast<float>((ofGetWidth() / 2) - (paddleSize.width / 2)), static_cast<float>(ofGetHeight() - 50) };
	float paddleSpeed = 10;

	// Sound effect players
	hitSound.load("bounce.wav");
	winSound.load("complete.wav");
	gameOverSound.load("game_over.wav");

	// Setting up the variables for creating the ball
	float ballSize{ 10 };
	Coordinates ballPosition{ paddlePosition.x + (paddleSize.width / 2) - (ballSize / 2),(paddlePosition.y - ballSize)-1 };

	ball = { ballSize,ballPosition};

	paddle = { paddleSize, paddlePosition, paddleSpeed };

	// Calculating the buffer (space between each brick) and calculating the width of the brick including buffer
	buffer = ofGetWidth() / 400;
	brickWidth = (ofGetWidth()  / 14) - buffer;
	RectangleSize brickSize{ static_cast<float>(ofGetHeight() / 50), brickWidth };

	// Loop through and add bricks to vector, setting color based on the iteration of the inner loop to figure out which row it will be in
	for(float x = buffer; x < ofGetWidth(); x += brickWidth + buffer)
	{
		float y = brickStart;
		for(int i = 1; i < 9; i++)
		{			
			Brick brick;

			switch (i)
			{
			case 1:
			case 2:
				brick = {{brickSize}, {x, y}, ofColor(255,0,0), 7};
				break;
			case 3:
			case 4:
				brick = { {brickSize}, {x, y}, ofColor(255,165,0),5 };
				break;
			case 5:
			case 6:
				brick = { {brickSize}, {x, y}, ofColor(0,255,0),3 };
				break;
			case 7:
			case 8:
				brick = { {brickSize}, {x, y}, ofColor(255,255,0),1 };
				break;
			default:
				break;
			}

			bricks.push_back(brick);
			y += fifthOfScreen;
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw()
{
	ofFill();
	ofBackground(0);
	ofSetColor(255);

	if(!gameStart)
	{
		gameFont.drawString("Points: " + std::to_string(points), 10, fifthOfScreen);
		gameFont.drawString("Lives: " + std::to_string(lives), ofGetWidth() - 150, fifthOfScreen);

		for (auto brick : bricks)
		{
			brick.draw();
		}

		paddle.draw();
		ball.draw();

		if (paused)
		{
			if (gameOver)
			{				
				gameFont.drawStringCentered("Game over", ofGetWidth() / 2, ofGetHeight() / 2);
				gameFont.drawStringCentered("Press Space to restart.", ofGetWidth() / 2, ofGetHeight() / 2 + gameFont.getLineHeight());
			}
			else if (gameWon)
			{				
				gameFont.drawStringCentered("You Won!", ofGetWidth() / 2, ofGetHeight() / 2);
				gameFont.drawStringCentered("Press Space to play again.", ofGetWidth() / 2, ofGetHeight() / 2 + gameFont.getLineHeight());
			}
			else
			{
				gameFont.drawStringCentered("Paused", ofGetWidth() / 2, ofGetHeight() / 2);
			}
		}
	}
	else
	{
		titleFont.drawStringCentered("Brick Breaker", ofGetWidth() / 2, brickStart * 2);
		gameFont.drawStringCentered("Controls:", ofGetWidth() / 2, ofGetHeight() * 0.65);
		gameFont.drawStringCentered("Move Paddle: <- -> keys, or move mouse", ofGetWidth() / 2, ofGetHeight() * 0.65 + gameFont.getLineHeight());
		gameFont.drawStringCentered("Press Spacebar to Pause game", ofGetWidth() / 2, ofGetHeight() * 0.65 + gameFont.getLineHeight()* 2);
		gameFont.drawStringCentered("Press Enter to start Normal mode.", ofGetWidth() / 2, ofGetHeight() * 0.65 + gameFont.getLineHeight() * 3.5);
		gameFont.drawStringCentered("Press 'E' to start Easy mode.", ofGetWidth() / 2, ofGetHeight() * 0.65 + gameFont.getLineHeight() * 4.5);
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	
	ball.hitSide();

	ofRectangle ballRect = ball.getRect();

	if(paddle.hit(ball.getRect()))
	{
		hitSound.play();
		if (paddle.sideHit(ballRect))
		{
			ball.reverseX();
		}

		// If the brick registers the top or bottom as being hitSound, the ball reverse it's trajectory on the Y axis.
		if (paddle.topHit(ballRect))
		{
			ball.reverseY();
		}
	}
	
	for(auto &brick :bricks)
	{
		// Checking if brick is not destroyed already and the ball is intersecting with it
		if(!brick.destroyed() && brick.getRect().intersects(ballRect))
		{
			// If the brick registers the side as being hitSound, the ball reverse it's trajectory on the X axis.
			if (brick.sideHit(ballRect))
			{
				ball.reverseX();
			}

			// If the brick registers the top or bottom as being hitSound, the ball reverse it's trajectory on the Y axis.
			if (brick.topBottomHit(ballRect))
			{
				ball.reverseY();
			}

			// After hitSound is determined, add the brick's point value to the player's score.
			points += brick.getPoints();

			if(brick.getPoints() == 7 && !redFlag)
			{
				ball.increaseSpeed();
				redFlag = true;
			}

			if(brick.getPoints() == 5 && !orangeFlag)
			{
				ball.increaseSpeed();
				orangeFlag = true;
			}

			if(brickCounter == 4 || brickCounter == 12)
			{
				ball.increaseSpeed();
			}
			hitSound.play();
			brickCounter++;
			break;		
		}
	}

	// Checking if top of the canvas is hitSound
	if(ball.hitTop() && !easy)
	{
		paddle.shrink();
	}

	// Checking if the bottom of the canvas is hitSound
	if(ball.hitBottom() && !gameOver)
	{
		// If lives are above 0, reset the ball's location to the start and decrement the life counter
		if(lives > 0)
		{
			ball.reset();
			lives--;
		}
		// If the lives are 0 or less, set paused and game over to true.
		else
		{
			gameOverSound.play();
			paused = true;
			gameOver = true;			
		}		
	}

	// Ball only moves if game is not paused
	if(!paused)
	{
		ball.move();
	}

	// Checking if all bricks are gone, and if so make the game as complete
	if(brickCounter >= static_cast<int>(bricks.size()) && !gameWon)
	{
		gameWon = true;
		paused = true;
		winSound.play();
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if(key == OF_KEY_LEFT && !paused && !gameOver)
	{
		paddle.move(-1);
	}
	if (key == OF_KEY_RIGHT && !paused && !gameOver)
	{
		paddle.move(1);
	}


	if(key == OF_KEY_SPACE && !gameStart)
	{
		if(gameOver || gameWon)
		{
			resetGame();
		}

		paused = !paused;
	}

	if(key == OF_KEY_RETURN && gameStart)
	{
		paused = !paused;
		gameStart = !gameStart;
	}

	if((key == 'E' || key == 'e') && gameStart)
	{
		easy = true;
		lives += 7;
		gameStart = !gameStart;
		paused = !paused;
	}
}

void ofApp::resetGame()
{
	if(easy)
	{
		lives = 10;
	}
	else
	{
		lives = 3;
	}
	
	for(auto &brick : bricks)
	{
		brick.reset();
	}
	gameOver = !gameOver;
	paddle.reset();
	ball.newGame();
	points = 0;
	
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
	if(mouseX > 0 && mouseX + paddle.getWidth() < ofGetWidth() && !paused)
	{
		paddle.mouseMove(mouseX);
	}	
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
