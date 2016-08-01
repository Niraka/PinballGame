#include "MapBuilder.h"

/**
Constructs a default MapBuilder. */
MapBuilder::MapBuilder()
{
}

/**
Constructs a Map by interpreting the data found in the given map file. The map file has sections for loading
image and audio resources alongside GameObject data. 

@param sFile The map file to load. Includes extension and full relative path. 
@param gameObjects A reference to a vector of pointers to GameObjects to store the constructed GameObjects in. 
@param mm A reference to a MaterialsManager that will store loaded materials. */
void MapBuilder::buildMap(std::string sFile, std::vector<GameObject*>& gameObjects, MaterialsManager& mm)
{
	TextureManager* tm = TextureManager::getInstance();
	AudioManager* am = AudioManager::getInstance();

	std::string sLine;
	std::ifstream fileStream;

	fileStream.open(sFile);
	while (std::getline(fileStream, sLine))
	{
		// Skip the line if it is empty
		if (sLine.empty())
		{
			continue;
		}
		// Skip the line if it begins with a #, space, or new line
		if (sLine.at(0) == '#' || sLine.at(0) == '/n' || sLine.at(0) == ' ')
		{
			continue;
		}
		else
		{
			// Find the first section token (EG: "[textures]") to determine the builder to use.
			if (sLine == "[textures prefix]")
			{
				std::getline(fileStream, sLine);
				if (sLine.empty())
				{
					// No texture directory provided - usually an error
					break;
				}
				else
				{
					tm->setWorkingDirectory(sLine);
				}
			}
			else if (sLine == "[textures]")
			{
				while (std::getline(fileStream, sLine))
				{
					if (sLine.empty())
					{
						// Finished loading textures
						break;
					}
					else
					{					
						tm->loadTexture(sLine.substr(0, sLine.find_first_of(' ')), sLine.substr(sLine.find_first_of(' ') + 1, sLine.length()));
					}
				}
			}
			else if (sLine == "[audio prefix]")
			{
				std::getline(fileStream, sLine);
				if (sLine.empty())
				{
					// No audio directory provided - usually an error
					break;
				}
				else
				{
					am->setWorkingDirectory(sLine);
				}
			}			
			else if (sLine == "[audio]")
			{
				while (std::getline(fileStream, sLine))
				{
					if (sLine.empty())
					{
						// Finished loading audio
						break;
					}
					else
					{
						if (sLine.at(0) == 'm')
						{
							am->loadMusic(sLine.substr(1, sLine.find_first_of(' ')), sLine.substr(sLine.find_first_of(' ') + 1, sLine.length()));
						}
						else if (sLine.at(0) == 's')
						{
							am->loadSoundBuffer(sLine.substr(1, sLine.find_first_of(' ')), sLine.substr(sLine.find_first_of(' ') + 1, sLine.length()));
						}
					}
				}
			}		
			else if (sLine == "[materials]")
			{	
				std::vector<std::string> strings;
				MaterialBuilder builder;

				while (std::getline(fileStream, sLine))
				{
					if (sLine.empty())
					{
						// Finished loading materials
						break;
					}
					else
					{
						if (sLine == "NEW")
						{
							while (sLine != "END")
							{
								std::getline(fileStream, sLine);
								strings.push_back(sLine);
							}
							builder.buildMaterial(strings, mm);		
						}
					}
				}
			}
			else if (sLine == "[gameobjects]")
			{
				std::vector<std::string> strings;
				GameObjectBuilder builder(mm);
				while (std::getline(fileStream, sLine))
				{
					if (sLine.empty())
					{
						// Finished loading game objects
						break;
					}
					else
					{
						if (sLine == "NEW")
						{
							while (sLine != "END")
							{
								std::getline(fileStream, sLine);
								strings.push_back(sLine);
							}
							gameObjects.push_back(builder.build(strings));
							strings.clear();
						}
					}
				}
			}
			else if (sLine == "[flippers]")
			{
				std::vector<std::string> strings;
				FlipperBuilder builder(mm);
				while (std::getline(fileStream, sLine))
				{
					if (sLine.empty())
					{
						// Finished loading flippers
						break;
					}
					else
					{
						if (sLine == "NEW")
						{
							while (sLine != "END")
							{
								std::getline(fileStream, sLine);
								strings.push_back(sLine);
							}
							gameObjects.push_back(builder.build(strings));
							strings.clear();
						}
					}
				}
			}
		}
	}

	// Finished - close the file stream
	fileStream.close();
}