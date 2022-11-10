#pragma once

#include "Ball.h"
#include "Brick.h"
#include "ofMain.h"
#include "Paddle.h"


class ofApp : public ofBaseApp
{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
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
		bool paused;
		const int OF_KEY_SPACE = 32;
		float points;

		float brickStart;

		float fifthOfScreen;
		
		float brickWidth;
		float buffer;

		
};