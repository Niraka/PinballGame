/**
Snowflake objects are used in large numbers (Generally 20-80) to populate the AnimationSnowfall animation
with falling snowflake images.

A Snowflake contains all of its own rotation, speed and position data.
*/

#ifndef Snowflake_H
#define Snowflake_H

#include <SFML/Graphics.hpp>

class Snowflake : public sf::Drawable
{
	public:
		Snowflake(sf::Texture* texture);

		void setFallSpeed(float fFallSpeed);
		void setRotationSpeed(float fRotationSpeed);
		void scale(float fScale);
		void setX(float fX);
		void setY(float fY);
		float getFallSpeed();
		float getX();
		float getY();
		void rotate();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	protected:

	private:
		sf::Sprite m_Sprite;
		float m_fFallSpeed;
		float m_fRotationSpeed;
		
		Snowflake();
};

#endif