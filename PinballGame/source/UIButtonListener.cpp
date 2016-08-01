#include "UIButtonListener.h"

/**
Constructs a default UIButtonListener. */
UIButtonListener::UIButtonListener()
{
}

/**
This function should only be called by the button that this button listener is listening to when
it is depressed. 

@param sButtonName The name of the button that was depressed. */
void UIButtonListener::buttonDepressed(std::string sButtonName)
{
}

/**
This function should only be called by the button that this button listener is listening to when
it is released.

@param sButtonName The name of the button that was released. */
void UIButtonListener::buttonReleased(std::string sButtonName)
{
}