/**
A map is a container and controller object for the game world.

The main component of a map is the vector of GameObjects that build up the actual world. Typically,
this vector is populated using a GameObjectBuilder object during a call to load the map.

Calls to draw the map will draw every GameObject container within it.

The map is able to store a vector of MapEventListener objects that it can notify of map events
as they occurr. See the MapEventListener class for more details on the types of events.

The map also contains one internal clock that can be manipulated to time the duration of play
on the map. This clock is reset every time the map is reset.

*/


#ifndef Map_H
#define Map_H

#include "GameObject.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "MaterialsManager.h"
#include "CollisionsManager.h"
#include "UIText.h"
#include "UIButton.h"
#include "UIManager.h"
#include "StringsManager.h"
#include "FontManager.h"
#include "ScoreTracker.h"
#include "MapEventListener.h"
#include "FlipperLeft.h"
#include "FlipperRight.h"
#include "MapBuilder.h"
#include "UIBuilder.h"
#include "UIDestructor.h"

class Map : public sf::Drawable, CollisionListener
{
	public:
		enum State {WAITING, LAUNCHING, PLAYING};

		Map();

		void setGravity(Vector2D& vGravity);
		void clearGameObjects();
		GameObject* getGameObject(std::string sGOName);
		void updateScoreDisplay();
		void createUI(UIButtonListener* bl, UIManager& uim);
		void deleteUI(UIManager& uim);
		void resetClock();
		sf::Clock getClock() const;
		void resetScore();
		float getScore() const;
		void launchEvent_gameOver();
		void addMapEventListener(MapEventListener* l);
		std::vector<GameObject*> getGameObjects(std::string sGOName);
		void setState(Map::State newState);
		Map::State getState();

		virtual void update() = 0;
		virtual void resetMap() = 0;
		virtual void collisionOccurred(std::string sName1, std::string sName2) = 0;
		virtual void build() = 0;
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	protected:
		State m_currentState;
		ScoreTracker m_scoreTracker;
		Vector2D m_vGravity;
		sf::Clock m_clock;
		std::vector<GameObject*> m_gameObjects;
		MaterialsManager m_materialsManager;
		CollisionsManager m_collisionsManager;
		UIText* m_scoreUIComponent;
	
	private:	
		std::vector<MapEventListener*> m_mapEventListeners;
};

#endif