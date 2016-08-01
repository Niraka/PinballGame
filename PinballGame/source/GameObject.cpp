#include "GameObject.h"

/**
Constructs a GameObject with the given parameters. 

@param sName The name of the Flipper.
@param pShape A pointer to the Shape representing this objects mass.
@param vPosition The position of the centre of the Flipper.
@param pMaterial A pointer to the Material this Flipper will use.
@param vRotationPoint The point that this Flipper will rotate around. 
@param bIsStatic True if the object will never move or rotate. */
GameObject::GameObject(std::string sName, Shape* pShape, Vector2D& vPosition, Material* pMaterial, bool bIsStatic)
: m_Collidable(sName, pShape, vPosition, pMaterial, bIsStatic)
{
	m_Collidable.addMovableListener(this);
	m_vDefaultPosition = vPosition;
	m_vDefaultVelocity = Vector2D(0, 0);
	m_fDefaultAngularVelocity = 0.f;
	m_fDefaultOrientation = pShape->getOrientation();
}

/**
Sets the texture of the GameObject.

@param texture The texture. */
void GameObject::setTexture(sf::Texture* texture)
{
	m_Sprite.setTexture(*texture);	
	// Need to get the scale before setting the origin so that the origin can be at the centre of the resized version of the shape.
	m_Sprite.setScale((m_Collidable.getShape().getHalfWidth() * 2.0) / texture->getSize().x, (m_Collidable.getShape().getHalfHeight() * 2.0) / texture->getSize().y);
	m_Sprite.setPosition(m_Collidable.getPosition().x(), m_Collidable.getPosition().y());	
	m_Sprite.setOrigin(m_Collidable.getShape().getHalfWidth() / m_Sprite.getScale().x, m_Collidable.getShape().getHalfHeight() / m_Sprite.getScale().y);	
	m_Sprite.setRotation(m_Collidable.getShape().getOrientation());
}

/**
Updates the GameObject. This function exists to be overridden by inheriting classes, and does nothing
when called on a normal GameObject. */
void GameObject::update()
{
}

/**
Returns the name of the GameObject. 

@return The name of the GameObject. */
std::string GameObject::getName()
{
	return m_Collidable.getName();
}

/**
Sets the position of the GameObject.

@param vNewPos The position. */
void GameObject::setPosition(Vector2D& vNewPos)
{
	m_Collidable.setPosition(vNewPos);
}

/**
Returns the position of the GameObject.

@return The position. */
Vector2D& GameObject::getPosition()
{
	return m_Collidable.getPosition();
}

/**
Returns a pointer to the Collidable representing this GameObject. 

@return A pointer to the Collidable representing this GameObject. */
Collidable* GameObject::getCollidable()
{
	return &m_Collidable;
}

/**
This function is called by the Movable this GameObject is listening to. It is used to ensure
consistency amongst the position of the collidable and the position of the sprite. */
void GameObject::movableMoved()
{
	m_Sprite.setPosition(m_Collidable.getPosition().x(), m_Collidable.getPosition().y());
}

/**
This function is called by the Movable this GameObject is listening to. It is used to ensure
consistency amongst the orientation of the collidable and the orientation of the sprite. */
void GameObject::movableRotated()
{
	m_Sprite.setRotation(m_Collidable.getShape().getOrientation());
}

/**
Resets the GameObject, settings its position, velocity, orientation and angular velocity to their
default values. Any existing force is also cleared from the GameObjects Movable. Default values are
equal to the values given when the object was created. Alternatively, default values can be manually
set. */
void GameObject::reset()
{
	m_Collidable.clearForce();
	m_Collidable.setVelocity(m_vDefaultVelocity);
	m_Collidable.setPosition(m_vDefaultPosition);
	m_Collidable.setAngularVelocity(m_fDefaultAngularVelocity);
	m_Collidable.setOrientation(m_fDefaultOrientation);
}

/**
Sets the default position of the GameObject.

@param vPos The position. */
void GameObject::setDefaultPosition(Vector2D& vPos)
{
	m_vDefaultPosition = vPos;
}

/**
Sets the default velocity of the GameObject.

@param vVel The velocity. */
void GameObject::setDefaultVelocity(Vector2D& vVel)
{
	m_vDefaultVelocity = vVel;
}

/**
Sets the default orientation of the GameObject, in degrees. 

@param fOrientation The orientation. */
void GameObject::setDefaultOrientation(float fOrientation)
{
	m_fDefaultOrientation = fOrientation;
}

/**
Sets the default angular velocity of the GameObject, in degrees. 

@param fAngularVelocity The velocity. */
void GameObject::setDefaultAngularVelocity(float fAngularVelocity)
{
	m_fDefaultAngularVelocity = fAngularVelocity;
}

/**
Sets the orientation of the GameObject. 

@param fOrientation The orientation. */
void GameObject::setOrientation(float fOrientation)
{
	// How this works:
	// Setting the orientation of the Collidable will trigger a movableRotated event on Collidable, and thus, this GameObject.
	// The movableRotated event will then configure the rotation of the sprite.
	m_Collidable.setOrientation(fOrientation);
}

/**
Modifies the orientation of the GameObject. 

@param fOrientation The orientation. */
void GameObject::modOrientation(float fOrientation)
{	
	// How this works:
	// Modding the orientation of the Collidable will trigger a movableRotated event on Collidable, and thus, this GameObject.
	// The movableRotated event will then configure the rotation of the sprite.
	m_Collidable.setOrientation(m_Collidable.getShape().getOrientation() + fOrientation);
}

/**
Returns the orientation of the GameObject. This function is essentially a shortcut for collidable.getShape().getOrientation(). 

@return The orientation of the GameObject. */
float GameObject::getOrientation()
{
	return m_Collidable.getShape().getOrientation();
}

/**
Draws the GameObject to the target. Consult the SFML Graphics documentation for further information.

@see sf::RenderTarget
@see sf::RenderStates
@param target The target to draw to.
@param states The RenderStates. */
void GameObject::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}