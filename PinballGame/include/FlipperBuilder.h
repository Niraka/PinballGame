/**
A FlipperBuilder is an extension of the GameObjectBuilder class that has been modified to build
a Flipper object instead of a GameObject.

Any returned pointers are pointers to GameObjects.
*/

#ifndef FlipperBuilder_H
#define FlipperBuilder_H

#include "GameObjectBuilder.h"
#include "FlipperLeft.h"
#include "FlipperRight.h"

class FlipperBuilder : public GameObjectBuilder
{
	public:
		FlipperBuilder(MaterialsManager& mm);

		virtual GameObject* build(std::vector<std::string>& strings);

	protected:

	private:
};

#endif