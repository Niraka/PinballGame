#include "AnimationSnowfall.h"

/**
Construct a default AnimationSnowfall. */
AnimationSnowfall::AnimationSnowfall()
{
	m_fXOffset = 25;
	m_fSnowflakeWidth = 50;
	m_fDensityMultiplier = 10;

	// Default values
	m_fFallSpeed = 1;
	m_fWindowWidth = 1200;
	m_fWindowHeight = 800;
	m_fWindSpeed = 0.f;
	m_RandomGenerator.seed(time(0));

	distributorX = std::uniform_real_distribution<float>(m_fXOffset, (m_fWindowWidth - m_fXOffset));
	distributorY = std::uniform_real_distribution<float>(-(m_fWindowHeight + m_fSnowflakeWidth + 150), -m_fSnowflakeWidth);
	distributorSpeed = std::uniform_real_distribution<float>((m_fFallSpeed - 0.3f), (m_fFallSpeed + 0.3f));
}

/**
Sets the texture that the animation will use for the snowflakes. Note that only a pointer to a texture
is stored locally. The actual texture must be kept in memory elsewhere.

@param texture A pointer to an sf::Texture. */
void AnimationSnowfall::setTexture(sf::Texture* texture)
{
	m_Texture = texture;
}

/**
Sets the speed that the snowflake objects will move from the top of the screen to the bottom. Fall speeds are randomly
offset by plus or minus 0.3. The fall speed must be at least 0.31.

@param fFallSpeed The fall speed. */
void AnimationSnowfall::setFallSpeed(float fFallSpeed)
{
	if (fFallSpeed <= 0.3)
	{
		fFallSpeed = 0.31;
	}

	m_fFallSpeed = fFallSpeed;
	distributorSpeed = std::uniform_real_distribution<float>((m_fFallSpeed - 0.3f), (m_fFallSpeed + 0.3f));
}

/**
Sets the size of the window, and thus the size of the animation. Setting the window size to a smaller or larger number
than the actual window will only affect the distribution of the snowflakes.

@param iWindowWidth The width of the window. 
@param iWindowHeight The height of the window. */
void AnimationSnowfall::setWindowSize(int iWindowWidth, int iWindowHeight)
{
	m_fWindowWidth = iWindowWidth;
	m_fWindowHeight = iWindowHeight;
	distributorX = std::uniform_real_distribution<float>(m_fXOffset, (m_fWindowWidth - m_fXOffset));
	distributorY = std::uniform_real_distribution<float>(-(m_fWindowHeight + m_fSnowflakeWidth + 150), -m_fSnowflakeWidth);
}

/**
Sets the density of the snowfall. The number of snowflakes involved in the animation is equal to 10 times
the density. Tweak this number based on window size to get the desired affect. 

@param iDensity The density of the snowfall. */
void AnimationSnowfall::setDensity(int iDensity)
{
	std::uniform_real_distribution<float> distributorRotation(-0.4, 0.6);
	std::uniform_real_distribution<float> distributorScale(0.6, 1.5);
	if (m_Texture)
	{
		m_vSnowflakes.clear();

		for (int i = 0; i < (iDensity * m_fDensityMultiplier); i++)
		{
			Snowflake s(m_Texture);
			s.scale(distributorScale(m_RandomGenerator));
			s.setRotationSpeed(distributorRotation(m_RandomGenerator));
			s.setX(distributorX(m_RandomGenerator));
			s.setY(distributorY(m_RandomGenerator));
			s.setFallSpeed(distributorSpeed(m_RandomGenerator));
			m_vSnowflakes.push_back(s);
		}
	}
}

/**
Updates the animation frame. The animation has no internal timing and will run at an FPS equal to the rate that
it is called. */
void AnimationSnowfall::update()
{
	for (std::vector<Snowflake>::iterator it = m_vSnowflakes.begin(); it != m_vSnowflakes.end(); ++it)
	{
		if (it->getY() > (m_fWindowHeight + m_fSnowflakeWidth))
		{
			// Reset position
			it->setX(distributorX(m_RandomGenerator));
			it->setY(distributorY(m_RandomGenerator));
			it->setFallSpeed(distributorSpeed(m_RandomGenerator));
		}
		else
		{
			// Apply movement and rotation
			it->setY(it->getY() + it->getFallSpeed());
			it->setX(it->getX() + m_fWindSpeed);
			it->rotate();
		}
	}
}

/**
Draws the animation to the target. Consult the SFML Graphics documentation for further information.

@see sf::RenderTarget
@see sf::RenderStates
@param target The target to draw to.
@param states The RenderStates. */
void AnimationSnowfall::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (std::vector<Snowflake>::const_iterator it = m_vSnowflakes.begin(); it != m_vSnowflakes.end(); ++it)
	{
		target.draw(*it);
	}
}