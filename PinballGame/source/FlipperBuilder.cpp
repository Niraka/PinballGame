#include "FlipperBuilder.h"

/**
Constructs FlipperBuilder with the given parameters. 

@param mm The MaterialsManager that contains the Material the flippers will use. */ 
FlipperBuilder::FlipperBuilder(MaterialsManager& mm) : GameObjectBuilder(mm)
{
}

/**
Attempts to build a Flipper using the given vector of strings. Returns a pointer to the GameObject baseclass of
the flipper. 

@param sStrings A vector of strings representing the parameters of the flipper. 
@return A pointer to the GameObject baseclass of the flipper. */
GameObject* FlipperBuilder::build(std::vector<std::string>& sStrings)
{
	// Parsing temporary values
	std::string sKey;
	std::string sValue;
	int equalsChar = 0;

	// Values for building a Flipper
	std::string sType;
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
	float fRotationX;
	float fRotationY;
	float fRiseSpeed;
	float fFallSpeed;

	// Parse properties
	for (std::vector<std::string>::iterator it = sStrings.begin(); it != sStrings.end(); ++it)
	{
		// Split the line in to key and value components
		equalsChar = (*it).find_first_of('=');
		sKey = (*it).substr(0, equalsChar);
		sValue = (*it).substr(equalsChar + 1, (*it).length());

		if (sKey == "" || sValue == "")
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
		else if (sKey == "sType")
		{
			sType = sValue;
		}
		else if (sKey == "fRotationX")
		{
			fRotationX = stof(sValue);
		}
		else if (sKey == "fRotationY")
		{
			fRotationY = stof(sValue);
		}
		else if (sKey == "fRiseSpeed")
		{
			fRiseSpeed = stof(sValue);
		}
		else if (sKey == "fFallSpeed")
		{
			fFallSpeed = stof(sValue);
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
	else if (sShapeType == "circle")
	{
		pShape = new Circle(fRadius, fOrientation);
	}
	else 
	{	
		// Default to circle. Keeps the compiler happy about avoiding potentially undeclared variables.
		pShape = new Circle(10, 0);
	}

	if (sType == "left")
	{
		FlipperLeft* fl = new FlipperLeft(sName, pShape, Vector2D(fPositionX, fPositionY), m_MaterialsManager.getMaterial(sMaterial), Vector2D(fRotationX, fRotationY));
		fl->setTexture(TextureManager::getInstance()->getTexture(sTexture));
		fl->getCollidable()->setGravityMultiplier(fGravityModifier);
		fl->setRiseSpeed(fRiseSpeed);
		fl->setFallSpeed(fFallSpeed);
		return fl;
	}
	else if (sType == "right")
	{
		FlipperRight* fr = new FlipperRight(sName, pShape, Vector2D(fPositionX, fPositionY), m_MaterialsManager.getMaterial(sMaterial), Vector2D(fRotationX, fRotationY));
		fr->setTexture(TextureManager::getInstance()->getTexture(sTexture));
		fr->getCollidable()->setGravityMultiplier(fGravityModifier);
		fr->setRiseSpeed(fRiseSpeed);
		fr->setFallSpeed(fFallSpeed);	
		return fr;
	}
	else
	{
		// Default to left flipper. Keeps the compiler happy about avoiding potentially undeclared variables.
		FlipperLeft* fl = new FlipperLeft(sName, pShape, Vector2D(fPositionX, fPositionY), m_MaterialsManager.getMaterial(sMaterial), Vector2D(fRotationX, fRotationY));
		fl->setTexture(TextureManager::getInstance()->getTexture(sTexture));
		fl->getCollidable()->setGravityMultiplier(fGravityModifier);
		fl->setRiseSpeed(fRiseSpeed);
		fl->setFallSpeed(fFallSpeed);
		return fl;
	}
}