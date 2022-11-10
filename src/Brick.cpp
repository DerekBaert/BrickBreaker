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
Brick::Brick(RectangleSize size, Coordinates position, ofColor colour, float pointValue)
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
 * \brief Checks if given rectangle is intersecting with brick
 * \param rect rectangle to check for intersection
 * \return True if intersection occurs, false if not
 */
bool Brick::hit(const ofRectangle rect)
{
	if(!mHit)
	{
		mHit = mRectangle.intersects(rect);

	}
	return mRectangle.intersects(rect);
}



float* Brick::getSides()
{
	float sides[4] = { mRectangle.getLeft(), mRectangle.getRight(), mRectangle.getTop(), mRectangle.getBottom() };
	return sides;
}

float Brick::getPoints()
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




