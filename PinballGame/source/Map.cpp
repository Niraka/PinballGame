#include "Map.h"

/**
Constructs a default Map. */
Map::Map()
{
	m_collisionsManager.addCollisionListener(this);
	m_currentState = State::WAITING;
}

/**
Sets the gravity of the map. Gravity is applied to every non-static GameObject
every game loop.

@param vGravity The gravity vector. */
void Map::setGravity(Vector2D& vGravity)
{
	m_vGravity = vGravity;
}

/**
Clears all GameObjects from the map, clearing up any used memory as it goes. */
void Map::clearGameObjects()
{
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		delete &(*it)->getCollidable()->getShape();
		delete *it;
	}
	m_gameObjects.clear();
}		

/**
Sets the state of the map. *

@param newState The new state. */
void Map::setState(Map::State newState)
{
	m_currentState = newState;
}

/**
Returns the state of the map. 

@return The state of the map. */
Map::State Map::getState()
{
	return m_currentState;
}

/**
Creates the user interface for the map. The interface is consistent across all maps. 

@param bl A pointer to the button listener to add to components that require one.
@param uim A reference to the UIManager that will manage the newly created UI. */
void Map::createUI(UIButtonListener* bl, UIManager& uim)
{
	std::string sScoreComponent;

	UIBuilder b(uim);
	b.buildUI("../data/user_interfaces/game/avalanche_constructor.txt", bl, sScoreComponent);
	uim.setUILoaded(UIManager::UIs::MAP_AVALANCHE, true);

	// Link the score component
	UIComponent* u = uim.getUIComponentRef(sScoreComponent);
	UIText* txt = dynamic_cast<UIText*>(u);
	m_scoreUIComponent = txt;
}

/**
Deletes the user interface for the map. 

@param uim A reference to the UIManager containing the UI to be deleted. */
void Map::deleteUI(UIManager& uim)
{
	UIDestructor d(uim);
	d.deconstructUI("../data/user_interfaces/game/avalanche_destructor.txt");
	uim.setUILoaded(UIManager::UIs::MAP_AVALANCHE, false);
}

/**
Resets the maps clock to 0. */
void Map::resetClock()
{
	m_clock.restart();
}

/**
Returns a reference to the maps clock. 

@return A reference to the maps clock. */
sf::Clock Map::getClock() const
{
	return m_clock;
}

/**
Resets the score to 0. Updates the score display accordingly. */
void Map::resetScore()
{
	m_scoreTracker.setScore(0.f);
	m_scoreTracker.setScoreMultiplier(1.f);
	updateScoreDisplay();
}

/**
Returns the current score.

@return The current score. */
float Map::getScore() const
{
	return m_scoreTracker.getScore();
}

/**
Registers a MapEventListener with this map. 

@param l The MapEventListener to add. */
void Map::addMapEventListener(MapEventListener* l)
{
	m_mapEventListeners.push_back(l);
}

/**
Launches a game over event to all MapEventListeners registered with this map. */
void Map::launchEvent_gameOver()
{
	for (std::vector<MapEventListener*>::iterator it = m_mapEventListeners.begin(); it != m_mapEventListeners.end(); ++it)
	{
		(*it)->gameOver(this);
	}
}

/**
Updates the UIText component with the new score value. If the component was not set (The component was missing from the
map file, the program will crash (Intentionally). */
void Map::updateScoreDisplay()
{
	m_scoreUIComponent->setString(&std::string(std::to_string((int)m_scoreTracker.getScore())));
	m_scoreUIComponent->setAlignment(UIText::Alignment::CENTRE);
}

/**
Searches for the first GameObject with the given name and returns a pointer to it. 

@param sGOName The name of the GameObject to get. 
@return The first GameObject found with the given name, or a nullptr if no GameObject was found. */
GameObject* Map::getGameObject(std::string sGOName)
{
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		if ((*it)->getName() == sGOName)
		{
			return *it;
		}
	}
	return nullptr;
}

/**
Searches for every GameObject whos name contains the given name. Returns a vector of pointers to the found
GameObjects.

@param sGOName The name to search with. 
@return A vector of pointers to GameObjects whos names contained the given name. */
std::vector<GameObject*> Map::getGameObjects(std::string sGOName)
{
	std::vector<GameObject*> gameObjects;
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		if ((*it)->getName().find(sGOName) != std::string::npos)
		{
			gameObjects.push_back(*it);
		}
	}
	return gameObjects;
}

/**
Draws the map to the target. Consult the SFML Graphics documentation for further information.

@see sf::RenderTarget
@see sf::RenderStates
@param target The target to draw to.
@param states The RenderStates. */
void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	for (std::vector<GameObject*>::const_iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		target.draw(**it);
	}
}
