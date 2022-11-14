#include "Brick.h"


/// <summary>
/// Constructs the brick with default values.
/// </summary>
Brick::Brick() :mSize{ 10,10 }, mPosition{ 0,0 }, mColour{ ofColor(0,0,0)}, mPointValue{1}, mHit{false},
	mRectangle{ mPosition.x, mPosition.y, mSize.width, mSize.height }
{}

/**
 * \brief Constructs a brick with the given parameters
 * \param size Struct with the dimensions of the brick
 * \param position Struct with the X and Y coordinates for the brick
 * \param colour Colour of the brick
 * \param pointValue How many points the brick is worth
 */
Brick::Brick(RectangleSize size, Coordinates position, ofColor colour, int pointValue)
	:mSize{ size }, mPosition{ position }, mColour{ colour }, mPointValue{pointValue}, mHit{ false }, mRectangle{ mPosition.x, mPosition.y, mSize.width, mSize.height }
{}

/**
 * \brief Draws the brick to the canvas
 */
void Brick::draw()
{
	ofSetColor(mColour);
	if(!mHit)
	{
		ofDrawRectangle(mRectangle);
	}	
}

/**
 * \brief Checks if the given rectangle is touching the top or bottom of the brick
 * \param rect Rectangle to compare against
 * \return True if the rectangle is touching the top or bottom, false if not
 */
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

/**
 * \brief Checks if the given rectangle is touching the side of the brick
 * \param rect Rectangle to compare against
 * \return True if the rectangle is touching the side, false if not
 */
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

/**
 * \brief Return the rectangle object being drawn to the screen.
 * \return The rectangle object
 */
ofRectangle Brick::getRect()
{
	return mRectangle;
}

/**
 * \brief Returns the point value of the brick.
 * \return The point value of the brick
 */
int Brick::getPoints()
{
	return mPointValue;
}

/**
 * \brief Indicates if the brick has been broken or not
 * \return True if destroyed, false if not
 */
bool Brick::destroyed()
{
	return mHit;
}

/**
 * \brief Resets the brick to not destroyed.
 */
void Brick::reset()
{
	mHit = false;
}




