/**
A UIBuilder is a text file interpretter that attempts to build and store a user interface from the specification outlined
in a UI configuration file.

As UIComponents are mostly used to display some sort of information to the player, the UIBuilder provides functionality for
loading any resources required by the interface under construction before it is constructed. The resources are stored in the
same way that any other resource in the program is stored - in the relevant singleton resource manager.

Determining the component to build and the parameters to supply that component with is done by reading a series of vectors of
strings and then looking for matches against expected parameters. The expected parameters are outlined in any UI configuration
files comment section and should be strictly adhered to. In most situations, an incomplete UIComponent is going to cause the 
game to crash.
*/


#ifndef UIBuilder_H
#define UIBuilder_H

#include "AudioManager.h"
#include "TextureManager.h"
#include "StringsManager.h"
#include "FontManager.h"
#include "UIManager.h"
#include "UIComponentBuilder.h"
#include <string>
#include <istream>
#include <fstream>

class UIBuilder
{
	public:
		UIBuilder(UIManager& uim);

		void buildUI(std::string sUIFile, UIButtonListener* bl);
		void buildUI(std::string sUIFile, UIButtonListener* bl, std::string& sScoreComponent);

	protected:
	private:
		UIManager* m_pUIM;
};

#endif