#pragma once
#include "Coordinates.h"
#include "RectangleSize.h"
#include "Sides.h"
#include <ofMain.h>
class Brick
{
	RectangleSize mSize;
	Coordinates mPosition;
	ofColor mColour;
	int mPointValue;
	bool mHit;
	ofRectangle mRectangle;

public:
	Brick();
	Brick(RectangleSize size, Coordinates position, ofColor colour, int pointValue);

	void draw();

	bool topBottomHit(const ofRectangle rect);
	bool sideHit(const ofRectangle rect);

	ofRectangle getRect();
	int getPoints();
	bool destroyed();
	void reset();
};
