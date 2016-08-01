#include "TextureManager.h"

bool TextureManager::bInstanceExists;
TextureManager* TextureManager::instance;

/**
Constructs a new TextureManager object. A default working directory of "textures/" is assigned. */
TextureManager::TextureManager()
{
	m_sTexturesDirectory = "textures/";
}

/**
Returns a pointer to the TextureManager object. If the TextureManager does not already exist, it is created
and returned.

@return A pointer to the TextureManager. */
TextureManager* TextureManager::getInstance()
{
	if (bInstanceExists)
	{
		return instance;
	}
	else
	{
		instance = new TextureManager();
		bInstanceExists = true;
		return instance;
	}
}

/**
Sets the working directory. Calls to loadTexture() will append the working directory to the beginning of
the file path.

@param sDirectory The directory to set the working directory to. */
void TextureManager::setWorkingDirectory(std::string sDirectory)
{
	m_sTexturesDirectory = sDirectory;
}

/**
Loads a Texture from from the given image file and stores it under the given key. Check the sf::Texture documentation
for information on supported image types.

Loading a texture with a key that already exists will NOT overwrite existing textures. 

@see sf::Texture
@param sKey The key to assign to the loaded texture.
@param sFile The file to load the image from, extension included. 
@return True if loading the texture was successful. False otherwise. */
bool TextureManager::loadTexture(std::string sKey, std::string sFile)
{
	sf::Texture tex;
	if (tex.loadFromFile(m_sTexturesDirectory + sFile))
	{
		m_textures[sKey] = tex;
		return true;
	}
	else
	{
		return false;
	}
}

/**
Returns true if a texture with the given key exists. 

@param sKey The key of the texture to search for. 
@return True if a texture with the given key exists. False otherwise. */
bool TextureManager::textureExists(std::string sKey)
{
	if (m_textures.find(sKey) != m_textures.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
Clears a texture, identified by key, from the TextureManager. If no texture with the given key exists, no
action is taken.

@param sKey The key of the texture to clear. */
void TextureManager::clearTexture(std::string sKey)
{
	m_textures.erase(sKey);
}

/**
Clears all textures from the TextureManager. */
void TextureManager::clearTextures()
{
	m_textures.clear();
}

/**
Returns a pointer to an sf::Texture with the given key.

@param sKey The key of the texture to get.
@return A pointer to an sf::Texture, or a nullptr if the key did not exist. */
sf::Texture* TextureManager::getTexture(std::string sKey)
{
	return &m_textures[sKey];
}