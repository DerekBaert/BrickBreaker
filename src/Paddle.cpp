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
	mRectangle.x += mSpeed * modifier;
}

void Paddle::shrink()
{
	mRectangle.width = mHalf;
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

void Paddle::reset()
{
	mRectangle.x = mPosition.x;
	mRectangle.y = mPosition.y;
}

void Paddle::mouseMove(const int newX)
{
	mRectangle.x = newX;
}

float Paddle::getWidth()
{
	return mRectangle.width;
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


