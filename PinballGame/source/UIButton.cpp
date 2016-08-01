#include "UIButton.h"

/**
Constructs a UIButton with the given parameters.

@param sComponentName The name of the component.
@param fOffsetX The X axis offset from the parent component.
@param fOffsetY The Y axis offset from the parent component.
@param fWidth The width of the component.
@param fHeight The height of the component. */
UIButton::UIButton(std::string sComponentName, float fOffsetX, float fOffsetY, float fWidth, float fHeight) 
: UIComponent(sComponentName, fOffsetX, fOffsetY, fWidth, fHeight)
{
	m_Sprite.setPosition(getAbsolutePositionX(), getAbsolutePositionY());
	addComponentListener(this);
}

/**
Sets the texture. A button texture must be 200x210. 

@param texture The texture. */
void UIButton::setTexture(sf::Texture* texture)
{
	m_Sprite.setTexture(*texture);
	m_Sprite.setTextureRect(sf::IntRect(0, 0, getWidth(), getHeight()));
}

/**
Sets the sound that is played when this button is hovered over.

@param sound The sound. */
void UIButton::setSoundHover(sf::SoundBuffer* sound)
{
	m_SoundHover.setBuffer(*sound);
	m_SoundHover.setVolume(50);
}

/**
Sets the sound that is played when this button is clicked.

@param sound The sound. */
void UIButton::setSoundClicked(sf::SoundBuffer* sound)
{
	m_SoundClicked.setBuffer(*sound);
	m_SoundClicked.setVolume(50);
}

/**
Adds the given button listener to the button. 

@param bl The button listener. */
void UIButton::addButtonListener(UIButtonListener* bl)
{
	m_ButtonListeners.push_back(bl);
}

/**
Removes the given button listener from the button.

@param bl The button listener. */
void UIButton::removeButtonListener(UIButtonListener* bl)
{
	for (std::vector<UIButtonListener*>::iterator it = m_ButtonListeners.begin(); it != m_ButtonListeners.end(); ++it)
	{
		if ((*it) == bl)
		{
			m_ButtonListeners.erase(it);
			return;
		}
	}
}

/**
Launches a button depressed event to all button listeners registered on this button. If the button is not
active, no event is launched on this component or any child components. */
void UIButton::launchEvent_buttonDepressed()
{
	if (m_bIsActive)
	{
		for (std::vector<UIButtonListener*>::iterator it = m_ButtonListeners.begin(); it != m_ButtonListeners.end(); ++it)
		{
			(*it)->buttonDepressed(getName());
		}
	}
}

/**
Launches a button released event to all button listeners registered on this button. If the button is not
active, no event is launched on this component or any child components. Plays the 'clicked' sound if one
was present. */
void UIButton::launchEvent_buttonReleased()
{
	if (m_bIsActive)
	{
		m_SoundClicked.play();
		for (std::vector<UIButtonListener*>::iterator it = m_ButtonListeners.begin(); it != m_ButtonListeners.end(); ++it)
		{
			(*it)->buttonReleased(getName());	
		}
	}
}

/**
Simulates a depressed event on the button. */
void UIButton::simulateDepress()
{
	componentDepressed(getName());
}

/**
Simulates a released event on the button. */
void UIButton::simulateRelease()
{
	componentReleased(getName());
}

/**
This function should be called by any other function that would result in this component or any parent components
position being modified. */
void UIButton::positionUpdated()
{
	m_Sprite.setPosition(getAbsolutePositionX(), getAbsolutePositionY());
	repositionChildren();
}

/**
Draws the button to the target. If the component is set to invisible, the component and all of its child components
are not drawn. Consult the SFML Graphics documentation for further information. 

@see sf::RenderTarget
@see sf::RenderStates
@param target The target to draw to.
@param states The RenderStates. */
void UIButton::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_bIsVisible)
	{
		target.draw(m_Sprite);	
		for (std::map<std::string, UIComponent*>::const_iterator it = m_ChildComponents.begin(); it != m_ChildComponents.end(); ++it)
		{
			it->second->draw(target, states);
		}
	}
}

/**
This function is called by the component that this UIButton is listening to. The button texture is switched to the
depressed texture. A button depressed event is launched.

@param sComponentName The name of the component that was depressed. */
void UIButton::componentDepressed(std::string sComponentName)
{
	m_Sprite.setTextureRect(sf::IntRect(0, 140, getWidth(), getHeight()));
	launchEvent_buttonDepressed();
}

/**
This function is called by the component that this UIButton is listening to. The button texture is switched to either
the hovered or default state depending on the button is still being hovered over. A button released event is launched.

@param sComponentName The name of the component that was released. */
void UIButton::componentReleased(std::string sComponentName)
{
	if (isHovered())
	{
		m_Sprite.setTextureRect(sf::IntRect(0, 70, getWidth(), getHeight()));
	}
	else
	{
		m_Sprite.setTextureRect(sf::IntRect(0, 0, getWidth(), getHeight()));
	}
	launchEvent_buttonReleased();
}

/**
This function is called by the component that this UIButton is listening to. The button texture is switched to the
hovered state and the 'hovered' sound is played. 

@param sComponentName The name of the component that was hovered. */
void UIButton::componentHovered(std::string sComponentName)
{
	if (!isHovered())
	{
		m_SoundHover.play();
		m_Sprite.setTextureRect(sf::IntRect(0, 70, getWidth(), getHeight()));
	}
	else if (isHovered() && !isReleased())
	{
		m_Sprite.setTextureRect(sf::IntRect(0, 70, getWidth(), getHeight()));
	}
}

/**
This function is called by the component that this UIButton is listening to. The button texture is switched to the
unhovered state. 

@param sComponentName The name of the component that was unhovered. */
void UIButton::componentUnhovered(std::string sComponentName)
{
	m_Sprite.setTextureRect(sf::IntRect(0, 0, getWidth(), getHeight()));
}