#include "UIComponentListener.h"

/**
Constructs a default UIComponentListener. */
UIComponentListener::UIComponentListener()
{
}

/**
This function should only be called by the component that this component listener is registered with when the 
component is depressed.

@param sComponentName The name of the component. */
void UIComponentListener::componentDepressed(std::string sComponentName)
{
}

/**
This function should only be called by the component that this component listener is registered with when the 
component is released.

@param sComponentName The name of the component. */
void UIComponentListener::componentReleased(std::string sComponentName)
{
}

/**
This function should only be called by the component that this component listener is registered with when the 
component is hovered over. 

@param sComponentName The name of the component. */
void UIComponentListener::componentHovered(std::string sComponentName)
{
}

/**
This function should only be called by the component that this component listener is registered with when the 
component is unhovered.

@param sComponentName The name of the component. */
void UIComponentListener::componentUnhovered(std::string sComponentName)
{
}