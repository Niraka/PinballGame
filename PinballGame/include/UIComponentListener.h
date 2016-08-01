/**
A UIComponentListener is an abstract class that provides the necessary functionality for listening for events
that occur on UIComponents. 
*/

#ifndef UIComponentListener_H
#define UIComponentListener_H

#include <string>

class UIComponentListener
{	
	public:
		UIComponentListener();

		virtual void componentDepressed(std::string sComponentName) = 0;
		virtual void componentReleased(std::string sComponentName) = 0;
		virtual void componentHovered(std::string sComponentName) = 0;
		virtual void componentUnhovered(std::string sComponentName) = 0;
	
	protected:

	private:

};

#endif