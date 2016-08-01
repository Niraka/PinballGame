#include "MapSnowTunnels.h"

#include "Circle.h"
#include "AABB.h"
#include "OBB.h"

/**
Constructs a default MapSnowTunnels. */
MapSnowTunnels::MapSnowTunnels()
{
}

/**
Updates the map with snow tunnels specific logic. */
void MapSnowTunnels::update()
{
	switch (m_currentState)
	{
	case Map::State::WAITING:

		// Handle flipper interactions
		m_flipperLeft->update();
		m_flipperRight->update();

		break;

	case Map::State::LAUNCHING:

		// Handle flipper interactions
		m_flipperLeft->update();
		m_flipperRight->update();

		// Handle launcher collider interactions
		if (getGameObject("wallLauncherCollider")->getPosition().y() < 660)
		{
			getGameObject("wallLauncherCollider")->getCollidable()->modPosition(Vector2D(0.f, 0.5));
		}
		else // (getGameObject("wallLauncherCollider")->getPosition().y() >= 660)
		{
			setState(Map::State::PLAYING);
		}

		break;

	case Map::State::PLAYING:

		// Handle flipper interactions
		m_flipperLeft->update();
		m_flipperRight->update();

		// Handle launcher collider interactions
		if (getGameObject("wallLauncherCollider")->getPosition().y() > 600.f)
		{
			getGameObject("wallLauncherCollider")->getCollidable()->setMaterial(m_materialsManager.getMaterial("launcher"));
			getGameObject("wallLauncherCollider")->getCollidable()->applyForce(0.f, -150000.f);
		}
		else if (getGameObject("wallLauncherCollider")->getPosition().y() <= 600.f)
		{
			getGameObject("wallLauncherCollider")->getCollidable()->setVelocity(0, 0);
			getGameObject("wallLauncherCollider")->getCollidable()->setMaterial(m_materialsManager.getMaterial("immovable"));
		}

		// Apply gravity to ALL game objects
		for (std::vector<GameObject*>::const_iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
		{
			(*it)->getCollidable()->applyForce(m_vGravity * (*it)->getCollidable()->getGravityMultiplier());
		}

		// Score update must occur BEFORE collision checks. Collision checks can cause the game to end. Having the score update
		// after a loss can result in a score of 1 being displayed.
		m_scoreTracker.modScore(1.f);
		updateScoreDisplay();

		m_collisionsManager.update(0.016);
		m_collisionsManager.checkCollisions();
				
		// Apply velocity cap
		for (std::vector<GameObject*>::const_iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
		{
			Collidable* c = (*it)->getCollidable();
			if (c->getVelocity().x() > 450)
			{
				c->setVelocity(450, c->getVelocity().y());
			}
			if (c->getVelocity().y() > 450)
			{
				c->setVelocity(c->getVelocity().x(), 450);
			}
		}

		break;
	}
}

/**
Launches a game over event and resets the map to a default state. */
void MapSnowTunnels::resetMap()
{
	launchEvent_gameOver();
	resetScore();
	resetClock();
	getGameObject("wallLauncherCollider")->reset();
	getGameObject("snowball")->reset();
}

/**
Builds the Snow Tunnels map. The map data is loaded in from a fixed file location ("maps/snow_tunnels.txt"). Note that
the map demands the existence of the following objects: "flipperLeft", "flipperRight". */
void MapSnowTunnels::build()
{
	MapBuilder mb;
	mb.buildMap("../data/maps/snow_tunnels.txt", m_gameObjects, m_materialsManager);

	// Add each GameObject to the collision manager.
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); ++it)
	{
		if ((*it)->getCollidable()->isStatic())
		{
			m_collisionsManager.addStaticCollidable((*it)->getCollidable());
		}
		else
		{
			m_collisionsManager.addNonStaticCollidable((*it)->getCollidable());
		}	
	}

	// Link flippers for convenience
	GameObject* g = getGameObject("flipperLeft");
	m_flipperLeft = dynamic_cast<FlipperLeft*>(g);
	g = getGameObject("flipperRight");
	m_flipperRight = dynamic_cast<FlipperRight*>(g);
}

/**
This function is called by the collision manager whenever a collision occurs between two Collidable objects that
exist on the map. Note that the order in which the names are received for a collisionOccurred event are essentially
random. Additionally, a Collidable inherits its name from a GameObject, allowing for safe calls to getGameObject(sName1)
etc etc.

@param sName1 The name of the first Collidable. 
@param sName2 The name of the second Collidable. */
void MapSnowTunnels::collisionOccurred(std::string sName1, std::string sName2)
{
	if (sName1 == "snowball" && sName2 == "sporgle" || sName2 == "snowball" && sName1 == "sporgle")
	{
		m_scoreTracker.modScore(2000.f);
		updateScoreDisplay();
	}
	else if (sName1 == "snowball" && sName2 == "wallBottom" || sName2 == "snowball" && sName1 == "wallBottom")
	{
		resetMap();
	}
	else if (sName1 == "snowball" && sName2 == "wallLauncherCollider" || sName2 == "snowball" && sName1 == "wallLauncherCollider")
	{
		if (m_currentState == Map::State::PLAYING && m_clock.getElapsedTime().asSeconds() > 5)
		{
			resetMap();
		}
	}

	// Apply affects if a flipper was hit
	if (sName1 == "flipperRight")
	{
		getGameObject(sName2)->getCollidable()->multiplyVelocity(1.8);
		m_flipperRight->setState(Flipper::FlipperStates::FALLING);
	}
	if (sName2 == "flipperRight")
	{
		getGameObject(sName1)->getCollidable()->multiplyVelocity(1.8);
		m_flipperRight->setState(Flipper::FlipperStates::FALLING);
	}
	if (sName1 == "flipperLeft")
	{
		getGameObject(sName2)->getCollidable()->multiplyVelocity(1.8);
		m_flipperLeft->setState(Flipper::FlipperStates::FALLING);
	}
	if (sName2 == "flipperLeft")
	{
		getGameObject(sName1)->getCollidable()->multiplyVelocity(1.8);
		m_flipperLeft->setState(Flipper::FlipperStates::FALLING);
	}
}