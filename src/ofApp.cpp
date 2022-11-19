#include "ofApp.h"
#include "Paddle.h"

//--------------------------------------------------------------

// Pretty much done, ball still bounces weirdly on some corners

// Font source: https://www.fontspace.com/pixeloid-font-f69232
// Centered True Type Font: https://github.com/armadillu/ofxCenteredTrueTypeFont/blob/master/src/ofxCenteredTrueTypeFont.h
// Hit, game over and winSound sounds: https://mixkit.co/free-sound-effects/game/ (no option to link individually)
// Background music: https://soundimage.org/chiptunes/

void ofApp::setup()
{
	ofSetFrameRate(60);

	createButtons();

	// Loading fonts to be used in game
	titleFont.load("pixel2.ttf", 75);
	titleFont.setLetterSpacing(1.5);
	gameFont.load("pixel2.ttf", 20);

	// Creating game manager
	manager = GameManager();

	loadSounds();

	// Sets and starts title music if game has not started
	if(!manager.isGameStarted())
	{
		titleMusic.setLoop(true);
		titleMusic.play();
	}

	createBallAndPaddle();
	loadBricks();
}




//--------------------------------------------------------------
void ofApp::draw()
{
	ofFill();
	ofBackground(0);
	ofSetColor(255);

	if(manager.isGameStarted())
	{
		gamePlay();
	}
	else
	{
		titleScreen();		
	}
}

//--------------------------------------------------------------
void ofApp::update()
{
	playGameMusic();

	if (manager.isMuted())
	{
		if(backgroundMusic.isPlaying())
		{
			backgroundMusic.setVolume((0));
		}

		if(titleMusic.isPlaying())
		{
			titleMusic.setVolume(0);
		}		
	}
	else
	{
		if (backgroundMusic.isPlaying())
		{
			backgroundMusic.setVolume(1);
		}

		if (titleMusic.isPlaying())
		{
			titleMusic.setVolume(1);
		}
	}
	
	// Ball only moves if game is not paused
	if (!manager.isGamePaused())
	{
		ball.move();
		if (!manager.isMuted())
		{
			backgroundMusic.setVolume((1));
		}
	}
	else
	{
		if (!manager.isMuted())
		{
			backgroundMusic.setVolume((0.25));
		}
	}

	// Checks if the ball has hit the paddle, a brick, or one of the sides.
	ofRectangle ballRect;
	paddleHitCheck(ballRect);
	brickHitCheck(ballRect);
	borderHitCheck();	

	// Checking if all bricks are gone, and if so mark the game as complete
	if(manager.brickCount() >= static_cast<int>(bricks.size()) && !manager.isGameWon())
	{
		backgroundMusic.stop();
		manager.winGame();
		manager.pauseButton();
		if(!manager.isMuted())
		{
			winSound.play();
		}
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key)
{
	if(key == OF_KEY_LEFT && !manager.isGamePaused() && !manager.isGameOver())
	{
		paddle.move(-1);
	}
	if (key == OF_KEY_RIGHT && !manager.isGamePaused() && !manager.isGameOver())
	{
		paddle.move(1);
	}


	if(key == OF_KEY_SPACE && manager.isGameStarted())
	{
		manager.pauseButton();
	}

	if(key == 'm' || key == 'M')
	{
		manager.muteUnmute();
	}
}

void ofApp::easyMode()
{
	if (!manager.isGameStarted())
	{
		manager.easyModeOn();
		manager.pauseButton();
		manager.gameStarted();
	}
	else
	{
		manager.easyModeOn();
		resetGame();
	}
}

void ofApp::normalMode()
{
	if (!manager.isGameStarted())
	{
		manager.easyModeOff();
		manager.gameStarted();
		manager.pauseButton();
	}
	else
	{
		manager.easyModeOff();
		resetGame();
	}
}

void ofApp::resetGame()
{
	//if(manager.isEasyMode())
	//{
	//	manager.reset();
	//	manager.easyModeOn();
	//}
	//else
	//{
	//	manager.reset();
	//}
	
	for(auto &brick : bricks)
	{
		brick.reset();
	}
	paddle.reset();
	ball.newGame();
	manager.reset();
	manager.pauseButton();
	backgroundMusic.play();
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y )
{
	if(mouseX > 0 && mouseX + paddle.getWidth() < WINDOW_WIDTH && !manager.isGamePaused())
	{
		paddle.mouseMove(mouseX);
	}	
}


#pragma region Custom functions
void ofApp::createBallAndPaddle()
{
	// Setting up the variables for creating the paddle, and the speed of the paddle as well
	paddleSize = { 15,100 };
	Coordinates paddlePosition{ static_cast<float>((WINDOW_WIDTH / 2) - (paddleSize.width / 2)), static_cast<float>(WINDOW_HEIGHT - 40) };
	float paddleSpeed = 10;
	paddle = { paddleSize, paddlePosition, paddleSpeed };

	// Setting up the variables for creating the ball
	float ballSize{ 7 };
	Coordinates ballPosition{ paddlePosition.x + (paddleSize.width / 2) - (ballSize / 2),(paddlePosition.y - ballSize) - 1 };
	ball = { ballSize,ballPosition };
}

void ofApp::loadBricks()
{
	// Calculating the buffer (space between each brick) and calculating the width of the brick including buffer
	buffer = WINDOW_WIDTH / 400;
	brickWidth = (WINDOW_WIDTH / 14) - buffer;
	RectangleSize brickSize{ static_cast<float>(WINDOW_HEIGHT / 50), brickWidth };

	// Calculating starting point for brick grid, and what 1/5 of the screen is for later calculations.
	brickStart = WINDOW_HEIGHT / 10;
	fifthOfScreen = brickStart / 2;

	// Loop through and add bricks to vector, setting color based on the iteration of the inner loop to figure out which row it will be in
	for (float x = buffer; x < WINDOW_WIDTH; x += brickWidth + buffer)
	{
		float y = brickStart;
		for (int i = 1; i < 9; i++)
		{
			Brick brick;

			// Checking what color of brick to add based on the iteration
			switch (i)
			{
			case 1:
			case 2:
				brick = { {brickSize}, {x, y}, ofColor(255,0,0), 7 };
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

void ofApp::loadSounds()
{
	// Sound effect players
	hitSound.load("bounce.wav");
	winSound.load("complete.wav");
	gameOverSound.load("game_over.wav");
	backgroundMusic.load("Arcade-Puzzler.mp3");
	titleMusic.load("Arcade-Heroes.mp3");
}

void ofApp::createButtons()
{
	//  Setting up buttons and font elements for title screen	
	easyStart.addListener(this, &ofApp::easyMode);
	normalStart.addListener(this, &ofApp::normalMode);
	easyStart.setup("Easy");
	normalStart.setup("Normal");
	easyStart.loadFont("pixel2.ttf", 20);
	normalStart.loadFont("pixel2.ttf", 20);
	easyStart.setPosition(WINDOW_WIDTH / 2 - easyStart.getWidth() / 2, WINDOW_HEIGHT * 0.85);
	normalStart.setPosition(WINDOW_WIDTH / 2 + 10, WINDOW_HEIGHT * 0.85);
}

void ofApp::gamePlay()
{
	gameFont.drawString("Points: " + std::to_string(manager.getScore()), 10, fifthOfScreen);
	gameFont.drawString("Lives: " + std::to_string(manager.getLives()), WINDOW_WIDTH - 150, fifthOfScreen);

	for (auto brick : bricks)
	{
		brick.draw();
	}

	paddle.draw();
	ball.draw();

	if (manager.isGamePaused())
	{
		if (manager.isGameOver())
		{
			gameFont.drawStringCentered("Game over", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
			gameFont.drawStringCentered("Try again?", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + gameFont.getLineHeight());
			easyStart.setPosition(WINDOW_WIDTH / 2 - easyStart.getWidth() / 2, WINDOW_HEIGHT / 2 + gameFont.getLineHeight() * 3);
			normalStart.setPosition(WINDOW_WIDTH / 2 + 10, WINDOW_HEIGHT / 2 + gameFont.getLineHeight() * 3);
			easyStart.draw();
			normalStart.draw();
		}
		else if (manager.isGameWon())
		{
			gameFont.drawStringCentered("You Won!", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
			gameFont.drawStringCentered("Play again?", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2 + gameFont.getLineHeight());
			easyStart.setPosition(WINDOW_WIDTH / 2 - easyStart.getWidth() / 2, WINDOW_HEIGHT / 2 + gameFont.getLineHeight() * 3);
			normalStart.setPosition(WINDOW_WIDTH / 2 + 10, WINDOW_HEIGHT / 2 + gameFont.getLineHeight() * 3);
			easyStart.draw();
			normalStart.draw();
		}
		else
		{
			gameFont.drawStringCentered("Paused", WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
		}
	}
}

void ofApp::titleScreen()
{
	titleFont.drawStringCentered("Brick Breaker", WINDOW_WIDTH / 2, brickStart * 2);
	gameFont.drawStringCentered("Controls:", WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.65);
	gameFont.drawStringCentered("Move Paddle: <- -> keys, or move mouse", WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.65 + gameFont.getLineHeight());
	gameFont.drawStringCentered("Mute music: 'M/m' key", WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.65 + gameFont.getLineHeight() * 2);
	gameFont.drawStringCentered("Press Space bar to Pause game", WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.65 + gameFont.getLineHeight() * 3);
	easyStart.draw();
	normalStart.draw();
}

void ofApp::paddleHitCheck(ofRectangle& ballRect)
{
	ballRect = ball.getRect();

	if (paddle.hit(ballRect))
	{
		ofRectangle intersection = paddle.getIntersection(ballRect);
		ball.pushOut(intersection, paddle.getRect());

		if(!manager.isMuted())
		{
			hitSound.play();
		}

		// If the brick registers the top or bottom as being hitSound, the ball reverse it's trajectory on the Y axis.
		if (paddle.sideHit(ballRect))
		{

			ball.reverseX();
		}
		if (paddle.topHit(ballRect))
		{
			ball.reverseY();
		}

	}
}

void ofApp::brickHitCheck(ofRectangle ballRect)
{
	ballRect = ball.getRect();

	for (auto& brick : bricks)
	{
		// Checking if brick is not destroyed already and the ball is intersecting with it
		if (!brick.destroyed() && brick.getRect().intersects(ballRect))
		{
			ofRectangle intersection = brick.getRect().getIntersection(ballRect);
			// If the brick registers the top or bottom as being hitSound, the ball reverse it's trajectory on the Y axis.
			
			if (brick.topBottomHit(ballRect, intersection))
			{
				ball.reverseY();
			}
			else if (brick.sideHit(ballRect, intersection))
			{
				ball.reverseX();
			}
			// If the brick registers the side as being hitSound, the ball reverse it's trajectory on the X axis.


			// After hitSound is determined, add the brick's point value to the player's score.
			manager.addPoints(brick.getPoints());

			if (brick.getPoints() == 7 && !manager.wasRedHit())
			{
				ball.increaseSpeed();
				manager.redHit();
			}

			if (brick.getPoints() == 5 && !manager.wasOrangeHit())
			{
				ball.increaseSpeed();
				manager.orangeHit();
			}

			if (manager.brickCount() == 4 || manager.brickCount() == 12)
			{
				ball.increaseSpeed();
			}
			if(!manager.isMuted())
			{
				hitSound.play();
			}
			manager.incrementBrickCounter();
			break;
		}
	}
}

void ofApp::borderHitCheck()
{
	// Checking if the ball has hit one of the sides
	ball.hitSide();

	// Checking if top of the canvas is hit
	if (ball.hitTop() && !manager.isEasyMode())
	{
		paddle.shrink();
	}

	// Checking if the bottom of the canvas is hit
	if (ball.hitBottom() && !manager.isGameOver())
	{
		// If lives are above 0, reset the ball's location to the start and decrement the life counter
		if (manager.getLives() > 0)
		{
			ball.reset();
			manager.loseALife();
		}
		// If the lives are 0 or less, set paused and game over to true.
		else
		{
			backgroundMusic.stop();
			if(!manager.isMuted())
			{
				gameOverSound.play();
			}
			manager.pauseButton();
			manager.loseGame();
		}
	}
}

void ofApp::playGameMusic()
{
	if (!manager.isGameStarted() && !titleMusic.isPlaying())
	{
		titleMusic.setLoop(true);
		titleMusic.play();
	}

	if (manager.isGameStarted() && !manager.isGameOver() && !manager.isGameWon())
	{
		if (!backgroundMusic.isLoaded())
		{
			backgroundMusic.load("Arcade-Puzzler.mp3");
		}
		if (titleMusic.isPlaying())
		{
			titleMusic.stop();
		}

		if (!backgroundMusic.isPlaying())
		{
			backgroundMusic.setLoop(true);
			backgroundMusic.play();
		}
	}
}
#pragma endregion