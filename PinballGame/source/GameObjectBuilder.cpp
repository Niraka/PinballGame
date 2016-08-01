#include "GameObjectBuilder.h"

/**
Constructs a GameObjectBuilder with the given parameters.

@param mm The MaterialsManager containing the materials to build the GameObjects with. */
GameObjectBuilder::GameObjectBuilder(MaterialsManager& mm) : m_MaterialsManager(mm)
{
	tm = TextureManager::getInstance();
	am = AudioManager::getInstance();
}

/**
Attempts to build a new GameObject by parsing the given vector of strings as parameters. Missing parameters are very
likely to cause crashes. Returns a pointer to the created GameObject. 

@return A pointer to the created GameObject. */
GameObject* GameObjectBuilder::build(std::vector<std::string>& strings)
{
	// Parsing temporary values
	std::string sKey;
	std::string sValue;
	int equalsChar = 0;

	// Values for building a GameObject
	std::string sName;
	float fPositionX;
	float fPositionY;
	std::string sMaterial;
	std::string sShapeType;
	Shape* pShape;
	float fRadius;
	float fWidth;
	float fHeight;
	float fOrientation;
	float fGravityModifier;
	std::string sTexture;
	bool bIsStatic;

	// Parse properties
	for (std::vector<std::string>::iterator it = strings.begin(); it != strings.end(); ++it)
	{
		// Split the line in to key and value components
		equalsChar = (*it).find_first_of('=');
		sKey = (*it).substr(0, equalsChar);
		sValue = (*it).substr(equalsChar + 1, (*it).length());

		if (sKey == "" | sValue == "")
		{
			continue;
		}

		if (sKey == "sName")
		{
			sName = sValue;
		}
		else if (sKey == "fPositionX")
		{
			fPositionX = stof(sValue);
		}
		else if (sKey == "fPositionY")
		{
			fPositionY = stof(sValue);
		}
		else if (sKey == "sMaterial")
		{
			sMaterial = sValue;
		}
		else if (sKey == "sShapeType")
		{
			sShapeType = sValue;
		}
		else if (sKey == "fRadius")
		{
			fRadius = stof(sValue);
		}
		else if (sKey == "fWidth")
		{
			fWidth = stof(sValue);
		}
		else if (sKey == "fHeight")
		{
			fHeight = stof(sValue);
		}
		else if (sKey == "fOrientation")
		{
			fOrientation = stof(sValue);
		}
		else if (sKey == "fGravityMultiplier")
		{
			fGravityModifier = stof(sValue);
		}
		else if (sKey == "sTexture")
		{
			sTexture = sValue;
		}		
		else if (sKey == "bIsStatic")
		{
			if (sValue == "true")
			{
				bIsStatic = true;
			}
			else
			{
				bIsStatic = false;
			}
		}
	}

	// Create shape
	if (sShapeType == "obb")
	{
		pShape = new OBB(fWidth, fHeight,fOrientation);
	}
	else if (sShapeType == "aabb")
	{
		pShape = new AABB(fWidth, fHeight);
	}
	else // Default to circle
	{
		pShape = new Circle(fRadius, fOrientation);
	}

	GameObject* pGO = new GameObject(sName, pShape, Vector2D(fPositionX, fPositionY), m_MaterialsManager.getMaterial(sMaterial), bIsStatic);
	pGO->getCollidable()->setGravityMultiplier(fGravityModifier);
	pGO->setTexture(tm->getTexture(sTexture));
	return pGO;
}