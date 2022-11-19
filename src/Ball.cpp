#include "Ball.h"

#include "ofAppRunner.h"
#include "ofGraphics.h"
#include "ofMath.h"


Ball::Ball() : mSize{ 10 }, mPosition{ 5,5 }, mSpeed{ 100,100 }, mOffset{ 1,-1 }, mRectangle(mPosition.x, mPosition.y, mSize, mSize)
{}

Ball::Ball(float size, Coordinates position) : mSize{ size }, mPosition{ position }, mSpeed{ 100,100 }, mOffset { 1,-1 }, mRectangle(mPosition.x, mPosition.y, mSize, mSize)
{}

void Ball::move()
{
	mRectangle.setX(mRectangle.getX() + (mSpeed.x * ofGetLastFrameTime()) * mOffset.x);
	mRectangle.setY(mRectangle.getY() + (mSpeed.y * ofGetLastFrameTime()) * mOffset.y);
}

void Ball::increaseSpeed()
{
	mSpeed.x += 25;
	mSpeed.y += 25;
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
	if(mRectangle.getRight() >= ofGetWidth() || mRectangle.getLeft() <= 0)
	{
		reverseX();
		ofClamp(mRectangle.x, 0, ofGetWidth() - mRectangle.getWidth());
	}

}

void Ball::reset()
{
	mRectangle.setX(mPosition.x);
	mRectangle.setY(mPosition.y);
	mOffset = { 1,-1 };
}

void Ball::newGame()
{
	reset();
	mSpeed = { 100,100 };
}

bool Ball::hitTop()
{
	if(mRectangle.getTop() <= 0)
	{
		reverseY();
		ofClamp(mRectangle.y, 0, ofGetHeight());
	}

	return mRectangle.getY() <= 0 + (mSize / 2);
}

bool Ball::hitBottom()
{
	return mRectangle.getY() >= ofGetHeight();
}

Coordinates Ball::getPosition()
{
	return {mRectangle.getX(), mRectangle.getY()};
}

 ofRectangle Ball::getRect()
{
	return mRectangle;
}

void Ball::pushOut(ofRectangle intersection, ofRectangle rect)
{
	if (mRectangle.getTop() >= rect.getTop() + rect.getHeight() / 2)
	{
		mRectangle.setY(intersection.getTop() + intersection.getHeight());
	}
	else
	{
		mRectangle.setY(intersection.getTop() - mRectangle.getHeight());
	}
}

