/**
A UIComponentBuilder provides a method for the creation of a set of user interface components (UIText / 
UIButton / UIImage / etc) via the interpretation of a vector of strings.

The type of component built depends on the parameters passed to the builder. The returned pointer, however,
will always be a UIComponent.
*/

#ifndef UIComponentBuilder_H
#define UIComponentBuilder_H

#include "UIButton.h"
#include "UIImage.h"
#include "UIText.h"
#include "UIFrame.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "StringsManager.h"
#include "FontManager.h"

class UIComponentBuilder
{
	public:
		UIComponentBuilder();

		UIComponent* build(std::vector<std::string> strings, UIButtonListener* bl);

	protected:

	private:
		TextureManager* m_tm;
		AudioManager* m_am;
		StringsManager* m_sm;
		FontManager* m_fm;
};

#endif