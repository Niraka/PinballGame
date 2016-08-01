/**
A UIImage is an extension of the UIComponent class to provide functionality for drawing
images on the component.

Although the component has been extended for drawing images, it does not actually store the image
itself. Only a pointer to the current location of the texture is stored on the component when the
setTexture function is called, and such the image/texture must be kept in memory elsewhere for the 
lifetime of the UIImage.

Additionally, it is important to note that the texture will scale to fill the entire size of the
UIImage, with no option for configuration.
*/

#ifndef UIImage_H
#define UIImage_H

#include "UIComponent.h"

class UIImage : public UIComponent
{
	public:
		UIImage(std::string sComponentName, float fOffsetX, float fOffsetY, float fWidth, float fHeight);

		void setTexture(sf::Texture* texture);

		virtual void positionUpdated();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
	private:
		sf::Sprite m_Sprite;

		UIImage();
};

#endif