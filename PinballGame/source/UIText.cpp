#include "UIText.h"

/**
Constructs a default UIText. */
UIText::UIText() : UIComponent("Unnamed", 0, 0, 200, 50)
{
}

/**
Constructs a UIText component with the given parameters.

@param sComponentName The name of the component.
@param fOffsetX The X axis offset from the parent component.
@param fOffsetY The Y axis offset from the parent component.
@param fWidth The width of the component.
@param fHeight The height of the component. */
UIText::UIText(std::string sComponentName, float fOffsetX, float fOffsetY, float fWidth, float fHeight) 
: UIComponent(sComponentName, fOffsetX, fOffsetY, fWidth, fHeight)
{
	m_Alignment = Alignment::LEFT;
	m_Text.setColor(sf::Color::Black);
	m_Text.setString("");
}

/**
Sets the font.

@param font The font. */
void UIText::setFont(sf::Font* font)
{
	m_Text.setFont(*font);
	positionUpdated();
}

/**
Sets the color.

@param color The color. */
void UIText::setColor(sf::Color color)
{
	m_Text.setColor(color);
}

/**
Sets the string. All ` characters within the string are replaced with a new-line character.

@param str The string. */
void UIText::setString(std::string* str)
{
	sf::String s = *str;
	int i;
	while ((i = s.find('`')) != sf::String::InvalidPos)
	{
		s.erase(i);
		s.insert(i, "\n");
	}
	m_Text.setString(s);
}

/**
Sets the string. All ` characters within the string are replaced with a new-line character.

@param str The string. */
void UIText::setString(sf::String& str)
{
	int i;
	while ((i = str.find('`')) != sf::String::InvalidPos)
	{
		str.erase(i);
		str.insert(i, "\n");
	}
	m_Text.setString(str);
}

/**
Sets the size of the font. 

@param iSize The font size. */
void UIText::setFontSize(int iSize)
{
	m_Text.setCharacterSize(iSize);
}

/**
Sets the alignment of the text. This will modify where the component is positioned. 

@param alignment The alignment. */
void UIText::setAlignment(Alignment alignment)
{
	m_Alignment = alignment;
	positionUpdated();
}

/**
This function should be called by any other function that would result in this component or any parent components
position being modified. */
void UIText::positionUpdated()
{
	switch (m_Alignment)
	{
		case LEFT:
			m_Text.setPosition(getAbsolutePositionX(), getAbsolutePositionY());
			break;
		case CENTRE:
			m_Text.setPosition(getAbsolutePositionX() - (m_Text.getLocalBounds().width / 2), getAbsolutePositionY());
			break;
		case RIGHT:
			m_Text.setPosition(getAbsolutePositionX() - m_Text.getLocalBounds().width, getAbsolutePositionY());
			break;
		default:
			m_Text.setPosition(getAbsolutePositionX(), getAbsolutePositionY());
	}
	repositionChildren();
}

/**
Draws the text to the target. If the component is set to invisible, the component and all of its child components
are not drawn. Consult the SFML Graphics documentation for further information. 

@see sf::RenderTarget
@see sf::RenderStates
@param target The target to draw to.
@param states The RenderStates. */
void UIText::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_bIsVisible)
	{
		target.draw(m_Text);
		for (std::map<std::string, UIComponent*>::const_iterator it = m_ChildComponents.begin(); it != m_ChildComponents.end(); ++it)
		{
			it->second->draw(target, states);
		}
	}
}