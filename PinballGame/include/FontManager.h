/**
The FontManager is a singleton font resource management class that stores sf::Font
objects in a convenient central location.

All font objects stored within the FontManager are assigned (by the programmer)
unique std::string keys that can be used to retrieve the object for as long as it 
is in memory.

As an sf::font is a fairly low-memory resource, loading all fonts that you intend to use 
upon launch and keeping them for the lifetime of the program is an advisable strategy.
*/

#ifndef FontManager_H
#define FontManager_H

#include <string>
#include <map>
#include <SFML/Graphics.hpp>

class FontManager
{
	public:
		static FontManager* getInstance();
		void setWorkingDirectory(std::string sDirectory);
		bool loadFont(std::string sKey, std::string sFile);
		bool fontExists(std::string sKey);
		void clearFont(std::string sKey);
		void clearFonts();
		sf::Font* getFont(std::string sKey);

	protected:

	private:
		static bool bInstanceExists;
		static FontManager* instance;
		std::string m_sFontsDirectory;
		std::map<std::string, sf::Font> m_fonts;

		FontManager();
};

#endif