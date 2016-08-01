/**
A UIManager is a controller and container class for a user interface and the components that it is made up
of.

The UIManager contains one fixed UIFrame component - The root component. Adding a new interface or component is
as simple as adding the parent of the constructed interface as a child of the UIManagers root component. Removing 
interfaces or individual components can be done by removing the component from the hierarchy. Note that removing
a component does not mean the memory it occupies it cleared.

The UIManager has support for 4 types of events: Hover, unhover, depress and release. These events can be checked
on all components that are both active and part of the hierarchy by calling the relevant check_X_Events function.
The hover and unhover events are bundled in to the checkHoverEvents function. You will need to tweak the frequency
that you check for hover events in order to get responsive hover events.

The UIManager also keeps tracks of which user interfaces have been loaded in to memory. This allows you to safely
enable and disable components that you know exist, and also prevents wasteful usage of file reading operations.
*/

#ifndef UIManager_H
#define UIManager_H

#include "UIFrame.h"
#include <map>

class UIManager
{
	public:		
		enum UIs {NO_UI, MAIN, MAP_SELECTION, INSTRUCTIONS, HIGHSCORES, OPTIONS, MAP_AVALANCHE, MAP_SNOW_TUNNELS};

		UIManager();
		
		void checkHoverEvents(float mouseX, float mouseY);
		void checkReleaseEvents(float mouseX, float mouseY);
		void checkDepressEvents(float mouseX, float mouseY);
		UIFrame& getRootComponent();
		void addUIComponentRef(UIComponent* u);
		UIComponent* getUIComponentRef(std::string sComponentName);
		void removeUIComponentRef(std::string sComponentName);
		void setUILoaded(UIs ui, bool isLoaded);
		bool getUILoaded(UIs ui);

	protected:

	private:
		UIFrame m_RootComponent;
		std::map<std::string, UIComponent*> m_UIComponents;
		bool m_abLoadedUIs[7];
};

#endif