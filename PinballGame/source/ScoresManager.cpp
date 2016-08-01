#include "ScoresManager.h"

/**
Constructs a default ScoresManager. */
ScoresManager::ScoresManager()
{
	for (int i = 0; i < s_ikNumScores; i++)
	{
		m_afScores[i] = 0.f;
	}
}

/**
Adds a new score value to the ScoresManager. If the new score is greater than at least one of the currently stored
score values, the new score replaces it. The scores are then sorted such that smaller scores are moved up the array. 

@param fScore The score to add. */
void ScoresManager::addScore(float fScore)
{
	if (fScore > m_afScores[(s_ikNumScores - 1)])
	{
		m_afScores[(s_ikNumScores - 1)] = fScore;
		sortScores();
	}
}

/**
Sorts the scores in the ScoreManager in to ascending order. The scores are sorted using bubblesort, which I
believe to be good enough given that there are only 8 score values and they are rarely out of order. */
void ScoresManager::sortScores()
{
	bool hasSwapped;
	do 
	{
		hasSwapped = false;
		for (int i = 0; i < (s_ikNumScores - 1); i++)
		{
			if (m_afScores[i] < m_afScores[(i + 1)])
			{
				float temporary = m_afScores[i];
				m_afScores[i] = m_afScores[(i + 1)];
				m_afScores[(i + 1)] = temporary;
				hasSwapped = true;
			}
		}
	} 
	while (hasSwapped);
}

/**
Saves the scores currently in the ScoreManager in to the specified text file. The file name will be appended to
"highscores/" and should should include the file extension.

@param sFile The file to save to. */
void ScoresManager::saveScores(std::string sFile)
{
	std::ofstream outputStream;
	outputStream.open("../data/highscores/" + sFile, std::ios_base::trunc);

	for (int i = 0; i < s_ikNumScores; i++)
	{
		outputStream << m_afScores[i] << "\n";
	}

	outputStream.close();
}

/**
Attempts to load up to 8 score values from the given text file. The file name will be appended to "highscores/" and
should should include the file extension.

@param sFile The file to load from. */
void ScoresManager::loadScores(std::string sFile)
{
	int iIndex = 0;
	std::string line;

	std::ifstream inputStream;
	inputStream.open("../data/highscores/" + sFile);
	while (std::getline(inputStream, line))
	{
		if (iIndex >= 8)
		{
			
			break;
		}

		// Skip the line if it begins with a #, space, or new line
		if (line.at(0) == '#' || line.at(0) == '/n' || line.at(0) == ' ')
		{
			continue;
		}
		else
		{
			m_afScores[iIndex] = stof(line);
			iIndex++;
		}
	}
	inputStream.close();
	sortScores();
}

/**
Resets all of the score values stored in the ScoreManager to 0. */
void ScoresManager::resetScores()
{
	for (int i = 0; i < s_ikNumScores; i++)
	{
		m_afScores[i] = 0.f;
	}
}

/**
Returns a score, identified by index. Returns -1 if the index was out of bounds.

@param iIndex The index of the score to get.
@return The score value stored at the specified index. */
float ScoresManager::getScore(int iIndex)
{
	if (iIndex >= 0 && iIndex < s_ikNumScores)
	{
		return m_afScores[iIndex];
	}
	else
	{
		return -1;
	}
}