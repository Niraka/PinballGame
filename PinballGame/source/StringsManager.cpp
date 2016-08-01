#include "StringsManager.h"

bool StringsManager::bInstanceExists;
StringsManager* StringsManager::instance;

/**
Constructs a new StringsManager object. A default working directory of "strings/" is assigned. */
StringsManager::StringsManager()
{
	m_sStringsDirectory = "strings/";
}

/**
Returns a pointer to the StringsManager object. If the StringsManager does not already exist, it is created
and returned.

@return A pointer to the StringsManager. */
StringsManager* StringsManager::getInstance()
{
	if (bInstanceExists)
	{
		return instance;
	}
	else
	{
		instance = new StringsManager();
		bInstanceExists = true;
		return instance;
	}
}

/**
Sets the working directory. Calls to loadStrings() will append the working directory to the beginning of
the file path.

@param sDirectory The directory to set the working directory to. */
void StringsManager::setWorkingDirectory(std::string sDirectory)
{
	m_sStringsDirectory = sDirectory;
}

/**
Loads all string values from the given text file in to the StringsManager. A strings file should 
have the .txt extension and should adhere to the formatting rules stated within the header of a strings
file.

Loading a string with a key that already existed will overwrite the current value with the new value.

@param file The name of the file to load, extension included. */
void StringsManager::loadStrings(std::string file)
{
	std::string sLine;
	std::string sKey;
	std::string sValue;
	std::ifstream inputStream;
	inputStream.open(m_sStringsDirectory + file);

	if (!inputStream.is_open())
	{
		return;
	}

	while (std::getline(inputStream, sLine))
	{
		// Skip completely empty lines
		if (sLine.empty())
		{
			continue;
		}

		// Skip the line if it begins with a #, space, or new line
		if (sLine.at(0) == '#' || sLine.at(0) == '/n' || sLine.at(0) == ' ')
		{
			continue;
		}

		sKey = sLine.substr(0, sLine.find_first_of(' '));
		sValue = sLine.substr(sLine.find_first_of(' '), sLine.length());

		// Trims excess whitespace from the front of the line
		sValue = sValue.substr(sValue.find_first_not_of(' '), sValue.length());
		m_sStrings[sKey] = sValue;	
	}
	inputStream.close();
}

/**
Clears all strings from the StringsManager whose keys are contained within the given strings file. A strings file should 
have the .txt extension and should adhere to the formatting rules stated within the header of a strings
file.

Note that this function still utilises file I/O.

@param file The name of the file to load, extension included. */
void StringsManager::clearStrings(std::string file)
{
	std::string sLine;
	std::ifstream inputStream;
	inputStream.open(m_sStringsDirectory + file);

	if (!inputStream.is_open())
	{
		return;
	}

	while (std::getline(inputStream, sLine))
	{
		// Skip completely empty lines
		if (sLine.empty())
		{
			continue;
		}

		// Skip the line if it begins with a #, space, or new line
		if (sLine.at(0) == '#' || sLine.at(0) == '/n' || sLine.at(0) == ' ')
		{
			continue;
		}

		sLine = sLine.substr(0, sLine.find_first_of(' '));
		m_sStrings.erase(sLine);
		
	}
	inputStream.close();
}

/**
Clears all strings from the StringsManager. */
void StringsManager::clearStrings()
{
	m_sStrings.clear();
}

/**
Returns a pointer to a string with the given key.

@param sKey The key of the string to get. 
@return A pointer to a string, or a nullptr if the key did not exist */
std::string* StringsManager::getString(std::string sKey)
{
	return &m_sStrings[sKey];
}