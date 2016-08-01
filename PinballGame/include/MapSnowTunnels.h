/**
An extension of the Map class to define "SnowTunnels" specific functionality.
*/


#ifndef MapSnowTunnels_H
#define MapSnowTunnels_H

#include "Map.h"

class MapSnowTunnels : public Map
{
	public:
		MapSnowTunnels();

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