/**
The PlayerController is a configurations handler for any settings that the player can modify.

Calling the "toggle" functionality on a setting will switch the setting to the opposite of its
current true or false value.

The settings stored in the controller can be edited at any time, but should generally be done
so through the use of a user interface and at a time where it is natural the the player (such
as on an options menu).

The controller contains no functionality for loading or saving a configuration file, and will
return to hardcoded default values whenever the game is relaunched.
*/

#ifndef PlayerController_H
#define PlayerController_H

#include <SFML/Graphics.hpp>

class PlayerController
{
	public:

		static PlayerController* getInstance();
		void resetAll();
		void resetBindings();
		void setBind_leftFlipper(sf::Keyboard::Key key);
		void setBind_rightFlipper(sf::Keyboard::Key key);
		void setBind_launcher(sf::Keyboard::Key key);
		void toggleMusic();
		void toggleHotkeys();
		void toggleSnowfall();
		bool getMusicEnabled();
		bool getHotkeysEnabled();
		bool getSnowfallEnabled();
		sf::Keyboard::Key getBind_leftFlipper() const;
		sf::Keyboard::Key getBind_rightFlipper() const;
		sf::Keyboard::Key getBind_launcher() const;

	protected:
	
	private:
		static bool bInstanceExists;
		static PlayerController* instance;
		bool m_bMusicEnabled;		
		bool m_bHotkeysEnabled;
		bool m_bSnowfallEnabled;
		sf::Keyboard::Key m_bindLeftFlipper;
		sf::Keyboard::Key m_bindRightFlipper;
		sf::Keyboard::Key m_bindLauncher;		
		
		PlayerController();
};

#endif