#include "GameManager.h"

GameManager::GameManager()
	: mIsPaused{ true }, mIsGameStarted{ false }, mScore{ 0 }, mLives{ 3 }, mIsGameOver{ false }, mIsGameWon{ false }, mIsEasyMode{ false }, mWasRedHit{ false },
	mWasOrangeHit{ false }, mBrickCounter{ 0 }, mIsMuted{ false }
{}

void GameManager::pauseButton()
{
	mIsPaused = !mIsPaused;
}

bool GameManager::isGamePaused()
{
	return mIsPaused;
}

void GameManager::gameStarted()
{
	mIsGameStarted = true;
}

bool GameManager::isGameStarted()
{
	return mIsGameStarted;
}

void GameManager::addPoints(int pointValue)
{
	mScore += pointValue;
}

int GameManager::getScore()
{
	return mScore;
}

void GameManager::loseALife()
{
	mLives--;
}

int GameManager::getLives()
{
	return mLives;
}

void GameManager::loseGame()
{
	mIsGameOver = true;
}

bool GameManager::isGameOver()
{
	return mIsGameOver;
}

void GameManager::winGame()
{
	mIsGameWon = true;
}

bool GameManager::isGameWon()
{
	return mIsGameWon;
}

void GameManager::easyModeOn()
{
	mIsEasyMode = true;
	mLives = 10;
}

void GameManager::easyModeOff()
{
	mIsEasyMode = false;
	mLives = 3;
}

bool GameManager::isEasyMode()
{
	return mIsEasyMode;
}

void GameManager::redHit()
{
	mWasRedHit = true;
}

bool GameManager::wasRedHit()
{
	return mWasRedHit;
}

void GameManager::orangeHit()
{
	mWasOrangeHit = true;
}

bool GameManager::wasOrangeHit()
{
	return mWasOrangeHit;
}

void GameManager::incrementBrickCounter()
{
	mBrickCounter++;
}

int GameManager::brickCount()
{
	return mBrickCounter;
}

void GameManager::reset()
{
	mIsPaused = true;
	mIsGameStarted = true;
	mScore = 0;
	
	if(isEasyMode())
	{
		mLives = 10;
	}
	else
	{
		mLives = 3;
	}
	
	mIsGameOver = false;
	mIsGameWon = false;
	//mIsEasyMode = false;
	mWasRedHit = false;
	mWasOrangeHit = false;
	mBrickCounter = 0;
}

void GameManager::muteUnmute()
{
	mIsMuted = !mIsMuted;
}

bool GameManager::isMuted()
{
	return mIsMuted;
}












