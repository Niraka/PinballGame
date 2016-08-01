/**
The FlipperLeft is an extension of the Flipper class that allows the Flipper to rotate
anticlockwise around a point when its update function is called.
*/

#ifndef FlipperLeft_H
#define FlipperLeft_H

#include "Flipper.h"

class FlipperLeft : public Flipper
{
	public:
		FlipperLeft(std::string sName, Shape* pShape, Vector2D& vPosition, Material* pMaterial, Vector2D vRotationPoint);

		virtual void update();

	protected:

	private:

};

#endif