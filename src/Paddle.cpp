#include "Paddle.h"

#include "ofAppRunner.h"
#include "ofGraphics.h"
#include "ofRectangle.h"


Paddle::Paddle() : mSize{ 10,20 }, mPosition{ 10,10 }, mSpeed{ 10 }, mHalf{ 10 }, mRectangle{ mPosition.x, mPosition.y, mSize.width, mSize.height }
{}

Paddle::Paddle(RectangleSize size, Coordinates position, float speed)
	: mSize{ size }, mPosition{ position }, mSpeed{speed}, mHalf {	size.width / 2}, mRectangle{ mPosition.x, mPosition.y, mSize.width, mSize.height }
{}

void Paddle::move(const int modifier)
{
	mRectangle.setX(mRectangle.getX() + mSpeed * modifier);
}

void Paddle::shrink()
{
	mRectangle.setWidth(mHalf);
}

void Paddle::draw()
{
	ofSetColor(0, 0, 200);
	ofDrawRectangle(mRectangle);
}


bool Paddle::hit(const ofRectangle rect)
{
	return mRectangle.intersects(rect);
}

ofRectangle Paddle::getIntersection(const ofRectangle rect)
{
	return mRectangle.getIntersection(rect);
}


void Paddle::reset()
{
	mRectangle.setX(mPosition.x);
	mRectangle.setY(mPosition.y);
}

void Paddle::mouseMove(const int newX)
{
	mRectangle.setX(newX);
}

float Paddle::getWidth()
{
	return mRectangle.width;
}

ofRectangle Paddle::getRect()
{
	return mRectangle;
}

bool Paddle::topHit(const ofRectangle rect)
{
	return rect.getTop() <= mRectangle.getBottom() && rect.getBottom() >= mRectangle.getTop()
		&& (rect.getTop() > mRectangle.getTop() + mRectangle.height / 2 || rect.getBottom() < mRectangle.getTop() + mRectangle.height / 2);
}

bool Paddle::sideHit(const ofRectangle rect)
{
	return rect.getRight() >= mRectangle.getLeft() && rect.getLeft() <= mRectangle.getRight()
		&& (rect.getLeft() < mRectangle.getLeft() || rect.getRight() > mRectangle.getRight());
}


