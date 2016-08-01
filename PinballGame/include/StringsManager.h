/**
The StringsManager is a singleton string resource management class that stores
std::string objects in a convenient central location.

All std::string objects stored within the StringsManager are assigned (by the programmer) 
unique std::string keys that can be used to retrieve the object for as long as it is 
in memory.

Generally speaking the StringsManager is intended for use with longer strings, such as quest
text or a set of instructions. 
*/

#ifndef StringsManager_H
#define StringsManager_H

#include <string>
#include <map>
#include <iostream>
#include <fstream>

class StringsManager
{
	public:
		static StringsManager* getInstance();
		void setWorkingDirectory(std::string sDirectory);
		void loadStrings(std::string sFile);
		void clearStrings(std::string sFile);
		void clearStrings();
		std::string* getString(std::string sKey);

	protected:

	private:
		static bool bInstanceExists;
		static StringsManager* instance;
		std::string m_sStringsDirectory;
		std::map<std::string, std::string> m_sStrings;

		StringsManager();
};

#endif