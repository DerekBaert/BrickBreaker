#include "Brick.h"

Brick::Brick() :mSize{ 10,10 }, mPosition{ 0,0 }, mColour{ ofColor(0,0,0)}, mPointValue{1}, mHit{false},
	mRectangle{ mPosition.x, mPosition.y, mSize.width, mSize.height }
{}


Brick::Brick(RectangleSize size, Coordinates position, ofColor colour, int pointValue)
	:mSize{ size }, mPosition{ position }, mColour{ colour }, mPointValue{pointValue}, mHit{ false }, mRectangle{ mPosition.x, mPosition.y, mSize.width, mSize.height }
{}


void Brick::draw()
{
	ofSetColor(mColour);
	if(!mHit)
	{
		ofDrawRectangle(mRectangle);
	}	
}

bool Brick::topBottomHit(const ofRectangle rect)
{
	if(!mHit)
	{
		mHit = rect.getTop() <= mRectangle.getBottom() && rect.getBottom() >= mRectangle.getTop()
		&& (rect.getTop() > mRectangle.getTop() + mRectangle.height / 2 || rect.getBottom() < mRectangle.getTop() + mRectangle.height / 2);
	}	
	return rect.getTop() <= mRectangle.getBottom() && rect.getBottom() >= mRectangle.getTop()
		&& (rect.getTop() > mRectangle.getTop() + mRectangle.height / 2 || rect.getBottom() < mRectangle.getTop() + mRectangle.height / 2);
}

bool Brick::sideHit(const ofRectangle rect)
{
	if(!mHit)
	{
		mHit = rect.getRight() >= mRectangle.getLeft() && rect.getLeft() <= mRectangle.getRight()
		&& (rect.getLeft() < mRectangle.getLeft() || rect.getRight() > mRectangle.getRight());
	}	
	return rect.getRight() >= mRectangle.getLeft() && rect.getLeft() <= mRectangle.getRight()
		&& (rect.getLeft() < mRectangle.getLeft() || rect.getRight() > mRectangle.getRight());
}

ofRectangle Brick::getRect()
{
	return mRectangle;
}

int Brick::getPoints()
{
	return mPointValue;
}

bool Brick::destroyed()
{
	return mHit;
}

void Brick::reset()
{
	mHit = false;
}




