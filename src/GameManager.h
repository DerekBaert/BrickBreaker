#pragma once

/**
 * \brief Tracks states within the game, as well as the score and lives.
 */
class GameManager
{
	bool mIsPaused;
	bool mIsGameStarted;
	int mScore;
	int mLives;
	bool mIsGameOver;
	bool mIsGameWon;
	bool mIsEasyMode;
	bool mWasRedHit;
	bool mWasOrangeHit;
	int mBrickCounter;
public:
	GameManager();

	/**
	 * \brief Pauses the game.
	 */
	void pauseButton();

	/**
	 * \brief Checks if game is paused.
	 * \return True if game is paused, false if not.
	 */
	bool isGamePaused();

	/**
	 * \brief Flags the game as started (not on title screen).
	 */
	void gameStarted();

	/**
	 * \brief Checks if game is started.
	 * \return True if game is started.
	 */
	bool isGameStarted();

	/**
	 * \brief Adds the passed in integer to the total player score.
	 * \param pointValue The points to add to the score.
	 */
	void addPoints(int pointValue);

	/**
	 * \brief Returns the current score.
	 * \return The current score.
	 */
	int getScore();

	/**
	 * \brief Decrements life counter.
	 */
	void loseALife();

	/**
	 * \brief Returns life count.
	 * \return Amount of lives remaining.
	 */
	int getLives();

	/**
	 * \brief Flags the game as over.
	 */
	void loseGame();

	/**
	 * \brief Checks if game is over.
	 * \return True if game is over, false if not.
	 */
	bool isGameOver();

	/**
	 * \brief Flags the game as won.
	 */
	void winGame();

	/**
	 * \brief Checks if the game is won.
	 * \return True if the game is won, false if not.
	 */
	bool isGameWon();

	/**
	 * \brief Flags the game to easy mode and increases lives to 10.
	 */
	void easyModeOn();

	/**
	 * \brief Checks the mode of the current game.
	 * \return True if easy mode is on, false if not.
	 */
	bool isEasyMode();

	/**
	 * \brief Flags that a red brick has been hit.
	 */
	void redHit();

	/**
	 * \brief Checks if a red brick as been hit.
	 * \return True if a red brick has been hit, false if not.
	 */
	bool wasRedHit();

	/**
	 * \brief Flags that an orange brick has been hit.
	 */
	void orangeHit();

	/**
	 * \brief Checks if an orange brick as been hit.
	 * \return True if an orange brick has been hit, false if not.
	 */
	bool wasOrangeHit();

	/**
	 * \brief Increments the brick counter.
	 */
	void incrementBrickCounter();

	/**
	 * \brief Returns how many bricks have been hit.
	 * \return Amount of bricks hit.
	 */
	int brickCount();

	void reset();
};
