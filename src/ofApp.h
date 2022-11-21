#pragma once
#include "Ball.h"
#include "Brick.h"
#include "GameManager.h"
#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"
#include "Paddle.h"
#include "ofxGui.h"


class ofApp : public ofBaseApp
{
	public:
	
		void setup();
		void update();
		void draw();
		void keyPressed(int key);

		/**
		 * \brief Plays the game's background music depending on what screen is displayed.
		 */
		void playGameMusic();

		/**
		 * \brief Checks if the ball has hit one of the borders and adjusts the ball's direction if it has.
		 */
		void borderHitCheck();

		/**
		 * \brief Checks if the ball has hit the paddle.
		 * \param ballRect ofRectangle of the ball
		 */
		void paddleHitCheck(ofRectangle& ballRect);

		/**
		 * \brief Checks if the ball has hit a brick.
		 * \param ballRect ofRectangle of the ball.
		 */
		void brickHitCheck(ofRectangle ballRect, ofRectangle ballPrevious);

		/**
		 * \brief Displays Title screen to canvas
		 */
		void titleScreen();

		/**
		 * \brief Begins game
		 */
		void gamePlay();

		/**
		 * \brief Creates the buttons for the title screen
		 */
		void createButtons();

		/**
		 * \brief Loads sounds and music players for the game.
		 */
		void loadSounds();

		/**
		 * \brief Creates the ball paddle objects
		 */
		void createBallAndPaddle();

		/**
		 * \brief Populates the bricks array with Brick objects
		 */
		void loadBricks();

		/**
		 * \brief Starts the game on easy mode.
		 */
		void easyMode();

		/**
		 * \brief Starts the game on normal mode.
		 */
		void normalMode();

		/**
		 * \brief Resets the game on game over or game complete.
		 */
		void resetGame();

		/**
		 * \brief Moves the paddle to follow the mouse.
		 * \param x The X position of the mouse.
		 * \param y The Y position of the mouse.
		 */
		void mouseMoved(int x, int y);


		const int WINDOW_HEIGHT{ ofGetHeight() };
		const int WINDOW_WIDTH{ ofGetWidth() };
		Ball ball;
		Paddle paddle;
		std::vector<Brick> bricks{};
		RectangleSize paddleSize;
		const int OF_KEY_SPACE {32};

		GameManager manager;

		float brickStart;
		float fifthOfScreen;		
		float brickWidth;
		float buffer;

		ofxCenteredTrueTypeFont gameFont;
		ofxCenteredTrueTypeFont titleFont;

		ofSoundPlayer hitSound;
		ofSoundPlayer winSound;
		ofSoundPlayer gameOverSound;
		ofSoundPlayer backgroundMusic;
		ofSoundPlayer titleMusic;

		ofxButton easyStart;
		ofxButton normalStart;
		
};