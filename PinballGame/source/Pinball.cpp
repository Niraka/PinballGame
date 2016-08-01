#include <iostream>
#include "Pinball.h"

/**
Constructs a default Pinball object. */
Pinball::Pinball()
{
	// Instantiate singleton resource managers and the player controller. These should not be deconstructed
	// for the lifetime of the program
	m_pFontManager = FontManager::getInstance();
	m_pAudioManager = AudioManager::getInstance();
	m_pTextureManager = TextureManager::getInstance();
	m_pStringsManager = StringsManager::getInstance();
	m_pPlayerController = PlayerController::getInstance();

	// Set some default values
	m_uiWindowWidth = 1200;
	m_uiWindowHeight = 800;
	m_GameState = GameState::IN_MENU;
	m_currentUI = UIManager::UIs::NO_UI;
	m_currentMap = Maps::NO_MAP;
	m_bStateUpdated = false;

	// Create the window and disable the option to resize it
	m_Window.create(sf::VideoMode(m_uiWindowWidth, m_uiWindowHeight, 32U), "Pinball", sf::Style::Close);
	m_Window.setFramerateLimit(60);

	// Configure background
	m_pTextureManager->setWorkingDirectory("../data/textures/");	
	m_pTextureManager->loadTexture("background", "menus/background.png");
	sf::Texture* t = m_pTextureManager->getTexture("background");	
	m_Background.setPosition(0, 0);
	m_Background.setTexture(*t);
	if (t->getSize().x != 0 && t->getSize().y != 0)
	{
		m_Background.setScale((float)m_uiWindowWidth / t->getSize().x, (float)m_uiWindowHeight / t->getSize().y);
	}

	// Create the snowfall animation	
	m_pTextureManager->loadTexture("obj_snowflake", "menus/snowflake2.png");
	m_AnimationSnowfall.setTexture(m_pTextureManager->getTexture("obj_snowflake"));
	m_AnimationSnowfall.setFallSpeed(1.2);
	m_AnimationSnowfall.setWindowSize(m_uiWindowWidth, m_uiWindowHeight);
	m_AnimationSnowfall.setDensity(12);
	
	// Enable background music
	m_pAudioManager->setWorkingDirectory("../data/audio/");
	m_pAudioManager->loadMusic("music", "music.wav");
	sf::Music* music = m_pAudioManager->getMusic("music");
	if (music)
	{
		music->play();
		music->setLoop(true);
	}

	// Load any existing scores
	m_ScoresManager.loadScores("highscores.txt");
}

/**
Switches the game state to the new state. The new state will take effect on the next game loop iteration.

@param newState The state to switch to. */
void Pinball::changeState(GameState newState)
{
	m_GameState = newState;
	m_bStateUpdated = true;
}

/**
Processes all of the games per-tick logic. The order of operation is as follows:
1) Event handling
2) GameState switching
3) Logic updates (including collision detection and resolution)
4) Rendering the current frame. */
void Pinball::gameLoop()
{	
	while (m_Window.isOpen())
	{		
		// Event handling
		sf::Event event;
		float iMouseX = sf::Mouse::getPosition(m_Window).x;
		float iMouseY = sf::Mouse::getPosition(m_Window).y;
		
		while (m_Window.pollEvent(event))
		{
			// Pick code path depending on current game state
			if (m_GameState == GameState::IN_MENU)
			{
				if (event.type == sf::Event::Closed)
				{
					closeGame();
				}
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					m_UIManager.checkDepressEvents(iMouseX, iMouseY);
				}
				else if (event.type == sf::Event::MouseButtonReleased)
				{
					m_UIManager.checkReleaseEvents(iMouseX, iMouseY);
				}
				else if (event.type == sf::Event::LostFocus)
				{
					m_UIManager.checkReleaseEvents(iMouseX, iMouseY);
				}
				else if (event.type == sf::Event::KeyReleased)
				{
					if (m_pPlayerController->getHotkeysEnabled())
					{
						if (event.key.code == sf::Keyboard::P)
						{
							UIComponent* u = m_UIManager.getUIComponentRef("btnMainPlay");
							UIButton* btn = dynamic_cast<UIButton*>(u);
							btn->simulateDepress();
							btn->simulateRelease();
						}
						else if (event.key.code == sf::Keyboard::I)
						{
							UIComponent* u = m_UIManager.getUIComponentRef("btnMainInstructions");
							UIButton* btn = dynamic_cast<UIButton*>(u);
							btn->simulateDepress();
							btn->simulateRelease();
						}
						else if (event.key.code == sf::Keyboard::O)
						{
							UIComponent* u = m_UIManager.getUIComponentRef("btnMainOptions");
							UIButton* btn = dynamic_cast<UIButton*>(u);
							btn->simulateDepress();
							btn->simulateRelease();
						}
						else if (event.key.code == sf::Keyboard::H)
						{
							UIComponent* u = m_UIManager.getUIComponentRef("btnMainHighScores");
							UIButton* btn = dynamic_cast<UIButton*>(u);
							btn->simulateDepress();
							btn->simulateRelease();
						}
						else if (event.key.code == sf::Keyboard::R && m_currentUI == UIManager::UIs::HIGHSCORES)
						{
							UIComponent* u = m_UIManager.getUIComponentRef("btnHighScoresReset");
							UIButton* btn = dynamic_cast<UIButton*>(u);
							btn->simulateDepress();
							btn->simulateRelease();
						}
						else if (event.key.code == sf::Keyboard::Q)
						{
							closeGame();
						}
					}
				}
			}
			else if (m_GameState == GameState::IN_GAME)
			{
				if (event.type == sf::Event::Closed)
				{
					m_pMap->launchEvent_gameOver();
					closeGame();
				}
				else if (event.type == sf::Event::MouseButtonPressed)
				{
					m_UIManager.checkDepressEvents(iMouseX, iMouseY);
				}
				else if (event.type == sf::Event::MouseButtonReleased)
				{
					m_UIManager.checkReleaseEvents(iMouseX, iMouseY);
				}
				else if (event.type == sf::Event::LostFocus)
				{
					m_UIManager.checkReleaseEvents(iMouseX, iMouseY);
				}
				else if (event.type == sf::Event::KeyPressed)
				{
					// Handle key presses
					if (m_pMap->getState() == Map::State::WAITING && event.key.code == m_pPlayerController->getBind_launcher())
					{
						m_pMap->setState(Map::State::LAUNCHING);
						m_pMap->resetClock();
					}
					else if (event.key.code == m_pPlayerController->getBind_leftFlipper())
					{
						GameObject* g = m_pMap->getGameObject("flipperLeft");
						FlipperLeft* fl = dynamic_cast<FlipperLeft*>(g);
						fl->setState(Flipper::FlipperStates::RISING);
					}
					else if (event.key.code == m_pPlayerController->getBind_rightFlipper())
					{
						GameObject* g = m_pMap->getGameObject("flipperRight");
						FlipperRight* fl = dynamic_cast<FlipperRight*>(g);
						fl->setState(Flipper::FlipperStates::RISING);
					}
				}
				else if (event.type == sf::Event::KeyReleased)
				{
					// Handle key releases
					if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Q)
					{
						UIComponent* u = m_UIManager.getUIComponentRef("btnQuit");
						UIButton* btn = dynamic_cast<UIButton*>(u);
						btn->simulateDepress();
						btn->simulateRelease();
					}
					else if (event.key.code == sf::Keyboard::R)
					{
						UIComponent* u = m_UIManager.getUIComponentRef("btnReset");
						UIButton* btn = dynamic_cast<UIButton*>(u);
						btn->simulateDepress();
						btn->simulateRelease();
					}
					else if (event.key.code == m_pPlayerController->getBind_launcher() && m_pMap->getState() == Map::State::LAUNCHING)
					{
						m_pMap->setState(Map::State::PLAYING);
					}
				}
			}
		}

		// State modification
		if (m_bStateUpdated)
		{
			m_bStateUpdated = false;
			if (m_GameState == GameState::IN_MENU)
			{
				if (m_currentMap != Maps::NO_MAP)
				{
					unloadMap();
				}
				m_pMap->deleteUI(m_UIManager);
				loadUI(UIManager::UIs::MAIN);
			}
			else if (m_GameState == GameState::IN_GAME)
			{
				// Unload all loaded menus.
				if (m_UIManager.getUILoaded(UIManager::UIs::HIGHSCORES)) { unloadUI(UIManager::UIs::HIGHSCORES); }
				if (m_UIManager.getUILoaded(UIManager::UIs::OPTIONS)) { unloadUI(UIManager::UIs::OPTIONS); }
				if (m_UIManager.getUILoaded(UIManager::UIs::MAP_SELECTION)) { unloadUI(UIManager::UIs::MAP_SELECTION); }
				if (m_UIManager.getUILoaded(UIManager::UIs::INSTRUCTIONS)) { unloadUI(UIManager::UIs::INSTRUCTIONS); }
				if (m_UIManager.getUILoaded(UIManager::UIs::MAIN)) { unloadUI(UIManager::UIs::MAIN); }
				loadMap(m_currentMap);
			}
		}

		// Logic and rendering
		if (m_GameState == GameState::IN_MENU)
		{
			m_UIManager.checkHoverEvents(iMouseX, iMouseY);
			if (m_pPlayerController->getSnowfallEnabled())
			{
				m_AnimationSnowfall.update();
			}	

			// Rendering
			m_Window.clear(sf::Color::Blue);
			m_Window.draw(m_Background);
			if (m_pPlayerController->getSnowfallEnabled())
			{
				m_Window.draw(m_AnimationSnowfall);
			}	
			m_Window.draw(m_UIManager.getRootComponent());
			m_Window.display();
		}
		else if (m_GameState == GameState::IN_GAME)
		{
			m_UIManager.checkHoverEvents(iMouseX, iMouseY);
			m_pMap->update();
			if (m_pPlayerController->getSnowfallEnabled())
			{
				m_AnimationSnowfall.update();
			}	

			// Rendering
			m_Window.clear(sf::Color::Blue);
			m_Window.draw(m_Background);
			if (m_pPlayerController->getSnowfallEnabled())
			{
				m_Window.draw(m_AnimationSnowfall);
			}
			m_Window.draw(m_UIManager.getRootComponent());	
			m_Window.draw(*m_pMap);
			m_Window.display();
		}
	}
}

/**
Unloads the given ui from memory. 

@param ui The UI to unload. */
void Pinball::unloadUI(UIManager::UIs ui)
{
	if (ui == UIManager::UIs::MAIN)
	{
		UIDestructor d(m_UIManager);
		d.deconstructUI("../data/user_interfaces/menu/main_destructor.txt");
		m_UIManager.setUILoaded(UIManager::UIs::MAIN, false);
	}
	else if (ui == UIManager::UIs::MAP_SELECTION)
	{	
		UIDestructor d(m_UIManager);
		d.deconstructUI("../data/user_interfaces/menu/map_selection_destructor.txt");
		m_UIManager.setUILoaded(UIManager::UIs::MAP_SELECTION, false);
	}
	else if (ui == UIManager::UIs::INSTRUCTIONS)
	{
		UIDestructor d(m_UIManager);
		d.deconstructUI("../data/user_interfaces/menu/instructions_destructor.txt");
		m_UIManager.setUILoaded(UIManager::UIs::INSTRUCTIONS, false);
	}
	else if (ui == UIManager::UIs::HIGHSCORES)
	{
		UIDestructor d(m_UIManager);
		d.deconstructUI("../data/user_interfaces/menu/high_scores_destructor.txt");
		m_UIManager.setUILoaded(UIManager::UIs::HIGHSCORES, false);
	}
	else if (ui == UIManager::UIs::OPTIONS)
	{
		UIDestructor d(m_UIManager);
		d.deconstructUI("../data/user_interfaces/menu/options_destructor.txt");
		m_UIManager.setUILoaded(UIManager::UIs::OPTIONS, false);
	}
}

/**
Loads the given UI in to memory. 

@param ui The UI to load. */
void Pinball::loadUI(UIManager::UIs ui)
{
	if (ui == UIManager::UIs::MAIN)
	{
		m_currentUI = UIManager::UIs::MAIN;
		UIBuilder b(m_UIManager);
		b.buildUI("../data/user_interfaces/menu/main_constructor.txt", this);
		m_UIManager.setUILoaded(UIManager::UIs::MAIN, true);
	}
	else if (ui == UIManager::UIs::MAP_SELECTION)
	{
		m_currentUI = UIManager::UIs::MAP_SELECTION;
		UIBuilder b(m_UIManager);
		b.buildUI("../data/user_interfaces/menu/map_selection_constructor.txt", this);
		m_UIManager.setUILoaded(UIManager::UIs::MAP_SELECTION, true);

		// Configure component listeners
		UIComponent* u = m_UIManager.getUIComponentRef("imgMapSelectionAvalanche");
		u->addComponentListener(this);
		u = m_UIManager.getUIComponentRef("imgMapSelectionSnowTunnels");
		u->addComponentListener(this);
	}
	else if (ui == UIManager::UIs::INSTRUCTIONS)
	{
		m_currentUI = UIManager::UIs::INSTRUCTIONS;
		UIBuilder b(m_UIManager);
		b.buildUI("../data/user_interfaces/menu/instructions_constructor.txt", this);
		m_UIManager.setUILoaded(UIManager::UIs::INSTRUCTIONS, true);

		// Configure text
		UIText* txt = dynamic_cast<UIText*>(m_UIManager.getUIComponentRef("txtInstructionsInfo"));
		if (m_pPlayerController->getBind_launcher() == sf::Keyboard::M)
		{
			txt->setString(m_pStringsManager->getString("instructions_info_zxm"));
		}
		else if (m_pPlayerController->getBind_launcher() == sf::Keyboard::W)
		{
			txt->setString(m_pStringsManager->getString("instructions_info_adw"));
		}
		else if (m_pPlayerController->getBind_launcher() == sf::Keyboard::Num3)
		{
			txt->setString(m_pStringsManager->getString("instructions_info_123"));
		}
	}
	else if (ui == UIManager::UIs::HIGHSCORES)
	{
		m_currentUI = UIManager::UIs::HIGHSCORES;
		UIBuilder b(m_UIManager);
		b.buildUI("../data/user_interfaces/menu/high_scores_constructor.txt", this);
		m_UIManager.setUILoaded(UIManager::UIs::HIGHSCORES, true);

		// Configure high scores
		for (int i = 0; i < 8; i++)
		{
			UIComponent* u = m_UIManager.getUIComponentRef("txtHighScores" + std::to_string(i));
			UIText* txt = dynamic_cast<UIText*>(u);
			if (txt)
			{
				txt->setString(&std::to_string((int)m_ScoresManager.getScore(i)));
				txt->setAlignment(UIText::Alignment::CENTRE);
			}
		}
	}
	else if (ui == UIManager::UIs::OPTIONS)
	{
		m_currentUI = UIManager::UIs::OPTIONS;
		UIBuilder b(m_UIManager);
		b.buildUI("../data/user_interfaces/menu/options_constructor.txt", this);
		m_UIManager.setUILoaded(UIManager::UIs::OPTIONS, true);
	
		// Configure options
		UIImage* imgM = dynamic_cast<UIImage*>(m_UIManager.getUIComponentRef("imgOptionsMusicCheckbox"));
		UIImage* imgH = dynamic_cast<UIImage*>(m_UIManager.getUIComponentRef("imgOptionsHotkeysCheckbox"));
		UIImage* imgS = dynamic_cast<UIImage*>(m_UIManager.getUIComponentRef("imgOptionsSnowfallCheckbox"));
		if (m_pPlayerController->getMusicEnabled())
		{
			imgM->setTexture(m_pTextureManager->getTexture("checkbox_green"));
		}
		else
		{
			imgM->setTexture(m_pTextureManager->getTexture("checkbox_red"));
		}
		if (m_pPlayerController->getHotkeysEnabled())
		{
			imgH->setTexture(m_pTextureManager->getTexture("checkbox_green"));
		}
		else
		{
			imgH->setTexture(m_pTextureManager->getTexture("checkbox_red"));
		}
		if (m_pPlayerController->getSnowfallEnabled())
		{
			imgS->setTexture(m_pTextureManager->getTexture("checkbox_green"));
		}
		else
		{
			imgS->setTexture(m_pTextureManager->getTexture("checkbox_red"));
		}

		UIImage* imgZ = dynamic_cast<UIImage*>(m_UIManager.getUIComponentRef("imgOptionsZXMSet"));
		UIImage* imgA = dynamic_cast<UIImage*>(m_UIManager.getUIComponentRef("imgOptionsADWSet"));
		UIImage* img1 = dynamic_cast<UIImage*>(m_UIManager.getUIComponentRef("imgOptions123Set"));
		if (m_pPlayerController->getBind_launcher() == sf::Keyboard::M)
		{
			imgZ->setTexture(m_pTextureManager->getTexture("keyset_zxm_green"));
			imgA->setTexture(m_pTextureManager->getTexture("keyset_adw_red"));
			img1->setTexture(m_pTextureManager->getTexture("keyset_123_red"));
		}
		else if (m_pPlayerController->getBind_launcher() == sf::Keyboard::W)
		{
			imgZ->setTexture(m_pTextureManager->getTexture("keyset_zxm_red"));
			imgA->setTexture(m_pTextureManager->getTexture("keyset_adw_green"));
			img1->setTexture(m_pTextureManager->getTexture("keyset_123_red"));
		}
		else if (m_pPlayerController->getBind_launcher() == sf::Keyboard::Num3)
		{
			imgZ->setTexture(m_pTextureManager->getTexture("keyset_zxm_red"));
			imgA->setTexture(m_pTextureManager->getTexture("keyset_adw_red"));
			img1->setTexture(m_pTextureManager->getTexture("keyset_123_green"));
		}

		// Configure component listeners
		UIComponent* u = m_UIManager.getUIComponentRef("imgOptionsMusicCheckbox");
		u->addComponentListener(this); 
		u = m_UIManager.getUIComponentRef("imgOptionsHotkeysCheckbox");
		u->addComponentListener(this);
		u = m_UIManager.getUIComponentRef("imgOptionsSnowfallCheckbox");
		u->addComponentListener(this);
		u = m_UIManager.getUIComponentRef("imgOptionsZXMSet");
		u->addComponentListener(this);
		u = m_UIManager.getUIComponentRef("imgOptionsADWSet");
		u->addComponentListener(this);
		u = m_UIManager.getUIComponentRef("imgOptions123Set");
		u->addComponentListener(this);
	}
}

/**
Unloads the current map. */
void Pinball::unloadMap()
{
	m_pMap->clearGameObjects();
}

/**
Loads a map. Ensure that the current map is unloaded if there is one.

@param map The map to load. */
void Pinball::loadMap(Maps map)
{
	m_pStringsManager->clearStrings();
	m_pStringsManager->loadStrings("ingame.txt");

	m_currentMap = map;

	if (m_currentMap == Maps::AVALANCHE)
	{
		MapAvalanche* m = new MapAvalanche();
		m->setGravity(Vector2D(0, 350));
		m->build();
		m->createUI(this, m_UIManager);
		m->addMapEventListener(this);
		m_pMap = m;
	}
	else if (m_currentMap == Maps::SNOW_TUNNELS)
	{
		MapSnowTunnels* m = new MapSnowTunnels();
		m->setGravity(Vector2D(0, 350));
		m->build();
		m->createUI(this, m_UIManager);
		m->addMapEventListener(this);
		m_pMap = m;
	}
}

/**
Changes the current UI. 

@param targetUI The target UI. */
void Pinball::changeUI(UIManager::UIs targetUI)
{
	if (m_currentUI != targetUI)
	{
		UIComponent* u;
		switch (m_currentUI)
		{
		case UIManager::UIs::MAP_SELECTION:
			u = m_UIManager.getUIComponentRef("imgMapSelectionBackground");
			u->setActive(false);
			u->setVisible(false);
			break;
		case UIManager::UIs::INSTRUCTIONS:
			u = m_UIManager.getUIComponentRef("imgInstructionsBackground");
			u->setActive(false);
			u->setVisible(false);
			break;
		case UIManager::UIs::HIGHSCORES:
			u = m_UIManager.getUIComponentRef("imgHighScoresBackground");
			u->setActive(false);
			u->setVisible(false);
			break;
		case UIManager::UIs::OPTIONS:
			u = m_UIManager.getUIComponentRef("imgOptionsBackground");
			u->setActive(false);
			u->setVisible(false);
			break;
		}

		if (!m_UIManager.getUILoaded(targetUI))
		{
			// If the target menu is not the current and is not loaded, load it
			loadUI(targetUI);
		}
		else
		{
			// If the target menu is not the current and it is loaded, switch to it
			switch (targetUI)
			{
			case UIManager::UIs::MAP_SELECTION:
				u = m_UIManager.getUIComponentRef("imgMapSelectionBackground");
				u->setActive(true);
				u->setVisible(true);
				break;
			case UIManager::UIs::INSTRUCTIONS:
				u = m_UIManager.getUIComponentRef("imgInstructionsBackground");
				u->setActive(true);
				u->setVisible(true);
				break;
			case UIManager::UIs::HIGHSCORES:
				u = m_UIManager.getUIComponentRef("imgHighScoresBackground");
				u->setActive(true);
				u->setVisible(true);
				break;
			case UIManager::UIs::OPTIONS:
				u = m_UIManager.getUIComponentRef("imgOptionsBackground");
				u->setActive(true);
				u->setVisible(true);
				break;
			}

			m_currentUI = targetUI;
		}
	}
}

/**
This function is called when any UIButton this Pinball is listening to launches a button depressed event.

@param sButtonName The name of the button the event occurred on. */
void Pinball::buttonDepressed(std::string sButtonName)
{
}

/**
This function is called when any UIButton this Pinball is listening to launches a button released event.

@param sButtonName The name of the button the event occurred on. */
void Pinball::buttonReleased(std::string sButtonName)
{
	if (sButtonName == "btnMainPlay")
	{
		changeUI(UIManager::UIs::MAP_SELECTION);
	}
	else if (sButtonName == "btnMainInstructions")
	{
		changeUI(UIManager::UIs::INSTRUCTIONS);
	}
	else if (sButtonName == "btnMainHighScores")
	{
		changeUI(UIManager::UIs::HIGHSCORES);
	}
	else if (sButtonName == "btnMainOptions")
	{
		changeUI(UIManager::UIs::OPTIONS);
	}
	else if (sButtonName == "btnMainQuit")
	{
		closeGame();
	}
	else if (sButtonName == "btnHighScoresReset")
	{
		m_ScoresManager.resetScores();
		m_ScoresManager.saveScores("highscores.txt");

		for (int i = 0; i < 8; i++)
		{
			UIComponent* u = m_UIManager.getUIComponentRef("txtHighScores" + std::to_string(i));
			UIText* txt = dynamic_cast<UIText*>(u);
			if (txt)
			{
				txt->setString(&std::to_string((int)m_ScoresManager.getScore(i)));
				txt->setAlignment(UIText::Alignment::CENTRE);
			}
		}
	}
	else if (sButtonName == "btnQuit")
	{
		m_pMap->launchEvent_gameOver();
		changeState(GameState::IN_MENU);
	}
	else if (sButtonName == "btnReset")
	{
		m_pMap->resetMap();
	}
}

/**
This function is called when any UIComponent this Pinball is listening to launches a component depressed event.

@param sComponentName The name of the component that event occurred on. */
void Pinball::componentDepressed(std::string sComponentName)
{
	if (sComponentName == "imgMapSelectionAvalanche")
	{
		changeState(GameState::IN_GAME);
		m_currentMap = Maps::AVALANCHE;
	}
	else if (sComponentName == "imgMapSelectionSnowTunnels")
	{
		changeState(GameState::IN_GAME);
		m_currentMap = Maps::SNOW_TUNNELS;
	}
	else if (sComponentName == "imgOptionsMusicCheckbox")
	{
		UIComponent* u = m_UIManager.getUIComponentRef("imgOptionsMusicCheckbox");
		UIImage* i = dynamic_cast<UIImage*>(u);
		m_pPlayerController->toggleMusic();
		if (m_pPlayerController->getMusicEnabled())
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_green"));
			sf::Music* music = m_pAudioManager->getMusic("music");
			if (music)
			{
				music->play();
			}
		}
		else
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_red"));	
			sf::Music* music = m_pAudioManager->getMusic("music");
			if (music)
			{
				music->pause();
			}
		}	
	}
	else if (sComponentName == "imgOptionsHotkeysCheckbox")
	{
		UIComponent* u = m_UIManager.getUIComponentRef("imgOptionsHotkeysCheckbox");
		UIImage* i = dynamic_cast<UIImage*>(u);
		m_pPlayerController->toggleHotkeys();
		if (m_pPlayerController->getHotkeysEnabled())
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_green"));
		}
		else
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_red"));
		}
	}
	else if (sComponentName == "imgOptionsSnowfallCheckbox")
	{
		UIComponent* u = m_UIManager.getUIComponentRef("imgOptionsSnowfallCheckbox");
		UIImage* i = dynamic_cast<UIImage*>(u);
		m_pPlayerController->toggleSnowfall();
		if (m_pPlayerController->getSnowfallEnabled())
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_green"));
		}
		else
		{
			i->setTexture(m_pTextureManager->getTexture("checkbox_red"));
		}
	}
	else if (sComponentName == "imgOptionsZXMSet")
	{
		UIComponent* u = m_UIManager.getUIComponentRef("imgOptionsZXMSet");
		UIImage* i = dynamic_cast<UIImage*>(u);
		i->setTexture(m_pTextureManager->getTexture("keyset_zxm_green"));
		u = m_UIManager.getUIComponentRef("imgOptionsADWSet");
		i = dynamic_cast<UIImage*>(u);
		i->setTexture(m_pTextureManager->getTexture("keyset_adw_red"));
		u = m_UIManager.getUIComponentRef("imgOptions123Set");
		i = dynamic_cast<UIImage*>(u);
		i->setTexture(m_pTextureManager->getTexture("keyset_123_red"));
		m_pPlayerController->setBind_leftFlipper(sf::Keyboard::Z);
		m_pPlayerController->setBind_rightFlipper(sf::Keyboard::X);
		m_pPlayerController->setBind_launcher(sf::Keyboard::M);

		// Configure text
		UIText* txt = dynamic_cast<UIText*>(m_UIManager.getUIComponentRef("txtInstructionsInfo"));
		if (txt)
		{
			txt->setString(m_pStringsManager->getString("instructions_info_zxm"));
		}	
	}
	else if (sComponentName == "imgOptionsADWSet")
	{
		UIComponent* u = m_UIManager.getUIComponentRef("imgOptionsADWSet");
		UIImage* i = dynamic_cast<UIImage*>(u);
		i->setTexture(m_pTextureManager->getTexture("keyset_adw_green"));
		u = m_UIManager.getUIComponentRef("imgOptionsZXMSet");
		i = dynamic_cast<UIImage*>(u);
		i->setTexture(m_pTextureManager->getTexture("keyset_zxm_red"));
		u = m_UIManager.getUIComponentRef("imgOptions123Set");
		i = dynamic_cast<UIImage*>(u);
		i->setTexture(m_pTextureManager->getTexture("keyset_123_red"));
		m_pPlayerController->setBind_leftFlipper(sf::Keyboard::A);
		m_pPlayerController->setBind_rightFlipper(sf::Keyboard::D);
		m_pPlayerController->setBind_launcher(sf::Keyboard::W);

		// Configure text
		UIText* txt = dynamic_cast<UIText*>(m_UIManager.getUIComponentRef("txtInstructionsInfo"));
		if (txt)
		{
			txt->setString(m_pStringsManager->getString("instructions_info_adw"));
		}
	}
	else if (sComponentName == "imgOptions123Set")
	{
		UIComponent* u = m_UIManager.getUIComponentRef("imgOptions123Set");
		UIImage* i = dynamic_cast<UIImage*>(u);
		i->setTexture(m_pTextureManager->getTexture("keyset_123_green"));
		u = m_UIManager.getUIComponentRef("imgOptionsZXMSet");
		i = dynamic_cast<UIImage*>(u);
		i->setTexture(m_pTextureManager->getTexture("keyset_zxm_red"));
		u = m_UIManager.getUIComponentRef("imgOptionsADWSet");
		i = dynamic_cast<UIImage*>(u);
		i->setTexture(m_pTextureManager->getTexture("keyset_adw_red"));
		m_pPlayerController->setBind_leftFlipper(sf::Keyboard::Num1);
		m_pPlayerController->setBind_rightFlipper(sf::Keyboard::Num2);
		m_pPlayerController->setBind_launcher(sf::Keyboard::Num3);

		// Configure text
		UIText* txt = dynamic_cast<UIText*>(m_UIManager.getUIComponentRef("txtInstructionsInfo"));
		if (txt)
		{
			txt->setString(m_pStringsManager->getString("instructions_info_123"));
		}
	}
}

/**
This function is called when any UIComponent this Pinball is listening to launches a component released event.

@param sComponentName The name of the component that event occurred on. */
void Pinball::componentReleased(std::string sComponentName)
{
}

/**
This function is called when any UIComponent this Pinball is listening to launches a component hovered event.

@param sComponentName The name of the component that event occurred on. */
void Pinball::componentHovered(std::string sComponentName)
{
}

/**
This function is called when any UIComponent this Pinball is listening to launches a component unhovered event.

@param sComponentName The name of the component that event occurred on. */
void Pinball::componentUnhovered(std::string sComponentName)
{
}

/**
This function is called when any Map this Pinball is listening to launches a game over event. 

@param pMap The map the event occurred on. */
void Pinball::gameOver(Map* pMap)
{
	m_ScoresManager.addScore(pMap->getScore());
	m_pMap->setState(Map::State::WAITING);
}

/**
Call this function when the game is closing. */
void Pinball::closeGame()
{
	m_ScoresManager.saveScores("highscores.txt");
	m_Window.close();
}