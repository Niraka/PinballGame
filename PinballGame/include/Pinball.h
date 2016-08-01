/**
The Pinball class is the main controller class for the entire program.

The class is responsible for the construction of all of the main components of the program, include the initial UI,
the snowfall animation, the window and the game loop.

The Pinball class also handles any and all input events occurring on the window. 
*/


#ifndef Pinball_H
#define Pinball_H

#include <SFML/Graphics.hpp>

#include "UIText.h"
#include "UIButton.h"
#include "UIFrame.h"
#include "UIImage.h"
#include "MapAvalanche.h"
#include "MapSnowTunnels.h"
#include "FontManager.h"
#include "TextureManager.h"
#include "PlayerController.h"
#include "AnimationSnowfall.h"
#include "AudioManager.h"
#include "StringsManager.h"
#include "UIManager.h"
#include "UIButtonListener.h"
#include "ScoresManager.h"
#include "Map.h"
#include "MapEventListener.h"

class Pinball : public UIButtonListener, UIComponentListener, MapEventListener
{
	public:
		enum GameState {IN_MENU, IN_GAME};
		enum Maps {NO_MAP, AVALANCHE, SNOW_TUNNELS};

		unsigned int m_uiWindowWidth;
		unsigned int m_uiWindowHeight;

		Pinball();

		void gameLoop();
		void changeState(GameState newState);
		void changeUI(UIManager::UIs targetUI);
		void loadUI(UIManager::UIs ui);
		void unloadUI(UIManager::UIs ui);
		void loadMap(Maps map);
		void unloadMap();
		void closeGame();

		virtual void buttonDepressed(std::string sButtonName);
		virtual void buttonReleased(std::string sButtonName);
		virtual void componentDepressed(std::string sComponentName);
		virtual void componentReleased(std::string sComponentName);
		virtual void componentHovered(std::string sComponentName);
		virtual void componentUnhovered(std::string sComponentName);
		virtual void gameOver(Map* m);
	
	protected:

	private:
		bool m_bStateUpdated;
		sf::RenderWindow m_Window;
		GameState m_GameState;
		AnimationSnowfall m_AnimationSnowfall;
		PlayerController* m_pPlayerController;	
		UIManager m_UIManager;
		UIManager::UIs m_currentUI;
		Maps m_currentMap;
		Map* m_pMap;
		ScoresManager m_ScoresManager;

		// Background
		sf::Sprite m_Background;

		// Resource management components
		FontManager* m_pFontManager;
		TextureManager* m_pTextureManager;
		AudioManager* m_pAudioManager;
		StringsManager* m_pStringsManager;		
};

#endif
