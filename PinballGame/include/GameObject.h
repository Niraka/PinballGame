/**
A GameObject is a representation of any tangible object that exists within the game world.

GameObjects can (but do not have to) be textured. The attachment points for a texture is the
centre point of both the texture and the gameobject. The position and orientation of the texture
is automatically updated with the gameobjects collidable.

The static flag is an inherited flag from the underlying collidable object. Making a
GameObject static tells the system that this object will never move or rotate. This flag cannot
be updated for the lifetime of the GameObject.

The reset function provides a way to reset the object to a predefined orientation, velocity and
position. The values to reset to can be updated, but usually the initial parameters are good
enough.
*/

#ifndef GameObject_H
#define GameObject_H

#include <SFML/Graphics.hpp>
#include "Collidable.h"
#include "MovableListener.h"

class GameObject : public sf::Drawable, MovableListener
{
	public:
		GameObject(std::string sName, Shape* pShape, Vector2D& vPosition, Material* pMaterial, bool bIsStatic);

		void setPosition(Vector2D& vNewPos);
		Vector2D& getPosition();
		Collidable* getCollidable();
		std::string getName();
		void reset();
		void setOrientation(float fOrientation);
		void modOrientation(float fOrientation);
		float getOrientation();
		void setDefaultPosition(Vector2D& pos);
		void setDefaultVelocity(Vector2D& vel);
		void setDefaultOrientation(float fOrientation);
		void setDefaultAngularVelocity(float fAngularVelocity);
		
		virtual void update();
		virtual void setTexture(sf::Texture* texture);
		virtual void movableRotated();
		virtual void movableMoved();
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		float m_fDefaultOrientation;
		float m_fDefaultAngularVelocity;
		Vector2D m_vDefaultPosition;
		Vector2D m_vDefaultVelocity;
		Collidable m_Collidable;
		sf::Sprite m_Sprite;

	private:

};

#endif