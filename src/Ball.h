#pragma once
#include "Coordinates.h"
#include "ofRectangle.h"
#include "RectangleSize.h"

/**
 * \brief Class for the ball object in the game.
 */
class Ball
{
	float mSize;
	Coordinates mPosition;
	Coordinates mSpeed;
	Coordinates mOffset;
	ofRectangle mRectangle;
	ofRectangle mPrevious;
public:
	/**
	 * \brief Constructs the ball with default parameters.
	 */
	Ball();

	/**
	 * \brief Constructs the ball with the given parameters.
	 * \param size The size of the ball.
	 * \param position The starting X and Y coordinates of the ball.
	 */
	Ball(float size, Coordinates position);

	/**
	 * \brief Changes the ball's position.
	 */
	void move();

	/**
	 * \brief Increases the ball's speed.
	 */
	void increaseSpeed();

	/**
	 * \brief Reverses the ball's direction on the X axis.
	 */
	void reverseX();

	/**
	 * \brief Reverses the ball's direction on the Y axis.
	 */
	void reverseY();

	/**
	 * \brief Draws the ball to the canvas
	 */
	void draw();

	/**
	 * \brief Checks if the ball has hit the side of the canvas, and reverses the X offset when it does.
	 */
	void hitSide();

	/**
	 * \brief Resets the position of the ball to it's starting location.
	 */
	void reset();

	/**
	 * \brief Resets the ball's location and it's speed to their starting values.
	 */
	void newGame();

	/**
	 * \brief Checks if the ball has hit the top of the screen
	 * \return True if the ball has hit the top of the screen, false if not.
	 */
	bool hitTop();

	/**
	 * \brief Checks if the ball has hit the bottom of the screen
	 * \return True if the ball has hit the bottom of the screen, false if not.
	 */
	bool hitBottom();

	/**
	 * \brief Returns the position of the ball.
	 * \return The X Y coordinates of the ball as a Coordinates struct.
	 */
	Coordinates getPosition();

	/**
	 * \brief Returns the rectangle object the class draws to the canvas. Typically used for intersection checks.
	 * \return The rectangle object the class draws to the canvas.
	 */
	ofRectangle getRect();

	/**
	 * \brief Pushes ball out of paddle
	 * \param rect ofRectangle representing intersection of paddle and ball
	 */
	void pushOut(ofRectangle intersection, ofRectangle rect);

	/**
	 * \brief The previous position of the ball object
	 * \return The ofRectangle of the ball's previous position.
	 */
	ofRectangle getPrevious();

};
