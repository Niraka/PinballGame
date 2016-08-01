#include "Snowflake.h"

/**
Constructs a default Snowflake. */
Snowflake::Snowflake()
{
}

/**
Constructs a Snowflake with the given parameters. 

@param texture The texture to apply to the Snowflake. */
Snowflake::Snowflake(sf::Texture* texture)
{
	m_Sprite.setPosition(0, 0);
	m_Sprite.setOrigin(25, 25);
	m_Sprite.setTexture(*texture);
}

/**
Sets the fall speed.

@param fFallSpeed The fall speed. */
void Snowflake::setFallSpeed(float fFallSpeed)
{
	m_fFallSpeed = fFallSpeed;
}

/**
Sets the rotation speed

@param fRotationSpeed The rotation speed. */
void Snowflake::setRotationSpeed(float fRotationSpeed)
{
	m_fRotationSpeed = fRotationSpeed;
}

/**
Scales the Snowflake by the given amount in the X and Y axis. 

@param fScale The amount to scale by. */
void Snowflake::scale(float fScale)
{
	m_Sprite.setScale(fScale, fScale);
}

/**
Sets the X position.

@param fX The X position. */
void Snowflake::setX(float fX)
{
	m_Sprite.setPosition(fX, getY());
}

/**
Sets the Y position.

@param fY The Y position. */
void Snowflake::setY(float fY)
{
	m_Sprite.setPosition(getX(), fY);
}

/**
Returns the fall speed.

@return The fall speed. */
float Snowflake::getFallSpeed()
{
	return m_fFallSpeed;
}

/**
Returns the X position.

@return The X position. */
float Snowflake::getX()
{
	return m_Sprite.getPosition().x;
}

/**
Returns the Y position.

@return The Y position. */
float Snowflake::getY()
{
	return m_Sprite.getPosition().y;
}

/**
Rotates the Snowflake by its rotation speed. */
void Snowflake::rotate()
{
	m_Sprite.rotate(m_fRotationSpeed);
}

/**
Draws the Snowflake to the target. Consult the SFML Graphics documentation for further information.

@see sf::RenderTarget
@see sf::RenderStates
@param target The target to draw to.
@param states The RenderStates. */
void Snowflake::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}