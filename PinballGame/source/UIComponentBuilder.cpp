#include "UIComponentBuilder.h"

/**
Constructs a default UIComponentBuilder. */
UIComponentBuilder::UIComponentBuilder()
{
	m_tm = TextureManager::getInstance();
	m_am = AudioManager::getInstance();
	m_sm = StringsManager::getInstance();
	m_fm = FontManager::getInstance();
}

/**
Builds a user interface component (EG: UIText, UIButton, UIImage..) using the vector of parameters and stores
it on the heap. Returns a pointer to the UIComponent base class of the component. This function is unstable 
when presented "bad" or missing parameters.

@param strings A vector of strings containing the parameters for building the component.
@param bl A pointer to a button listener to give to any components that require one.
@return A pointer to the UIComponent base class of the component. */
UIComponent* UIComponentBuilder::build(std::vector<std::string> strings, UIButtonListener* bl)
{
	// Parsing temporary values
	std::string sKey;
	std::string sValue;
	int equalsChar = 0;

	// Parse only minimum required values in first pass. A small optimisation on an otherwise fairly sluggish
	// piece of code.
	std::string sName;
	float fXOffset;
	float fYOffset;
	float fWidth;
	float fHeight;
	std::string sType;

	for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); ++it)
	{		
		// Split the line in to key and value components
		equalsChar = (*it).find_first_of('=');
		sKey = (*it).substr(0, equalsChar);
		sValue = (*it).substr(equalsChar + 1, (*it).length());

		if (sKey == "" | sValue == "")
		{
			continue;
		}
		
		if (sKey == "sName")
		{
			sName = sValue;
		}
		else if (sKey == "fXOffset")
		{
			fXOffset = stof(sValue);
		}
		else if (sKey == "fYOffset")
		{
			fYOffset = stof(sValue);
		}
		else if (sKey == "fWidth")
		{
			fWidth = stof(sValue);
		}
		else if (sKey == "fHeight")
		{
			fHeight = stof(sValue);
		}
		else if (sKey == "sType")
		{
			sType = sValue;
		}
	}

	// Create the relevant component and parse the required property set
	if (sType == "frame")
	{
		 UIFrame* frame = new UIFrame(sName, fXOffset, fYOffset, fWidth, fHeight);
		 return frame;
	}
	else if (sType == "image")
	{
		// Parse image specific properties
		std::string sTexture;

		for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); ++it)
		{		
			// Split the line in to key and value components
			equalsChar = (*it).find_first_of('=');
			sKey = (*it).substr(0, equalsChar);
			sValue = (*it).substr(equalsChar + 1, (*it).length());

			if (sKey == "" | sValue == "")
			{
				continue;
			}
		
			if (sKey == "sTexture")
			{
				sTexture = sValue;
			}
		}

		UIImage* image = new UIImage(sName, fXOffset, fYOffset, fWidth, fHeight);
		image->setTexture(m_tm->getTexture(sTexture));
		return image;
	}
	else if (sType == "text")
	{
		// Parse text specific properties
		sf::Color color;
		std::string sString;
		UIText::Alignment alignment;
		int iFontSize;
		std::string sFont;
				
		for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); ++it)
		{		
			// Split the line in to key and value components
			equalsChar = (*it).find_first_of('=');
			sKey = (*it).substr(0, equalsChar);
			sValue = (*it).substr(equalsChar + 1, (*it).length());

			if (sKey == "" | sValue == "")
			{
				continue;
			}
		
			if (sKey == "sColor")
			{
				if (sValue == "cyan") {color = sf::Color::Cyan;}
				else if (sValue == "blue") {color = sf::Color::Blue;}
				else if (sValue == "black") {color = sf::Color::Black;}
				else if (sValue == "red") {color = sf::Color::Red;}
				else if (sValue == "green") {color = sf::Color::Green;}
				else if (sValue == "yellow") {color = sf::Color::Yellow;}
				else if (sValue == "magenta") {color = sf::Color::Magenta; }
				else if (sValue == "white") {color = sf::Color::White;}
			}
			else if (sKey == "sString")
			{
				sString = sValue;
			}
			else if (sKey == "sAlignment")
			{
				if (sValue == "left")
				{
					alignment = UIText::Alignment::LEFT;
				}
				else if (sValue == "centre")
				{
					alignment = UIText::Alignment::CENTRE;
				}
				else if (sValue == "right")
				{
					alignment = UIText::Alignment::RIGHT;
				}
			}
			else if (sKey == "iFontSize")
			{
				iFontSize = stoi(sValue);
			}
			else if (sKey == "sFont")
			{
				sFont = sValue;
			}
		}

		UIText* text = new UIText(sName, fXOffset, fYOffset, fWidth, fHeight);
		text->setColor(color);
		text->setString(m_sm->getString(sString));
		text->setFontSize(iFontSize);
		text->setFont(m_fm->getFont(sFont));
		text->setAlignment(alignment);
		return text;
	}
	else if (sType == "button")
	{
		// Parse button-specific properties
		std::string sTexture;
		std::string sSoundHover;
		std::string sSoundClick;
		bool bHasListener;

		for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); ++it)
		{		
			// Split the line in to key and value components
			equalsChar = (*it).find_first_of('=');
			sKey = (*it).substr(0, equalsChar);
			sValue = (*it).substr(equalsChar + 1, (*it).length());

			if (sKey == "" | sValue == "")
			{
				continue;
			}
		
			if (sKey == "sTexture")
			{
				sTexture = sValue;
			}
			else if (sKey == "sSoundHover")
			{
				sSoundHover = sValue;
			}
			else if (sKey == "sSoundClick")
			{
				sSoundClick = sValue;
			}
			else if (sKey == "bHasListener")
			{
				if (sValue == "true")
				{
					bHasListener = true;
				}
				else
				{
					bHasListener = false;
				}
			}
		}

		UIButton* button = new UIButton(sName, fXOffset, fYOffset, fWidth, fHeight);
		button->setTexture(m_tm->getTexture(sTexture));
		button->setSoundClicked(m_am->getSoundBuffer(sSoundClick));
		button->setSoundHover(m_am->getSoundBuffer(sSoundHover));
		if (bHasListener)
		{
			button->addButtonListener(bl);
		}
		return button;
	}
	else
	{
		// This line is only here to keep the compiler happy. If it is ever reached, it is always an error in the user
		// interface configuration file.
		return new UIFrame("frameError", 0, 0, 0, 0);
	}
}