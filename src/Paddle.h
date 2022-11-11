#pragma once
#include "Coordinates.h"
#include "ofRectangle.h"
#include "RectangleSize.h"
class Paddle 
{
	RectangleSize mSize;
	Coordinates mPosition;
	float mSpeed;
	float mHalf;
	ofRectangle mRectangle;
public:
	Paddle();

	Paddle(RectangleSize size, Coordinates position, float speed);

	void move(const int offset);

	void shrink();
	void draw();
	bool hit(const ofRectangle rect);
	void reset();
};
