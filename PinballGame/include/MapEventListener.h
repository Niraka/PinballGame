/**
A MapEventListener is an abstract class that gives any subclass the required functionality for listening for
MapEvents occurring on the Map the listener is listening to. 
*/

#ifndef MapEventListener_H
#define MapEventListener_H

class Map;

class MapEventListener
{
	public:
		MapEventListener();

		virtual void gameOver(Map* pMap) = 0;

	protected:

	private:

};

#endif