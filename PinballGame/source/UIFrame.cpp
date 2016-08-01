#include "UIFrame.h"

/**
Constructs a default UIFrame. */
UIFrame::UIFrame() : UIComponent("Unnamed", 0, 0, 200, 50)
{
}

/**
Constructs a UIFrame with the given parameters.

@param sComponentName The name of the component.
@param fOffsetX The X axis offset from the parent component.
@param fOffsetY The Y axis offset from the parent component.
@param fWidth The width of the component.
@param fHeight The height of the component. */
UIFrame::UIFrame(std::string sComponentName, float fOffsetX, float fOffsetY, float fWidth, float fHeight) 
: UIComponent(sComponentName, fOffsetX, fOffsetY, fWidth, fHeight)
{
}

/**
This function should be called by any other function that would result in this component or any parent components
position being modified. */
void UIFrame::positionUpdated()
{
	repositionChildren();
}

/**
Drawing a frame is essentially a dummy method that passes on the draw call to its child components. The frame itself has no drawable text or 
image. If the component is set to invisible, the component and all of its child components are not drawn. Consult the SFML Graphics 
documentation for further information. 

@see sf::RenderTarget
@see sf::RenderStates
@param target The target to draw to.
@param states The RenderStates. */
void UIFrame::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (m_bIsVisible)
	{
		for (std::map<std::string, UIComponent*>::const_iterator it = m_ChildComponents.begin(); it != m_ChildComponents.end(); ++it)
		{
			it->second->draw(target, states);
		}
	}
}