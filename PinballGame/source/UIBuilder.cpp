#include "UIBuilder.h"

/**
Constructs a UIBuilder with the given parameters.

@param uim The UIManager to store the built UIComponents in. */
UIBuilder::UIBuilder(UIManager& uim)
{
	m_pUIM = &uim;
}

/**
Builds a UI using the given UI construction file. Loaded resources are stored in the relevant resource
containers (EG. TextureManager). Also attaches the given button listener to any components that require
one.

@param sUIFile The UIConstructor file.
@param bl A pointer to a button listener. */
void UIBuilder::buildUI(std::string sUIFile, UIButtonListener* bl)
{
	TextureManager* tm = TextureManager::getInstance();
	AudioManager* am = AudioManager::getInstance();
	StringsManager* sm = StringsManager::getInstance();
	FontManager* fm = FontManager::getInstance();

	std::string line;
	std::ifstream inputStream;

	inputStream.open(sUIFile);
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
			if (line == "[textures prefix]")
			{
				std::getline(inputStream, line);
				if (!line.empty())
				{
					tm->setWorkingDirectory(line);
				}
			}
			else if (line == "[textures]")
			{
				while (std::getline(inputStream, line))
				{
					if (line.empty())
					{
						// Finished loading textures
						break;
					}
					else
					{
						tm->loadTexture(line.substr(0, line.find_first_of(' ')), line.substr(line.find_first_of(' ') + 1, line.length()));
					}
				}
			}
			else if (line == "[audio prefix]")
			{
				std::getline(inputStream, line);
				if (!line.empty())
				{
					am->setWorkingDirectory(line);
				}
			}
			else if (line == "[audio]")
			{
				while (std::getline(inputStream, line))
				{
					if (line.empty())
					{
						// Finished loading audio
						break;
					}
					else
					{
						if (line.at(0) == 'm')
						{
							am->loadMusic(line.substr(1, line.find_first_of(' ')), line.substr(line.find_first_of(' ') + 1, line.length()));
						}
						else if (line.at(0) == 's')
						{
							am->loadSoundBuffer(line.substr(1, line.find_first_of(' ')), line.substr(line.find_first_of(' ') + 1, line.length()));
						}
					}
				}
			}
			else if (line == "[strings prefix]")
			{
				std::getline(inputStream, line);
				if (!line.empty())
				{
					sm->setWorkingDirectory(line);
				}
			}
			else if (line == "[strings]")
			{
				std::getline(inputStream, line);
				while (!line.empty())
				{
					sm->loadStrings(line);
					std::getline(inputStream, line);
				}
			}
			else if (line == "[fonts prefix]")
			{
				std::getline(inputStream, line);
				if (!line.empty())
				{
					fm->setWorkingDirectory(line);
				}
			}
			else if (line == "[fonts]")
			{
				std::getline(inputStream, line);
				while (!line.empty())
				{
					fm->loadFont(line.substr(0, line.find_first_of(' ')), line.substr(line.find_first_of(' ') + 1, line.size()));
					std::getline(inputStream, line);
				}
			}
			else if (line == "[components]")
			{
				// Add all objects as a UIComponent reference
				UIComponentBuilder builder;
				std::vector<std::string> strings;
				while (std::getline(inputStream, line))
				{
					if (line.empty())
					{
						// Finished loading UIComponents
						break;
					}
					else
					{
						if (line == "NEW")
						{
							while (line != "END")
							{
								std::getline(inputStream, line);
								strings.push_back(line);
							}
							m_pUIM->addUIComponentRef(builder.build(strings, bl));		
						}
					}
				}
			}
			else if (line == "[structure tree]")
			{
				std::string sParent;
				std::string sChild;
				while (std::getline(inputStream, line))
				{
					if (line.empty())
					{
						// Finished reading structure tree
						break;
					}
					else
					{
						sParent = line.substr(0, line.find_first_of('-'));
						sChild = line.substr(line.find_first_of('>') + 1, line.size());
						if (sParent == "ROOT" || sParent == "root")
						{
							m_pUIM->getRootComponent().addChild(m_pUIM->getUIComponentRef(sChild));
						}
						else
						{
							m_pUIM->getUIComponentRef(sParent)->addChild(m_pUIM->getUIComponentRef(sChild));
						}
					}
				}
			}
		}
	}
	m_pUIM->getRootComponent().repositionChildren();
	inputStream.close();
}

/**
Builds a UI using the given UI construction file. Loaded resources are stored in the relevant resource
containers (EG. TextureManager). Also gets the name of the component that will display the score and 
attaches the given button listener to any components that require one.

@param sUIFile The UIConstructor file.
@param bl A pointer to a button listener. 
@param sScoreComponent A reference to a string that will hold the name of the component that will display the score. */
void UIBuilder::buildUI(std::string sUIFile, UIButtonListener* bl, std::string& sScoreComponent)
{
	TextureManager* tm = TextureManager::getInstance();
	AudioManager* am = AudioManager::getInstance();
	StringsManager* sm = StringsManager::getInstance();
	FontManager* fm = FontManager::getInstance();

	std::string line;
	std::ifstream inputStream;

	inputStream.open(sUIFile);
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
			if (line == "[textures prefix]")
			{
				std::getline(inputStream, line);
				if (!line.empty())
				{
					tm->setWorkingDirectory(line);
				}
			}
			else if (line == "[textures]")
			{
				while (std::getline(inputStream, line))
				{
					if (line.empty())
					{
						// Finished loading textures
						break;
					}
					else
					{
						tm->loadTexture(line.substr(0, line.find_first_of(' ')), line.substr(line.find_first_of(' ') + 1, line.length()));
					}
				}
			}
			else if (line == "[audio prefix]")
			{
				std::getline(inputStream, line);
				if (!line.empty())
				{
					am->setWorkingDirectory(line);
				}
			}
			else if (line == "[audio]")
			{
				while (std::getline(inputStream, line))
				{
					if (line.empty())
					{
						// Finished loading audio
						break;
					}
					else
					{
						if (line.at(0) == 'm')
						{
							am->loadMusic(line.substr(1, line.find_first_of(' ')), line.substr(line.find_first_of(' ') + 1, line.length()));
						}
						else if (line.at(0) == 's')
						{
							am->loadSoundBuffer(line.substr(1, line.find_first_of(' ')), line.substr(line.find_first_of(' ') + 1, line.length()));
						}
					}
				}
			}
			else if (line == "[strings prefix]")
			{
				std::getline(inputStream, line);
				if (!line.empty())
				{
					sm->setWorkingDirectory(line);
				}
			}
			else if (line == "[strings]")
			{
				std::getline(inputStream, line);
				while (!line.empty())
				{
					sm->loadStrings(line);
					std::getline(inputStream, line);
				}
			}
			else if (line == "[fonts prefix]")
			{
				std::getline(inputStream, line);
				if (!line.empty())
				{
					fm->setWorkingDirectory(line);
				}
			}
			else if (line == "[fonts]")
			{
				std::getline(inputStream, line);
				while (!line.empty())
				{
					fm->loadFont(line.substr(0, line.find_first_of(' ')), line.substr(line.find_first_of(' ') + 1, line.size()));
					std::getline(inputStream, line);
				}
			}
			else if (line == "[components]")
			{
				// Add all objects as a UIComponent reference
				UIComponentBuilder builder;
				std::vector<std::string> strings;
				while (std::getline(inputStream, line))
				{
					if (line.empty())
					{
						// Finished loading UIComponents
						break;
					}
					else
					{
						if (line == "NEW")
						{
							while (line != "END")
							{
								std::getline(inputStream, line);
								strings.push_back(line);
							}
							m_pUIM->addUIComponentRef(builder.build(strings, bl));		
						}
					}
				}
			}
			else if (line == "[structure tree]")
			{
				std::string sParent;
				std::string sChild;
				while (std::getline(inputStream, line))
				{
					if (line.empty())
					{
						// Finished reading structure tree
						break;
					}
					else
					{
						sParent = line.substr(0, line.find_first_of('-'));
						sChild = line.substr(line.find_first_of('>') + 1, line.size());
						if (sParent == "ROOT" || sParent == "root")
						{
							m_pUIM->getRootComponent().addChild(m_pUIM->getUIComponentRef(sChild));
						}
						else
						{
							m_pUIM->getUIComponentRef(sParent)->addChild(m_pUIM->getUIComponentRef(sChild));
						}
					}
				}
			}
			else if (line == "[score component]")
			{
				std::getline(inputStream, line);
				sScoreComponent = line;
			}
		}
	}
	m_pUIM->getRootComponent().repositionChildren();
	inputStream.close();
}