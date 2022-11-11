#include "Paddle.h"

#include "ofGraphics.h"
#include "ofRectangle.h"


Paddle::Paddle() : mSize{ 10,20 }, mPosition{ 10,10 }, mSpeed{ 10 }, mHalf{ 10 }, mRectangle{ mPosition.x, mPosition.y, mSize.width, mSize.height }
{}

/**
 * \brief Constructs the paddle with the given parameters
 * \param size Struct containing the dimensions of the paddle
 * \param position Starting X and Y coordinates for the paddle
 * \param speed Speed the paddles moves
 */
Paddle::Paddle(RectangleSize size, Coordinates position, float speed)
	: mSize{ size }, mPosition{ position }, mSpeed{speed}, mHalf {	size.width / 2}, mRectangle{ mPosition.x, mPosition.y, mSize.width, mSize.height }
{}

/**
 * \brief Moves the paddle based on a modifier passed by the main app. 
 * \param modifier Integer passed by the main app, will be 1 or -1.
 */
void Paddle::move(const int modifier)
{
	mRectangle.x += mSpeed * modifier;
}

/**
 * \brief Shrinks the paddle to half of it's initial size
 */
void Paddle::shrink()
{
	mRectangle.width = mHalf;
}

/**
 * \brief Draws the paddle to the canvas
 */
void Paddle::draw()
{
	ofSetColor(0, 0, 200);
	ofDrawRectangle(mRectangle);
}

/**
 * \brief Checks if given rectangle is intersecting with brick
 * \param rect rectangle to check for intersection
 * \return True if intersection occurs, false if not
 */
bool Paddle::hit(const ofRectangle rect)
{
	return mRectangle.intersects(rect);
}

void Paddle::reset()
{
	mRectangle.x = mPosition.x;
	mRectangle.y = mPosition.y;
}

