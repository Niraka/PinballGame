/**
A ScoreManager loads, saves and stores up to 8 high score float values in ascending order.

Typically, only one ScoreManager will ever be required as a component of the game that is currently
being played. 
*/

#ifndef ScoresManager_H
#define ScoresManager_H

#include <string>
#include <iostream>
#include <fstream>

class ScoresManager
{
	public:
		ScoresManager();

		void addScore(float fScore);
		void sortScores();
		void resetScores();
		void saveScores(std::string file);
		void loadScores(std::string file);
		float getScore(int iIndex);

	protected:
	private:
		const static int s_ikNumScores = 8;
		float m_afScores[8];
};

#endif