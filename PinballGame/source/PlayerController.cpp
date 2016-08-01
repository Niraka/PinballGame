#include "PlayerController.h"

bool PlayerController::bInstanceExists;
PlayerController* PlayerController::instance;

/**
Constructs a default PlayerController. */
PlayerController::PlayerController()
{
	m_bMusicEnabled = true;
	m_bHotkeysEnabled = true;
	m_bSnowfallEnabled = true;
	m_bindLeftFlipper = sf::Keyboard::Z;
	m_bindRightFlipper = sf::Keyboard::X;
	m_bindLauncher = sf::Keyboard::M;
}

/**
Returns a pointer to the PlayerController object. If the PlayerController does not already exist, it is created
and returned.

@return A pointer to the PlayerController. */
PlayerController* PlayerController::getInstance()
{
	if (bInstanceExists)
	{
		return instance;
	}
	else
	{
		instance = new PlayerController();
		bInstanceExists = true;
		return instance;
	}
}

/**
Resets all of the settings and keybindings to their default values. */
void PlayerController::resetAll()
{
	m_bMusicEnabled = true;
	m_bHotkeysEnabled = true;
	m_bSnowfallEnabled = true;
	m_bindLeftFlipper = sf::Keyboard::Z;
	m_bindRightFlipper = sf::Keyboard::X;
	m_bindLauncher = sf::Keyboard::M;
}

/**
Resets the keybindings to their default values. */
void PlayerController::resetBindings()
{
	m_bindLeftFlipper = sf::Keyboard::Z;
	m_bindRightFlipper = sf::Keyboard::X;
	m_bindLauncher = sf::Keyboard::M;
}

/**
Sets the keybinding for the left flipper to the given key. 

@param key The key. */
void PlayerController::setBind_leftFlipper(sf::Keyboard::Key key)
{
	m_bindLeftFlipper = key;
}

/**
Sets the keybinding for the right flipper to the given key.

@param key The key. */
void PlayerController::setBind_rightFlipper(sf::Keyboard::Key key)
{
	m_bindRightFlipper = key;
}

/**
Sets the keybinding for the launcher to the given key.

@param key The key. */
void PlayerController::setBind_launcher(sf::Keyboard::Key key)
{
	m_bindLauncher = key;
}

/**
Toggles the music enabled flag. */
void PlayerController::toggleMusic()
{
	m_bMusicEnabled = !m_bMusicEnabled;
}

/**
Toggles the hotkeys enabled flag. */
void PlayerController::toggleHotkeys()
{
	m_bHotkeysEnabled = !m_bHotkeysEnabled;
}

/**
Toggles the snowfall enabled flag. */
void PlayerController::toggleSnowfall()
{
	m_bSnowfallEnabled = !m_bSnowfallEnabled;
}

/**
Returns true if music is enabled.

@return True if music is enabled. */
bool PlayerController::getMusicEnabled()
{
	return m_bMusicEnabled;
}

/**
Returns true if menu hotkeys are enabled.

@return True if menu hotkeys are enabled. */
bool PlayerController::getHotkeysEnabled()
{
	return m_bHotkeysEnabled;
}

/**
Returns true if the snowfall animation is enabled. 

@return True if the snowfall animation is enabled. */
bool PlayerController::getSnowfallEnabled()
{
	return m_bSnowfallEnabled;
}

/**
Returns an sf::Key keybinding that represents the left flipper control. 

@return The keybinding representing the left flipper. */
sf::Keyboard::Key PlayerController::getBind_leftFlipper() const
{
	return m_bindLeftFlipper;
}

/**
Returns an sf::Key keybinding that represents the right flipper control.

@return The keybinding representing the left flipper. */
sf::Keyboard::Key PlayerController::getBind_rightFlipper() const
{
	return m_bindRightFlipper;
}

/**
Returns an sf::Key keybinding that represents the launcher control.

@return The keybinding representing the launcher. */
sf::Keyboard::Key PlayerController::getBind_launcher() const
{
	return m_bindLauncher;
}