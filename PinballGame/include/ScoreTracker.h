/**
The score tracker is a small class used to encapsulate the calculation of a 'score' value. The score can be retrieved
or modified at any time, and contains a multiplier value for easily increasing or decreasing the actual score received
when modifying the score.
*/

#ifndef ScoreTracker_H
#define ScoreTracker_H

class ScoreTracker
{	
	public:
		ScoreTracker();
		void setScore(float fScore);
		void modScore(float fModification);
		float getScore() const;
		void setScoreMultiplier(float fMultiplier);	
		void modScoreMultiplier(float fMultiplier);
		float getScoreMultiplier();

	protected:

	private:
		float m_fScore;
		float m_fScoreMultiplier;
};

#endif