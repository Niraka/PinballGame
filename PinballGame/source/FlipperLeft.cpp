#include "FlipperLeft.h"

/**
Constructs a FlipperLeft with the given parameters. 

@param sName The name of the Flipper.
@param pShape A pointer to the Shape representing this objects mass. 
@param vPosition The position of the centre of the Flipper.
@param pMaterial A pointer to the Material this Flipper will use.
@param vRotationPoint The point that this Flipper will rotate around. */
FlipperLeft::FlipperLeft(std::string sName, Shape* pShape, Vector2D& vPosition, Material* pMaterial, Vector2D vRotationPoint)
: Flipper(sName, pShape, vPosition, pMaterial, vRotationPoint)
{
	m_fPeakAngle = -70;
}

/**
Updates the Flipper with FlipperLeft specific logic. */
void FlipperLeft::update()
{
	switch (m_currentState)
	{
		case FlipperStates::REST:

			break;
		case FlipperStates::RISING:

			if (getCollidable()->getShape().getOrientation() < m_fPeakAngle)
			{
				setState(FlipperStates::FALLING);
			}
			else
			{
				modOrientation(-m_fRiseSpeed);
				getCollidable()->rotateAboutPoint(-m_fRiseSpeed, m_vRotationPoint);
			}

			break;
		case FlipperStates::FALLING:

			if (getCollidable()->getShape().getOrientation() > m_fRestAngle)
			{
				setState(FlipperStates::REST);
			}
			else
			{
				modOrientation(m_fFallSpeed);
				getCollidable()->rotateAboutPoint(m_fFallSpeed, m_vRotationPoint);
			}

			break;
	}
}