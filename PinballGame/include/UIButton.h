/**
A UIButton is an extension of the UIComponent class to provide functionality for buttons that can
be clicked, hovered, responded to and textured.

Listening to events on a UIButton is as simple as registering a UIButtonListener with that button and ensuring
that the button is set to active (through functionaltiy provided by the UIComponent).

Texturing a button follows a set of limitations. The texture must be a total of 200x210 pixels and must contain
3 sub-rects, each 70 pixels high. Each of the sub-rects defines one of the following textures: A released texture,
a hovered texture and a depressed texture. The textures must be in that order.

Button clicks can be simulated in cases where hotkeys are used in place of actual clicks.

A button may also have a clicked and hover sound effect.
*/


#ifndef UIButton_H
#define UIButton_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "UIComponent.h"
#include "UIComponentListener.h"
#include "UIButtonListener.h"
#include <vector>

class UIButton : public UIComponent, UIComponentListener
{
	public:
		UIButton(std::string sComponentName, float fOffsetX, float fOffsetY, float fWidth, float fHeight);

		void setTexture(sf::Texture* texture);
		void setSoundHover(sf::SoundBuffer* sound);
		void setSoundClicked(sf::SoundBuffer* sound);
		void addButtonListener(UIButtonListener* bl);
		void removeButtonListener(UIButtonListener* bl);
		void simulateDepress();
		void simulateRelease();

		virtual void componentDepressed(std::string sComponentName);
		virtual void componentReleased(std::string sComponentName);
		virtual void componentHovered(std::string sComponentName);
		virtual void componentUnhovered(std::string sComponentName);
		virtual void positionUpdated();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:

	private:
		void launchEvent_buttonDepressed();
		void launchEvent_buttonReleased();
		std::vector<UIButtonListener*> m_ButtonListeners;
		sf::Sound m_SoundHover;
		sf::Sound m_SoundClicked;
		sf::Sprite m_Sprite;
		
		UIButton();	
};

#endif
