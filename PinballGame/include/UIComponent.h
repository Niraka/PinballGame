/**
A UIComponent is a data class that provides the structural data and functionality
for forming a hierarchical user interface through parent/child UIComponent relationships.

A UIComponent is always positioned relative to its parents top-left corner.
*/

#ifndef UIComponent_H
#define UIComponent_H

#include "UIComponentListener.h"
#include <SFML/Graphics.hpp>
#include <string>
#include <map>
#include <vector>

class UIComponent : public sf::Drawable
{
	public:
		UIComponent(std::string sComponentName, float fOffsetX, float fOffsetY, float fWidth, float fHeight);

		void setSize(float fWidth, float fHeight);
		void setWidth(float fWidth);
		void setHeight(float fHeight);
		float getWidth() const;
		float getHeight() const;
		void checkHoverEvents(float mouseX, float mouseY);
		void checkReleaseEvent(float mouseX, float mouseY);
		void checkDepressEvent(float mouseX, float mouseY);
		void addComponentListener(UIComponentListener* listener);
		void removeComponentListener(UIComponentListener* listener);
		void launchEvent_componentHovered();
		void launchEvent_componentUnhovered();
		void launchEvent_componentReleased();
		void launchEvent_componentDepressed();
		void setOffsetX(float fOffsetX);
		void setOffsetY(float fOffsetY);
		float getOffsetX() const;
		float getOffsetY() const;	
		float getAbsolutePositionX();
		float getAbsolutePositionY();
		std::string getName() const;
		bool hasParent() const;
		void addChild(UIComponent* UIComponent);
		void removeChild(std::string sComponentName);
		UIComponent* getParent() const;
		void repositionChildren();
		bool isHovered() const;
		bool isReleased() const;
		void setActive(bool bActive);
		void setVisible(bool bVisible);
		bool isActive();
		bool isVisible();

		virtual void positionUpdated() = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	protected:
		std::vector<UIComponentListener*> m_ComponentListeners;
		std::map<std::string, UIComponent*> m_ChildComponents;		
		bool m_bIsActive;
		bool m_bIsVisible;

	private:
		bool m_bIsHovered;
		bool m_bIsReleased;
		float m_fWidth;
		float m_fHeight;
		float m_fOffsetX;
		float m_fOffsetY;
		std::string m_sComponentName;
		UIComponent* m_Parent;


		UIComponent();	

		bool checkCollision(float mouseX, float mouseY);
		void setParent(UIComponent* UIComponent);		
};

#endif