#include "ScoreTracker.h"

/**
Constructs a ScoreTracker with an initial score of 0 and a score multiplier of 1. */
ScoreTracker::ScoreTracker()
{
	m_fScore = 0;
	m_fScoreMultiplier = 1;
}

/**
Sets the score multiplier to the given value. 

@param fMultiplier The multiplier. */
void ScoreTracker::setScoreMultiplier(float fMultiplier)
{
	m_fScoreMultiplier = fMultiplier;
}

/**
Modifies the score multiplier by the given value. 

@param fMultiplier The multiplier to add. */
void ScoreTracker::modScoreMultiplier(float fMultiplier)
{
	m_fScoreMultiplier += fMultiplier;
}

/**
Returns the score multiplier.

@return The score multiplier. */
float ScoreTracker::getScoreMultiplier()
{
	return m_fScoreMultiplier;
}

/**
Sets the score. 

@param fScore The score. */
void ScoreTracker::setScore(float fScore)
{
	m_fScore = fScore;
}

/**
Modifies the score by the given value. The value is multiplied by the score multiplier before
being added to the current score. 

@param fModification The score to add. */
void ScoreTracker::modScore(float fModification)
{
	m_fScore += (fModification * m_fScoreMultiplier);
}

/**
Returns the score.

@return The score. */
float ScoreTracker::getScore() const
{
	return m_fScore;
}