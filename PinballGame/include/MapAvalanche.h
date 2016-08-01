/**
An extension of the Map class to define "Avalanche" specific functionality.
*/

#ifndef MapAvalanche_H
#define MapAvalanche_H

#include "Map.h"

class MapAvalanche : public Map
{
	public:
		MapAvalanche();

		virtual void update();
		virtual void resetMap();
		virtual void collisionOccurred(std::string sName1, std::string sName2);
		virtual void build();

	protected:

	private:
		FlipperLeft* m_flipperLeft;
		FlipperRight* m_flipperRight;

};

#endif