#pragma once
#include "Coordinates.h"
#include "RectangleSize.h"
#include <ofMain.h>
class Brick
{
	RectangleSize mSize;
	Coordinates mPosition;
	ofColor mColour;
	float mPointValue;
	bool mHit;
	ofRectangle mRectangle;

public:
	Brick();
	Brick(RectangleSize size, Coordinates position, ofColor colour, float pointValue);

	void draw();

	bool hit(const ofRectangle rect);
	float* getSides();
	float getPoints();
	bool destroyed();
};
