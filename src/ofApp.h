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