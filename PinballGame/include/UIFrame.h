/**
A UIFrame is an extension of the UIComponent class that allows an otherwise abstract component to be
used as a purely structural block in a user interface hierarchy.

Generally speaking, a UIFrame is best used to encompass a large sub-section of a user interface so that
it can be enabled and disabled easily.

The root component of a UIManager is a UIFrame encompassing the entire screen.
*/

#ifndef UIFrame_H
#define UIFrame_H

#include "UIComponent.h"
#include "UIImage.h"

class UIFrame : public UIComponent
{
	public:
		UIFrame(std::string sComponentName, float fOffsetX, float fOffsetY, float fWidth, float fHeight);

		virtual void positionUpdated();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
	private:
		UIFrame();
};

#endif