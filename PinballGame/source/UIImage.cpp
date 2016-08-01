#include "UIImage.h"

/**
Constructs a default UIImage. */
UIImage::UIImage() : UIComponent("Unnamed", 0, 0, 200, 50)
{
}

/**
Constructs a UIImage with the given parameters.

@param sComponentName The name of the component.
@param fOffsetX The X axis offset from the parent component.
@param fOffsetY The Y axis offset from the parent component.
@param fWidth The width of the component.
@param fHeight The height of the component. */
UIImage::UIImage(std::string sComponentName, float fOffsetX, float fOffsetY, float fWidth, float fHeight) 
: UIComponent(sComponentName, fOffsetX, fOffsetY, fWidth, fHeight)
{
}

/**
Sets the texture.

@param texture The texture. */
void UIImage::setTexture(sf::Texture* texture)
{
	m_Sprite.setTexture(*texture);

	// Should the texture fail to load, this line prevents a division-by-zero crash.
	if (texture->getSize().x != 0 && texture->getSize().y != 0)
	{
		// Scales the texture to the size of the image
		m_Sprite.setScale(getWidth() / texture->getSize().x, getHeight() / texture->getSize().y);
	}
}

/**
This function should be called by any other function that would result in this component or any parent components
position being modified. */
void UIImage::positionUpdated()
{
	m_Sprite.setPosition(getAbsolutePositionX(), getAbsolutePositionY());
	repositionChildren();
}

/**
Draws the image to the target. If the component is set to invisible, the component and all of its child components are 
not drawn. Consult the SFML Graphics documentation for further information. 

@see sf::RenderTarget
@see sf::RenderStates
@param target The target to draw to.
@param states The RenderStates. */
void UIImage::draw(sf::RenderTarget& target, sf::RenderStates states) const
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


