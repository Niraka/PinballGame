#include "UIDestructor.h"

/**
Constructs a UIDestructor with the given parameters.

@param uim The UIManager containing the components to be destructed. */
UIDestructor::UIDestructor(UIManager& uim)
{
	m_pUIM = &uim;
	m_tm = TextureManager::getInstance();
	m_am = AudioManager::getInstance();
	m_sm = StringsManager::getInstance();
	m_fm = FontManager::getInstance();
}

/**
Deconstructs the UIComponents and resources listed in the given deconstruction file.

@param sDeconstructorFile The UIDestructor file. */
void UIDestructor::deconstructUI(std::string sDeconstructorFile)
{
	std::ifstream inputStream;
	std::string line;

	UIComponent* comp;

	inputStream.open(sDeconstructorFile);
	if (!inputStream.is_open())
	{
		return;
	}

	// Delete the components listed in the config file & clean up any resources
	while (std::getline(inputStream, line))
	{
		// Skip the line if it is empty
		if (line.empty())
		{
			continue;
		}
		// Skip the line if it begins with a #, space, or new line
		if (line.at(0) == '#' || line.at(0) == '/n' || line.at(0) == ' ')
		{
			continue;
		}
		else
		{
			if (line == "[textures]")
			{
				while (std::getline(inputStream, line))
				{
					if (line.empty())
					{
						// Finished clearing textures
						break;
					}
					else
					{
						m_tm->clearTexture(line);
					}
				}
			}
			else if (line == "[audio]")
			{
				while (std::getline(inputStream, line))
				{
					if (line.empty())
					{
						// Finished clearing audio
						break;
					}
					else
					{
						if (line.at(0) == 'm')
						{
							m_am->clearMusic(line.substr(1, line.size()));
						}
						else if (line.at(0) == 's')
						{
							m_am->clearSoundBuffer(line.substr(1, line.size()));
						}
					}
				}
			}
			else if (line == "[strings prefix]")
			{
				std::getline(inputStream, line);
				if (!line.empty())
				{
					m_sm->setWorkingDirectory(line);
				}
			}
			else if (line == "[strings]")
			{
				std::getline(inputStream, line);
				while (!line.empty())
				{
					m_sm->clearStrings(line);
					std::getline(inputStream, line);
				}
			}
			else if (line == "[fonts]")
			{
				std::getline(inputStream, line);
				while (!line.empty())
				{
					m_fm->clearFont(line);
					std::getline(inputStream, line);
				}
			}
			else if (line == "[root links]")
			{
				std::getline(inputStream, line);
				while (!line.empty())
				{
					m_pUIM->getRootComponent().removeChild(line);
					std::getline(inputStream, line);
				}
			}
			else if (line == "[deconstruction]")
			{
				std::getline(inputStream, line);
				while (!line.empty())
				{
					comp = m_pUIM->getUIComponentRef(line);
					delete comp;
					m_pUIM->removeUIComponentRef(line);
					std::getline(inputStream, line);
				}
			}
		}
	}

	inputStream.close();
}