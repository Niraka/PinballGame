/**
The TextureManager is a singleton texture resource management class that stores sf::Texture
objects in a convenient central location.

All texture objects stored within the TextureManager are assigned (by the programmer)
unique std::string keys that can be used to retrieve the object for as long as it is
in memory.

Note that both storing large numbers of sf::Texture objects and loading textures in to memory
constantly are wasteful behaviours.
*/

#ifndef TextureManager_H
#define TextureManager_H

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class TextureManager
{
	public:
		static TextureManager* getInstance();
		void setWorkingDirectory(std::string sDirectory);
		bool loadTexture(std::string sKey, std::string sFile);
		bool textureExists(std::string sKey);
		void clearTexture(std::string sKey);
		void clearTextures();
		sf::Texture* getTexture(std::string sKey);

	protected:
	
	private:
		static bool bInstanceExists;
		static TextureManager* instance;
		std::string m_sTexturesDirectory;
		std::map<std::string, sf::Texture> m_textures;	

		TextureManager();
};

#endif