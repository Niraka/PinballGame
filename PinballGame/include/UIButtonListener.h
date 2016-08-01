/**
A UIButtonListener is an abstract class that provides the necessary functionality for listening for 
release and depress events occurring on UIButtons.
*/

#ifndef UIButtonListener_H
#define UIButtonListener_H

#include <string>

class UIButtonListener
{
	public:
		UIButtonListener();

		virtual void buttonDepressed(std::string sButtonName) = 0;
		virtual void buttonReleased(std::string sButtonName) = 0;
	protected:
	private:
};

#endif