#pragma once
#include "Coordinates.h"
#include "RectangleSize.h"
#include "Sides.h"
#include <ofMain.h>
class Brick
{
	RectangleSize mSize;
	Coordinates mPosition;
	ofColor mColour;
	int mPointValue;
	bool mHit;
	ofRectangle mRectangle;

public:
	/**
	 * \brief Initializes the brick object with default values.
	 */
	Brick();

	/**
	 * \brief Initializes the brick object with the given parameters.
	 * \param size Rectangle size struct containing the height and width of the brick.
	 * \param position Coordinates struct containing the X and Y positions of the brick.
	 * \param colour ofColor object representing the color of the brick.
	 * \param pointValue The amount of points the brick is worth.
	 */
	Brick(RectangleSize size, Coordinates position, ofColor colour, int pointValue);

	/**
	 * \brief Draws the brick to the canvas
	 */
	void draw();

	/**
	 * \brief Checks if the given rectangle is touching the top or bottom of the brick
	 * \param rect Rectangle to compare against
	 * \return True if the rectangle is touching the top or bottom, false if not
	 */
	bool topBottomHit(const ofRectangle rect);

	/**
	 * \brief Checks if the given rectangle is touching the side of the brick
	 * \param rect Rectangle to compare against
	 * \return True if the rectangle is touching the side, false if not
	 */
	bool sideHit(const ofRectangle rect);

	/**
	 * \brief Return the rectangle object being drawn to the screen.
	 * \return The rectangle object
	 */
	ofRectangle getRect();

	/**
	 * \brief Returns the point value of the brick.
	 * \return The point value of the brick
	 */
	int getPoints();

	/**
	 * \brief Indicates if the brick has been broken or not
	 * \return True if destroyed, false if not
	 */
	bool destroyed();

	/**
	 * \brief Resets the brick to not destroyed.
	 */
	void reset();
};
