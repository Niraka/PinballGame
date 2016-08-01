/**
The FlipperRight is an extension of the Flipper class that allows the Flipper to rotate
clockwise around a point when its update function is called.
*/

#ifndef FlipperRight_H
#define FlipperRight_H

#include "Flipper.h"

class FlipperRight : public Flipper
{
	public:
		FlipperRight(std::string sName, Shape* pShape, Vector2D& vPosition, Material* pMaterial, Vector2D vRotationPoint);

		virtual void update();

	protected:

	private:

};

#endif