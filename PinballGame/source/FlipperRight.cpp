#include "FlipperRight.h"

/**
Constructs a FlipperRight with the given parameters.

@param sName The name of the Flipper.
@param pShape A pointer to the Shape representing this objects mass.
@param vPosition The position of the centre of the Flipper.
@param pMaterial A pointer to the Material this Flipper will use.
@param vRotationPoint The point that this Flipper will rotate around. */
FlipperRight::FlipperRight(std::string sName, Shape* shape, Vector2D& vPosition, Material* material, Vector2D vRotationPoint)
: Flipper(sName, shape, vPosition, material, vRotationPoint)
{
	m_fPeakAngle = 70;
}

/**
Updates the Flipper with FlipperRight specific logic. */
void FlipperRight::update()
{
	switch (m_currentState)
	{
		case FlipperStates::REST:

			break;
		case FlipperStates::RISING:

			if (getCollidable()->getShape().getOrientation() > m_fPeakAngle)
			{
				setState(FlipperStates::FALLING);
			}
			else
			{
				getCollidable()->rotateAboutPoint(m_fRiseSpeed, m_vRotationPoint);
				modOrientation(m_fRiseSpeed);
			}

			break;
		case FlipperStates::FALLING:

			if (getCollidable()->getShape().getOrientation() < m_fRestAngle)
			{
				setState(FlipperStates::REST);
			}
			else
			{
				getCollidable()->rotateAboutPoint(-m_fFallSpeed, m_vRotationPoint);
				modOrientation(-m_fFallSpeed);
			}

			break;
	}
}