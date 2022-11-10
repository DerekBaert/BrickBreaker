#include "Ball.h"

#include "ofAppRunner.h"
#include "ofGraphics.h"

/**
 * \brief Constructs the ball with default parameters.
 */
Ball::Ball() : mSize{ 10 }, mPosition{ 5,5 }, mSpeed{ 1,1 }, mOffset{ 1,-1 }, mRectangle(mPosition.x, mPosition.y, mSize, mSize)
{}

/**
 * \brief Constructs the ball with the given parameters.
 * \param size The size of the ball.
 * \param position The starting X and Y coordinates of the ball.
 */
Ball::Ball(float size, Coordinates position) : mSize{ size }, mPosition{ position }, mSpeed{ 2,2 }, mOffset { 1,-1 }, mRectangle(mPosition.x, mPosition.y, mSize, mSize)
{}

/**
 * \brief Changes the ball's position.
 */
void Ball::move()
{
	mRectangle.x += mSpeed.x * mOffset.x;
	mRectangle.y += mSpeed.y * mOffset.y;
}

/**
 * \brief Increases the ball's speed.
 */
void Ball::increaseSpeed()
{
	mSpeed.x++;
	mSpeed.y++;
}

/**
 * \brief Reverses the ball's direction on the X axis.
 */
void Ball::reverseX()
{
	mOffset.x *= -1;
}

/**
 * \brief Reverses the ball's direction on the Y axis.
 */
void Ball::reverseY()
{
	mOffset.y *= -1;
}

/**
 * \brief Draws the ball to the canvas
 */
void Ball::draw()
{
	ofSetColor(255);
	ofDrawRectangle(mRectangle);
}

/**
 * \brief Checks if the ball has hit the side of the canvas, and reverses the X offset when it does.
 */
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
}

/**
 * \brief Checks if the ball has hit the top of the screen
 * \return True if the ball has hit the top of the screen, false if not.
 */
bool Ball::hitTop()
{
	if(mRectangle.y <= 0)
	{
		reverseY();
	}
	return mRectangle.y <= 0 + (mSize / 2);
}

/**
 * \brief Checks if the ball has hit the bottom of the screen
 * \return True if the ball has hit the bottom of the screen, false if not.
 */
bool Ball::hitBottom()
{
	return mRectangle.y >= ofGetHeight();
}

Coordinates Ball::getPosition()
{
	return {mRectangle.x, mRectangle.y};
}

/**
 * \brief Returns the rectangle object the class draws to the canvas. Typically used for intersection checks.
 * \return The rectangle object the class draws to the canvas.
 */
 ofRectangle Ball::getRect()
{
	return mRectangle;
}