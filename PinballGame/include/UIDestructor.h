/**
A UIDestructor is a method of cleanly deconstructing a user interface via reading the deconstruction
configuration outlined in a UIDestructor text file.

A clean deconstruction involves the removal of any resources that are exclusively in use by that
user interface as well as releasing and memory used by the components or pointers to those components
*/

#ifndef UIDestructor_H
#define UIDestructor_H

#include "UIComponent.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "StringsManager.h"
#include "FontManager.h"
#include "UIManager.h"
#include <fstream>
#include <istream>

class UIDestructor
{
	public:
		UIDestructor(UIManager& uim);

		void deconstructUI(std::string sDeconstructorFile);

	protected:

	private:
		UIManager* m_pUIM;
		TextureManager* m_tm;
		AudioManager* m_am;
		StringsManager* m_sm;
		FontManager* m_fm;
};

#endif