#include "Ball.h"

#include "ofAppRunner.h"
#include "ofGraphics.h"


Ball::Ball() : mSize{ 10 }, mPosition{ 5,5 }, mSpeed{ 2,2 }, mOffset{ 1,-1 }, mRectangle(mPosition.x, mPosition.y, mSize, mSize)
{}

Ball::Ball(float size, Coordinates position) : mSize{ size }, mPosition{ position }, mSpeed{ 2,2 }, mOffset { 1,-1 }, mRectangle(mPosition.x, mPosition.y, mSize, mSize)
{}

void Ball::move()
{
	mRectangle.x += mSpeed.x * mOffset.x;
	mRectangle.y += mSpeed.y * mOffset.y;
}

void Ball::increaseSpeed()
{
	mSpeed.x += 0.5;
	mSpeed.y += 0.5;
}

void Ball::reverseX()
{
	mOffset.x *= -1;
}

void Ball::reverseY()
{
	mOffset.y *= -1;
}

void Ball::draw()
{
	ofSetColor(255);
	ofDrawRectangle(mRectangle);
}

void Ball::hitSide()
{
	if(mRectangle.x > ofGetWidth() - (mSize / 2) || mRectangle.x < 0 + (mSize / 2))
	{
		reverseX();
	}
}

void Ball::reset()
{
	mRectangle.x = mPosition.x;
	mRectangle.y = mPosition.y;
	mOffset = { 1,-1 };
}

void Ball::newGame()
{
	reset();
	mSpeed = { 2,2 };
}

bool Ball::hitTop()
{
	if(mRectangle.y <= 0)
	{
		reverseY();
	}
	return mRectangle.y <= 0 + (mSize / 2);
}

bool Ball::hitBottom()
{
	return mRectangle.y >= ofGetHeight();
}

Coordinates Ball::getPosition()
{
	return {mRectangle.x, mRectangle.y};
}

 ofRectangle Ball::getRect()
{
	return mRectangle;
}

