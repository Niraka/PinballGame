#include "MaterialsManager.h"

/**
Constructs a default MaterialsManager. */
MaterialsManager::MaterialsManager()
{
}
	
/**
Adds a new Material to the MaterialsManager with the given parameters. If the name was already in use, the current
Material is overwritten with the new one.

@param sName The name of the Material.
@param fDensity The density of the Material.
@param fRestitution The restitution of the Material.
@param fStaticFriction The static friction of the Material.
@param fDynamicFriction The dynamic friction of the Material. */
void MaterialsManager::addMaterial(std::string& sName, float fDensity, float fRestitution, float fStaticFriction, float fDynamicFriction)
{
	Material m(fDensity, fRestitution, fStaticFriction, fDynamicFriction);
	m_materials[sName] = m;
}

/**
Removes a Material with the given name from the MaterialsManager. 

@param sName The name of the Material to remove. */
void MaterialsManager::removeMaterial(std::string sName)
{
	m_materials.erase(sName);
}

/**
Clears all Materials from the MaterialsManager. */
void MaterialsManager::clearMaterials()
{
	m_materials.clear();
}

/**
Returns a pointer to a Material with the given name. Returns a nullptr if no Material the name
existed.

@param sName The name of the Material to get.
@return A pointer to a Material with the given name. */
Material* MaterialsManager::getMaterial(std::string sName)
{
	return &m_materials[sName];
}
