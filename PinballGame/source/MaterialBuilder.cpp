#include "MaterialBuilder.h"

/**
Constructs a default MaterialBuilder. */
MaterialBuilder::MaterialBuilder()
{
}

/**
Attempts to build and add to a MaterialsManager a Material from a given vector of strings. Adding
a Material with a name that already existed will overwrite the existing Material in the manager.

@param sStrings A vector of strings that will be parsed as Material properties. 
@param mm The MaterialsManager to add the Material to. */
void MaterialBuilder::buildMaterial(std::vector<std::string>& sStrings, MaterialsManager& mm)
{
	// Parsing temporary values
	std::string sKey;
	std::string sValue;
	int equalsChar = 0;

	// Values for building a Material		
	// Fill with default values as a nonsense-guard
	std::string sName = "Unknown value";
	float fDensity = 1.f;
	float fRestitution = 1.f;
	float fStaticFriction = 0.f;
	float fDynamicFriction = 0.f;

	// Parse properties
	for (std::vector<std::string>::iterator it = sStrings.begin(); it != sStrings.end(); ++it)
	{
		// Split the line in to key and value components
		equalsChar = (*it).find_first_of('=');
		sKey = (*it).substr(0, equalsChar);
		sValue = (*it).substr(equalsChar + 1, (*it).length());

		// Disregard lines where a key or value was missing
		if (sKey == "" || sValue == "")
		{
			continue;
		}		

		if (sKey == "sName")
		{
			sName = sValue;
		}
		else if (sKey == "fDensity")
		{
			if (sValue == "infinity")
			{
				fDensity = std::numeric_limits<float>::infinity();
			}
			else
			{
				fDensity = stof(sValue);
			}
		}
		else if (sKey == "fRestitution")
		{
			fRestitution = stof(sValue);
		}
		else if (sKey == "fStaticFriction")
		{
			fStaticFriction = stof(sValue);
		}
		else if (sKey == "fdynamicFriction")
		{
			fDynamicFriction = stof(sValue);
		}
	}

	mm.addMaterial(sName, fDensity, fRestitution, fStaticFriction, fDynamicFriction);
}