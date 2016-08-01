/**
The AudioManager is a singleton audio resource management class that stores
all sf::SoundBuffer and sf::Music objects in a convenient central location.

All SoundBuffer and Music objects stored within the AudioManager are assigned 
(by the programmer) unique std::string keys that can be used to retrieve the
object for as long as it is in memory.

Note that while a SoundBuffer and a Music may share the same key, two Music objects
or two SoundBuffer objects may not.
*/


#ifndef AudioManager_H
#define AudioManager_H

#include <SFML/Audio.hpp>
#include <map>

class AudioManager
{
	public:
		static AudioManager* getInstance();

		void setWorkingDirectory(std::string sDirectory);
		bool loadSoundBuffer(std::string sKey, std::string sFile);
		bool soundBufferExists(std::string sKey);
		void clearSoundBuffer(std::string sKey);
		void clearSoundBuffers();
		bool loadMusic(std::string sKey, std::string sFile); 
		bool musicExists(std::string sKey);
		void clearMusic(std::string sKey);
		void clearMusics();

		sf::SoundBuffer* getSoundBuffer(std::string sKey);
		sf::Music* getMusic(std::string sKey);

	protected:

	private:		
		static bool bInstanceExists;
		static AudioManager* instance;
		std::string m_sWorkingDirectory;
		std::map<std::string, sf::SoundBuffer> m_soundBuffers;
		std::map<std::string, sf::Music*> m_musics;
		
		AudioManager();
};

#endif