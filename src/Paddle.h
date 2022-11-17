#pragma once
#include "Coordinates.h"
#include "ofRectangle.h"
#include "RectangleSize.h"

/**
 * \brief Class for the player's paddle in the game.
 */
class Paddle 
{
	RectangleSize mSize;
	Coordinates mPosition;
	float mSpeed;
	float mHalf;
	ofRectangle mRectangle;
public:
	/**
	 * \brief Initializes the paddle with the default parameters.
	 */
	Paddle();

	/**
	 * \brief Initializes the paddle with the given parameters.
	 * \param size Struct containing the dimensions of the paddle.
	 * \param position Starting X and Y coordinates for the paddle.
	 * \param speed Speed the paddles moves.
	 */
	Paddle(RectangleSize size, Coordinates position, float speed);

	/**
	 * \brief Moves the paddle based on a modifier passed by the main app.
	 * \param modifier Integer passed by the main app, will be 1 or -1.
	 */
	void move(const int offset);

	/**
	 * \brief Shrinks the paddle to half of it's initial size
	 */
	void shrink();

	/**
	 * \brief Draws the paddle to the canvas
	 */
	void draw();

	/**
	 * \brief Checks if given rectangle is intersecting with brick
	 * \param rect rectangle to check for intersection
	 * \return True if intersection occurs, false if not
	 */
	bool hit(const ofRectangle rect);

	/**
	 * \brief Resets the paddle to it's starting position.
	 */
	void reset();

	/**
	 * \brief Moves the paddle on the X axis to the location of the mouse on the X axis.
	 * \param newX The value of the mouse's X position.
	 */
	void mouseMove(const int newX);

	/**
	 * \brief Returns the width of the paddle
	 * \return Width of the paddle
	 */
	float getWidth();

	/**
	 * \brief Indicates if the ball has hit the top of the paddle.
	 * \param rect ofRectangle of the ball object.
	 * \return True of the ball has hit the top of the paddle. 
	 */
	bool topHit(const ofRectangle rect);

	/**
	 * \brief Indicates if the ball has hit either side of the paddle.
	 * \param rect ofRectangle of the ball object.
	 * \return True of the ball has hit either side of the paddle.
	 */
	bool sideHit(const ofRectangle rect);
};
