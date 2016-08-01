/**
A Flipper is an extension of the GameObject class that adds the functionality for moving in an arc-like
manner around a point in a direction depending on the current state.

The states of the Flipper represent how it will behave at any given time.
The states are: Resting (Doing nothing whilst orientated at the rest angle), rising (Moving upwards towards the peak angle) 
and falling (Moving downwards towards the rest angle).
*/

#ifndef Flipper_H
#define Flipper_H

#include "GameObject.h"
#include <iostream>

class Flipper : public GameObject
{
	public:
		enum FlipperStates {REST, RISING, FALLING};

		Flipper(std::string sName, Shape* pShape, Vector2D& vPosition, Material* pMaterial, Vector2D vRotationPoint);

		void setRestAngle(float fAngle);
		void setPeakAngle(float fAngle);
		void setState(FlipperStates state);
		void setRiseSpeed(float fRiseSpeed);
		void setFallSpeed(float fFallSpeed);
		float getFallSpeed();
		float getRiseSpeed();
		FlipperStates getState();
		Vector2D& getRotationPoint();

		virtual void update() = 0;

	protected:
		FlipperStates m_currentState;
		Vector2D m_vRotationPoint;
		float m_fPeakAngle;
		float m_fRestAngle;
		float m_fRiseSpeed;
		float m_fFallSpeed;

	private:

};

#endif