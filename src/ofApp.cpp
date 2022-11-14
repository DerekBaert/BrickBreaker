#include "ofApp.h"
#include "Paddle.h"

//--------------------------------------------------------------

// Fix paddle bouncing behaviour
// Extras: Sound and music (1 pt each), title screen, easy mode

void ofApp::setup()
{
	redFlag = false;
	orangeFlag = false;
	brickStart = ofGetHeight() / 10;
	fifthOfScreen = brickStart / 2;
	// Setting up the variables for creating the paddle, and the speed of the paddle as well
	paddleSize = { 20,100 };
	Coordinates paddlePosition{ static_cast<float>((ofGetWidth() / 2) - (paddleSize.width / 2)), static_cast<float>(ofGetHeight() - 50) };
	float paddleSpeed = 10;

	// Setting up the variables for creating the ball
	float ballSize{ 10 };
	Coordinates ballPosition{ paddlePosition.x + (paddleSize.width / 2) - (ballSize / 2),(paddlePosition.y - ballSize)-1 };

	ball = { ballSize,ballPosition};
	paddle = { paddleSize, paddlePosition, paddleSpeed };

	buffer = ofGetWidth() / 400;
	brickWidth = (ofGetWidth()  / 14) - buffer;
	RectangleSize brickSize{ static_cast<float>(ofGetHeight() / 50), brickWidth };

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
		ofDrawBitmapString("Points: " + std::to_string(points), 10, fifthOfScreen);
		ofDrawBitmapString("Lives: " + std::to_string(lives), ofGetWidth() - 100, fifthOfScreen);

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
				ofDrawBitmapString("Game over", ofGetWidth() / 2, ofGetHeight() / 2);
				ofDrawBitmapString("Press Space to restart.", ofGetWidth() / 2, ofGetHeight() / 2 + 10);
			}
			else if (gameWon)
			{
				ofDrawBitmapString("You Won!", ofGetWidth() / 2, ofGetHeight() / 2);
				ofDrawBitmapString("Press Space to play again.", ofGetWidth() / 2, ofGetHeight() / 2 + 10);
			}
			else
			{
				ofDrawBitmapString("Paused", ofGetWidth() / 2, ofGetHeight() / 2);
			}
		}
	}
	else
	{
		ofDrawBitmapString("Use Left and Right Arrow Keys or your Mouse to move the paddle", ofGetWidth() / 2, ofGetHeight() / 2);
		ofDrawBitmapString("Press Enter to Start Normal mode, or the 'E' key for easy mode", ofGetWidth() / 2, ofGetHeight() / 2 + 10);
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	lives = easy ? 10 : 3;
	ball.hitSide();

	if(paddle.hit(ball.getRect()))
	{
		ball.reverseY();
	}

	ofRectangle ballRect = ball.getRect();
	for(auto &brick :bricks)
	{
		// Checking if brick is not destroyed already and the ball is intersecting with it
		if(!brick.destroyed() && brick.getRect().intersects(ballRect))
		{
			// If the brick registers the side as being hit, the ball reverse it's trajectory on the X axis.
			if (brick.sideHit(ballRect))
			{
				ball.reverseX();
			}

			// If the brick registers the top or bottom as being hit, the ball reverse it's trajectory on the Y axis.
			if (brick.topBottomHit(ballRect))
			{
				ball.reverseY();
			}

			// After hit is determined, add the brick's point value to the player's score.
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
			brickCounter++;
			break;		
		}
	}

	// Checking if top of the canvas is hit
	if(ball.hitTop() && !easy)
	{
		paddle.shrink();
	}

	// Checking if the bottom of the canvas is hit
	if(ball.hitBottom())
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
	if(brickCounter == static_cast<int>(bricks.size()))
	{
		gameWon = brickCounter == static_cast<int>(bricks.size());
		paused = brickCounter == static_cast<int>(bricks.size());
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


	if(key == OF_KEY_SPACE)
	{
		if(gameStart)
		{
			gameStart = !gameStart;
		}
		if(gameOver || gameWon)
		{
			resetGame();
		}

		paused = !paused;
	}

	if((key == 'E' || key == 'e') && gameStart)
	{
		easy = true;
		gameStart = !gameStart;
		paused = !paused;
	}
}

void ofApp::resetGame()
{
	lives = 3;
	for(auto &brick : bricks)
	{
		brick.reset();
	}
	gameOver = !gameOver;
	paddle.reset();
	ball.reset();
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
