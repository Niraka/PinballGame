#include "UIComponent.h"

/**
Constructs a UIComponent with the given parameters.

@param sComponentName The name of the component.
@param fOffsetX The X axis offset from the parent component.
@param fOffsetY The Y axis offset from the parent component.
@param fWidth The width of the component.
@param fHeight The height of the component. */
UIComponent::UIComponent(std::string sComponentName, float fOffsetX, float fOffsetY, float fWidth, float fHeight)
{
	m_bIsHovered = false;
	m_bIsReleased = true;
	m_sComponentName = sComponentName;
	m_fOffsetX = fOffsetX;
	m_fOffsetY = fOffsetY;
	m_fWidth = fWidth;
	m_fHeight = fHeight;
	m_bIsActive = true;
	m_bIsVisible = true;
}		

/**
Sets the active flag for this UIComponent. A component must be active to launch hover and click events. All child 
components inherit the flag if it is set to false.

@param bActive True if the component is active. */
void UIComponent::setActive(bool bActive)
{
	m_bIsActive = bActive;
}

/**
Sets the visibility flag for this UIComponent. A component must be visible for it to be drawn. All child components inherit
the flag if it is set to false.

@param bVisible True if the component is visible. */
void UIComponent::setVisible(bool bVisible)
{
	m_bIsVisible = bVisible;
}

/**
Returns true if the component is active.

@return True if the component is active. */
bool UIComponent::isActive()
{
	return m_bIsActive;
}

/**
Returns true if the component is visible.

@return True if the component is visible. */
bool UIComponent::isVisible()
{
	return m_bIsVisible;
}

/**
Sets the size of the UIComponent.

@param fWidth The width.
@param fHeight The height. */
void UIComponent::setSize(float fWidth, float fHeight)
{
	m_fWidth = fWidth;
	m_fHeight = fHeight;
}

/**
Sets the width of the UIComponent.

@param fWidth The width. */
void UIComponent::setWidth(float fWidth)
{
	m_fWidth = fWidth;
}

/**
Sets the height of the UIComponent.

@param fHeight The height. */
void UIComponent::setHeight(float fHeight)
{
	m_fHeight = fHeight;
}

/**
Returns the width of the UIComponent.

@return The width. */
float UIComponent::getWidth() const
{
	return m_fWidth;
}

/**
Returns the height of the UIComponent.

@return The height. */
float UIComponent::getHeight() const
{
	return m_fHeight;
}

/**
Sets the X axis offset of this component. Child components (if any) are repositioned accordingly. 

@param fOffsetX The X offset. */
void UIComponent::setOffsetX(float fOffsetX)
{
	m_fOffsetX = fOffsetX;
	positionUpdated();
}

/**
Sets the Y axis offset of this component. Child components (if any) are repositioned accordingly. 

@param fOffsetY The Y offset. */
void UIComponent::setOffsetY(float fOffsetY)
{
	m_fOffsetY = fOffsetY;
	positionUpdated();
}

/**
Returns the x-axis offset of this component. 

@return The X offset. */
float UIComponent::getOffsetX() const
{
	return m_fOffsetX;
}

/**
Returns the y-axis offset of this component. 

@return The Y offset. */
float UIComponent::getOffsetY() const
{
	return m_fOffsetY;
}

/**
Returns true if this component has a parent component. False otherwise. 

@return True if this component has a parent component. */
bool UIComponent::hasParent() const
{
	if (m_Parent == nullptr)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/**
Returns a pointer to the parent component of this component. A nullptr will be returned if no parent
component existed. 

@return A pointer to the parent component. */
UIComponent* UIComponent::getParent() const
{
	return m_Parent;
}

/**
Returns the name of the component. 

@return The name of the component. */
std::string UIComponent::getName() const
{
	return m_sComponentName;
}

/**
Sets the parent component of this component. 

@param UIComponent The parent UIComponent. */
void UIComponent::setParent(UIComponent* UIComponent)
{
	m_Parent = UIComponent;
}

/**
Adds a component to this component as a child. If the child component already has a parent, the existing
parent is removed. 

@param UIComponent The child UIComponent. */
void UIComponent::addChild(UIComponent* UIComponent)
{
	// Unhook existing parent
	if (UIComponent->hasParent())
	{
		UIComponent->getParent()->removeChild(UIComponent->getName()); 
	}
	// Add
	UIComponent->setParent(this);
	m_ChildComponents[UIComponent->getName()] = UIComponent;
	repositionChildren();
}

/**
Removes a child component, identified by name, from this component. 

@param sComponentName The name of the child component to remove. */
void UIComponent::removeChild(std::string sComponentName)
{
	std::map<std::string, UIComponent*>::iterator it = m_ChildComponents.find(sComponentName);
	if (it != m_ChildComponents.end())
	{
		m_ChildComponents[sComponentName]->setParent(nullptr);
		m_ChildComponents.erase(sComponentName);
		return;
	}
}

/**
Returns the X axis position of the component relative to the root component. Note that the root component is defined
as the first component encountered that does not have a parent. 

@return The absolute X position. */
float UIComponent::getAbsolutePositionX()
{
	if (hasParent())
	{
		return m_Parent->getAbsolutePositionX() + m_fOffsetX;
	}
	else
	{
		return m_fOffsetX;
	}
}

/**
Returns the Y axis position of the component relative to the root component. Note that the root component is defined
as the first component encountered that does not have a parent. 

@return The absolute Y position. */
float UIComponent::getAbsolutePositionY()
{
	if (hasParent())
	{
		return m_Parent->getAbsolutePositionY() + m_fOffsetY;
	}
	else
	{
		return m_fOffsetY;
	}
}

/**
Repositions all child-components to maintain their correct offsets from this component. This function should be called
every time this component moves. */
void UIComponent::repositionChildren()
{
	for (std::map<std::string, UIComponent*>::iterator it = m_ChildComponents.begin(); it != m_ChildComponents.end(); ++it)
	{
		it->second->positionUpdated();
	}
}

/**
Checks whether a release event should be launched on this UIComponent. If the component is not active, no event
will be launched.

@param mouseX The X position of the mouse.
@param mouseY The Y position of the mouse. */
void UIComponent::checkReleaseEvent(float mouseX, float mouseY)
{	
	// Return if the component is not active.
	if (!m_bIsActive)
	{
		return;
	}

	if (!m_bIsReleased && checkCollision(mouseX, mouseY))
	{
		launchEvent_componentReleased();
		m_bIsReleased = true;
	}

	// Continue on to child components.
	for (std::map<std::string, UIComponent*>::iterator it = m_ChildComponents.begin(); it != m_ChildComponents.end(); ++it)
	{
		it->second->checkReleaseEvent(mouseX, mouseY);
	}
}

/**
Checks whether a depress event should be launched on this UIComponent. If the component is not active, no event
will be launched.

@param mouseX The X position of the mouse.
@param mouseY The Y position of the mouse. */
void UIComponent::checkDepressEvent(float mouseX, float mouseY)
{	
	// Return if the component is not active.
	if (!m_bIsActive)
	{
		return;
	}

	if (m_bIsReleased && checkCollision(mouseX, mouseY))
	{
		launchEvent_componentDepressed();
		m_bIsReleased = false;
	}

	// Continue on to child components.
	for (std::map<std::string, UIComponent*>::iterator it = m_ChildComponents.begin(); it != m_ChildComponents.end(); ++it)
	{
		it->second->checkDepressEvent(mouseX, mouseY);
	}
}

/**
Checks whether a hover or unhover event should be launched on this UIComponent. If the component is not active, 
no event will be launched.

@param mouseX The X position of the mouse.
@param mouseY The Y position of the mouse. */
void UIComponent::checkHoverEvents(float mouseX, float mouseY)
{
	// Return if the component is not active.
	if (!m_bIsActive)
	{
		return;
	}

	bool isColliding = checkCollision(mouseX, mouseY);
	
	// Hover event checks
	if (m_bIsHovered && !isColliding)
	{
		launchEvent_componentUnhovered();
		m_bIsHovered = false;
	}
	else if (!m_bIsHovered && isColliding)
	{
		launchEvent_componentHovered();
		m_bIsHovered = true;
	}

	// Continue on to child components.
	for (std::map<std::string, UIComponent*>::iterator it = m_ChildComponents.begin(); it != m_ChildComponents.end(); ++it)
	{
		it->second->checkHoverEvents(mouseX, mouseY);
	}
}

/**
Launches a component hovered event to all registered UIComponentListeners. */
void UIComponent::launchEvent_componentHovered()
{
	for (std::vector<UIComponentListener*>::iterator it = m_ComponentListeners.begin(); it != m_ComponentListeners.end(); ++it)
	{
		(*it)->componentHovered(m_sComponentName);
	}
}

/**
Launches a component unhovered event to all registered UIComponentListeners. */
void UIComponent::launchEvent_componentUnhovered()
{
	for (std::vector<UIComponentListener*>::iterator it = m_ComponentListeners.begin(); it != m_ComponentListeners.end(); ++it)
	{
		(*it)->componentUnhovered(m_sComponentName);
	}
}

/**
Launches a component released event to all registered UIComponentListeners. */
void UIComponent::launchEvent_componentReleased()
{
	for (std::vector<UIComponentListener*>::iterator it = m_ComponentListeners.begin(); it != m_ComponentListeners.end(); ++it)
	{
		(*it)->componentReleased(m_sComponentName);
	}
}

/**
Launches a component depressed event to all registered UIComponentListeners. */
void UIComponent::launchEvent_componentDepressed()
{
	for (std::vector<UIComponentListener*>::iterator it = m_ComponentListeners.begin(); it != m_ComponentListeners.end(); ++it)
	{
		(*it)->componentDepressed(m_sComponentName);
	}
}

/**
Checks whether the given XY position falls within the bounds of the UIComponent.

@param mouseX The X position of the mouse.
@param mouseY The Y position of the mouse.
@return True if the XY position was within the bounds of the UIComponent. */
bool UIComponent::checkCollision(float mouseX, float mouseY)
{
	float absX = getAbsolutePositionX();
	if (mouseX >= absX && mouseX <= absX + m_fWidth)
	{
		float absY = getAbsolutePositionY();
		if (mouseY >= absY && mouseY <= absY + m_fHeight)
		{
			return true;
		}
	}
	return false;
}

/**
Returns true if the component is being hovered over.

@return True if the component is being hovered over. */
bool UIComponent::isHovered() const
{
	return m_bIsHovered;
}

/**
Returns true if the component is released.

@return True if the component is released. */
bool UIComponent::isReleased() const
{
	return m_bIsReleased;
}

/**
Adds a UIComponentListener to this UIComponent.

@param l The listener. */
void UIComponent::addComponentListener(UIComponentListener* l)
{
	m_ComponentListeners.push_back(l);
}

/**
Removes a UIComponentListener from this UIComponent.

@param l The listener. */
void UIComponent::removeComponentListener(UIComponentListener* l)
{
	for (std::vector<UIComponentListener*>::iterator it = m_ComponentListeners.begin(); it != m_ComponentListeners.end(); ++it)
	{
		if (*it == l)
		{
			m_ComponentListeners.erase(it);
		}
	}
}