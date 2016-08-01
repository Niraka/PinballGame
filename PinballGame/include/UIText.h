/**
A UIText is an extension of the UIComponent class to provide functionality for drawing
text on the component.

The text is highly configurable, allowing for changes to the text itself, the colour, the 
font and more.
*/

#ifndef UIText_H
#define UIText_H

#include "UIComponent.h"

class UIText : public UIComponent
{
	public:
		enum Alignment {LEFT, CENTRE, RIGHT};

		UIText(std::string sComponentName, float fOffsetX, float fOffsetY, float fWidth, float fHeight);
		
		void setFontSize(int iSize);
		void setFont(sf::Font* font);
		void setColor(sf::Color color);
		void setString(sf::String& str);
		void setString(std::string* str);
		void setAlignment(Alignment alignment);

		virtual void positionUpdated();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:

	private:
		Alignment m_Alignment;
		sf::Text m_Text;
		UIText();
};

#endif