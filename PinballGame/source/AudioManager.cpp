#include "AudioManager.h"

bool AudioManager::bInstanceExists;
AudioManager* AudioManager::instance;

/**
Constructs a new AudioManager object. A default working directory of "audio/" is assigned. */
AudioManager::AudioManager()
{
	m_sWorkingDirectory = "audio/";
}

/**
Returns a pointer to the AudioManager object. If the AudioManager does not already exist, it is created and
returned.

@return A pointer to the AudioManager. */
AudioManager* AudioManager::getInstance()
{
	if (bInstanceExists)
	{
		return instance;
	}
	else
	{
		instance = new AudioManager();
		bInstanceExists = true;
		return instance;
	}
}

/**
Sets the working directory. Calls to loadSoundBuffer() or loadMusic() will append the working directory
to the beginning of the file path.

@param sDirectory The directory to set the working directory to. */
void AudioManager::setWorkingDirectory(std::string sDirectory)
{
	m_sWorkingDirectory = sDirectory;
}

/**
Loads a SoundBuffer from the given file and stores it under the given key. Check the sf::SoundBuffer 
documentation for information on supported audio types.

Loading a SoundBuffer with a key that already exists will NOT overwrite existing SoundBuffers. 

@see sf::SoundBuffer
@param sKey The key to assign to the loaded SoundBuffer.
@param sFile The file to load the SoundBuffer from, extension included. 
@return True if loading the SoundBuffer was successful. False otherwise. */
bool AudioManager::loadSoundBuffer(std::string sKey, std::string sFile)
{
	if (soundBufferExists(sKey))
	{
		return false;
	}

	sf::SoundBuffer sb;
	if (sb.loadFromFile(m_sWorkingDirectory + sFile))
	{
		m_soundBuffers[sKey] = sb;
		return true;
	}
	else
	{
		return false;
	}
}

/**
Loads a Music from the given file and stores it under the given key. Check the sf::Music
documentation for information on supported audio types.

Loading a Music with a key that already exists will NOT overwrite existing Musics.

@see sf::Music
@param sKey The key to assign to the loaded Music.
@param sFile The file to load the Music from, extension included.
@return True if loading the Music was successful. False otherwise. */
bool AudioManager::loadMusic(std::string sKey, std::string sFile)
{
	if (musicExists(sKey))
	{
		return false;
	}

	// The underlying implementation of a music is a stream, and thus the object is non-copyable. 
	// Therefore the resource must be allocated to the heap and stored as a pointer.
	sf::Music* m = new sf::Music();
	if (m->openFromFile(m_sWorkingDirectory + sFile))
	{
		m_musics[sKey] = m;
		return true;
	}
	else
	{
		return false;
	}
}

/**
Returns true if a SoundBuffer with the given key exists.

@param sKey The key of the SoundBuffer to search for.
@return True if a SoundBuffer with the given key exists. False otherwise. */
bool AudioManager::soundBufferExists(std::string sKey)
{
	if (m_soundBuffers.find(sKey) != m_soundBuffers.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
Returns true if a Music with the given key exists.

@param sKey The key of the Music to search for.
@return True if a Music with the given key exists. False otherwise. */
bool AudioManager::musicExists(std::string sKey)
{
	if (m_musics.find(sKey) != m_musics.end())
	{
		return true;
	}
	else
	{
		return false;
	}
}

/**
Clears a SoundBuffer, identified by key, from the AudioManager. If no SoundBuffer with the given key exists,
no action is taken.

@param sKey The key of the SoundBuffer to clear. */
void AudioManager::clearSoundBuffer(std::string sKey)
{
	m_soundBuffers.erase(sKey);
}

/**
Clears a Music, identified by key, from the AudioManager. If no Music with the given key exists, no action
is taken.

@param sKey The key of the Music to clear. */
void AudioManager::clearMusic(std::string sKey)
{
	delete &m_musics[sKey];
	m_musics.erase(sKey);
}

/**
Clears all SoundBuffers from the AudioManager. */
void AudioManager::clearSoundBuffers()
{
	m_soundBuffers.clear();
}

/**
Clears all Musics from the AudioManager. */
void AudioManager::clearMusics()
{
	for (std::map<std::string, sf::Music*>::iterator it = m_musics.begin(); it != m_musics.end(); ++it)
	{
		delete &it;
	}
	m_musics.clear();
}

/**
Returns a pointer to an sf::SoundBuffer with the given key. 

@param sKey The key of the SoundBuffer to get.
@return A pointer to an sf::SoundBuffer, or a nullptr if the key did not exist. */
sf::SoundBuffer* AudioManager::getSoundBuffer(std::string sKey)
{
	return &m_soundBuffers[sKey];
}

/**
Returns a pointer to an sf::Music with the given key.

@param sKey The key of the Music to get.
@return A pointer to an sf::Music, or a nullptr if the key did not exist. */
sf::Music* AudioManager::getMusic(std::string sKey)
{
	return m_musics[sKey];
}