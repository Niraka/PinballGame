#include "Flipper.h"

/**
Constructs a Flipper with the given parameters.

@param sName The name of the Flipper.
@param pShape A pointer to the Shape representing this objects mass.
@param vPosition The position of the centre of the Flipper.
@param pMaterial A pointer to the Material this Flipper will use.
@param vRotationPoint The point that this Flipper will rotate around. */
Flipper::Flipper(std::string sName, Shape* pShape, Vector2D& vPosition, Material* pMaterial, Vector2D vRotationPoint)
: GameObject(sName, pShape, vPosition, pMaterial, false)
{
	setRestAngle(pShape->getOrientation());
	m_fRiseSpeed = 1.5;
	m_fFallSpeed = 1.5;

	// This line fixes a bug where the flippers will not start in the correct position. 
	setOrientation(0.f);

	setState(FlipperStates::FALLING);
	m_vRotationPoint = vRotationPoint;
}

/**
Returns the fall speed.

@return The fall speed. */
float Flipper::getFallSpeed()
{
	return m_fFallSpeed;
}

/**
Returns the rise speed.

@return The rise speed. */
float Flipper::getRiseSpeed()
{
	return m_fRiseSpeed;
}

/**
Sets the rest angle of the Flipper to the given angle. 

@param fAngle The angle. */
void Flipper::setRestAngle(float fAngle)
{
	m_fRestAngle = fAngle;
	setDefaultOrientation(m_fRestAngle);
}

/**
Sets the peak angle of the Flipper to the given angle.

@param fAngle The angle. */
void Flipper::setPeakAngle(float fAngle)
{
	m_fPeakAngle = fAngle;
}

/**
Sets the state of the Flipper. 

@param state The new state of the Flipper. */
void Flipper::setState(FlipperStates state)
{
	m_currentState = state;
}

/**
Returns the state of the flipper.

@return The state of the flipper. */
Flipper::FlipperStates Flipper::getState()
{
	return m_currentState;
}

/**
Sets the rise speed of the flipper.

@param fRiseSpeed The rise speed. */
void Flipper::setRiseSpeed(float fRiseSpeed)
{
	m_fRiseSpeed = fRiseSpeed;
}

/**
Sets the fall speed of the flipper. 

@param fFallSpeed The fall speed. */
void Flipper::setFallSpeed(float fFallSpeed)
{
	m_fFallSpeed = fFallSpeed;
}

/**
Returns the rotation point of the flipper. 

@return The rotation point. */
Vector2D& Flipper::getRotationPoint()
{
	return m_vRotationPoint;
}