#include "FontManager.h"

bool FontManager::bInstanceExists;
FontManager* FontManager::instance;

/**
Constructs a new FontManager object. A default working directory of "fonts/" is assigned. */
FontManager::FontManager()
{
	m_sFontsDirectory = "fonts/";
}

/**
Returns a pointer to the FontManager object. If the FontManager does not already exist, it is created and 
returned.

@return A pointer to the FontManager. */
FontManager* FontManager::getInstance()
{
	if (bInstanceExists)
	{
		return instance;
	}
	else
	{
		instance = new FontManager();
		bInstanceExists = true;
		return instance;
	}
}

/**
Sets the working directory. Calls to loadFont() will append the working directory to the beginning of
the file path.

@param sDirectory The directory to set the working directory to. */
void FontManager::setWorkingDirectory(std::string sDirectory)
{
	m_sFontsDirectory = sDirectory;
}

/**
Loads a font from the given file and stores it under the given key. Check the sf::Font documentation 
for information on supported font types.

Loading a font with a key that already exists will NOT overwrite existing fonts.

@see sf::Font
@param sKey The key to assign to the loaded font.
@param sFile The file to load the font from, extension included.
@return True if loading the font was successful. False otherwise. */
bool FontManager::loadFont(std::string sKey, std::string sFile)
{
	sf::Font f;

	// Avoid overwriting
	if (fontExists(sKey))
	{
		return false;
	}

	if (f.loadFromFile(m_sFontsDirectory + sFile))
	{
		m_fonts[sKey] = f;
		return true;
	}
	else
	{
		return false;
	}
}

/**
Returns true if a font with the given key exists.

@param sKey The key of the font to search for. 
@return True if a font with the given key exists. False otherwise. */
bool FontManager::fontExists(std::string sKey)
{
	if (m_fonts.find(sKey) != m_fonts.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
Clears a font, identified by key, from the FontManager. If no font with the given key exists, no action
is taken.

@param sKey The key of the font to clear. */
void FontManager::clearFont(std::string sKey)
{
	m_fonts.erase(sKey);
}

/**
Clears all fonts form the FontManager. */
void FontManager::clearFonts()
{
	m_fonts.clear();
}

/**
Returns a pointer to an sf::Font with the given key. 

@param sKey The key of the font to get.
@return A pointer to an sf::Font, or a nullptr if the key did not exist. */
sf::Font* FontManager::getFont(std::string sKey)
{
	return &m_fonts[sKey];
}