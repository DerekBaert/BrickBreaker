#pragma once


#include "Ball.h"
#include "Brick.h"
#include "GameManager.h"
#include "ofMain.h"
#include "ofxCenteredTrueTypeFont.h"
#include "Paddle.h"
#include "Sides.h"


class ofApp : public ofBaseApp
{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void resetGame();
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		Ball ball;
		Paddle paddle;
		std::vector<Brick> bricks{};
		RectangleSize paddleSize;
		const int OF_KEY_SPACE {32};

		GameManager manager;
		/*bool paused{ true };
		bool gameStart{ true };
		int points {0};
		int lives {3};
		bool gameOver {false};
		bool gameWon{ false };
		bool easy {false};
		bool redFlag {false};
		bool orangeFlag{false};
		int brickCounter{ 0 };*/

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

		
};