#include "UIManager.h"

/**
Constructs a default UIManager. */
UIManager::UIManager() : m_RootComponent("ROOT", 0, 0, 1200, 800)
{
	for (int i = 0; i < 7; i++)
	{
		m_abLoadedUIs[i] = false;
	}
}

/**
Checks for hover and unhover events on all UIComponents. A hover event occurs when the mouse XY position
enters the collision box of a component whilst the component is unhovered. Similarly, an unhover events occurs
when the mouse XY position is not within the collision box of a component whilst it is hovered. 

@param mouseX The mouse X position.
@param mouseY The mouse Y position. */
void UIManager::checkHoverEvents(float mouseX, float mouseY)
{
	m_RootComponent.checkHoverEvents(mouseX, mouseY);
}

/**
Checks for release events on all UIComponents. A release event occurs when the mouse XY position
is within the collision box of a component whilst the component is depressed.

@param mouseX The mouse X position.
@param mouseY The mouse Y position. */
void UIManager::checkReleaseEvents(float mouseX, float mouseY)
{
	m_RootComponent.checkReleaseEvent(mouseX, mouseY);
}

/**
Checks for depressed events on all UIComponents. A depressed event occurs when the mouse XY position
is within the collision box of a component whilst the component is released.

@param mouseX The mouse X position.
@param mouseY The mouse Y position. */
void UIManager::checkDepressEvents(float mouseX, float mouseY)
{
	m_RootComponent.checkDepressEvent(mouseX, mouseY);
}

/**
Returns a reference to the root UIComponent.

@return A reference to the root UIComponent. */
UIFrame& UIManager::getRootComponent()
{
	return m_RootComponent;
}

/**
Adds a pointer to a UIComponent to the UIManager. The component is then retrievable using its component
name.

@param u The UIComponent to add. */
void UIManager::addUIComponentRef(UIComponent* u)
{
	m_UIComponents[u->getName()] = u;
}

/**
Returns a pointer to a UIComponent with the given name.

@param sComponentName The name of the UIComponent to get.
@return A pointer to a UIComponent with the given name. */
UIComponent* UIManager::getUIComponentRef(std::string sComponentName)
{
	return m_UIComponents[sComponentName];
}

/**
Removes a UIComponent pointer with the given name from the UIManager.

@param sComponentName The name of the UIComponent to remove. */
void UIManager::removeUIComponentRef(std::string sComponentName)
{
	m_UIComponents.erase(sComponentName);
}

/**
Returns true if the given UI is loaded and resides in memory.

@param ui The UI to check.
@return True if the given UI is loaded. */
bool UIManager::getUILoaded(UIs ui)
{
	return m_abLoadedUIs[ui];
}

/**
Sets the loaded flag for the given UI.

@param ui The UI to set.
@param bIsLoaded True if the UI is loaded. False otherwise. */
void UIManager::setUILoaded(UIs ui, bool bIsLoaded)
{
	m_abLoadedUIs[ui] = bIsLoaded;
}