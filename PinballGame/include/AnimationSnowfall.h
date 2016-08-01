/**
A snowfall animation for adding a little more life to an otherwise static background.

The texture in use by the animation is not stored on the object, and thus must be kept in
memory elsewhere for as long as the animation is required.

The animation should be notified every time the size of the window changes in order to
produce a correct snowflake distribution.
*/

#ifndef AnimationSnowfall_H
#define AnimationSnowfall_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Snowflake.h"
#include <random>

class AnimationSnowfall : public sf::Drawable
{
	public:
		AnimationSnowfall();

		void setWindowSize(int iWindowWidth, int iWindowHeight);
		void setDensity(int iDensity);
		void setFallSpeed(float fFallSpeed);
		void setTexture(sf::Texture* texture);
		void update();

		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	
	protected:

	private:
		sf::Texture* m_Texture;
		std::vector<Snowflake> m_vSnowflakes;
		float m_fWindowHeight;
		float m_fWindowWidth;
		float m_fFallSpeed;
		float m_fWindSpeed;		
		float m_fXOffset;
		float m_fSnowflakeWidth;
		float m_fDensityMultiplier;
		std::mt19937 m_RandomGenerator; 
		std::uniform_real_distribution<float> distributorX;
		std::uniform_real_distribution<float> distributorY;
		std::uniform_real_distribution<float> distributorSpeed;
};

#endif