/**
The MaterialsManager is a container class for convenient storage of Material objects. 

The manager requires that every added Material is done so under a name that represents it. For example: A new Material
is added with a high density named "iron". Every time the high density Material is required, the user must simply
call "getMaterial("iron")".

Note that the MaterialsManager is NOT a singleton. This decision was made so that other Material sets that use the same
names may be loaded without causing conflict.
*/

#ifndef MaterialsManager_H
#define MaterialsManager_H

#include "Material.h"
#include <string>
#include <map>

class MaterialsManager
{
	public:
		MaterialsManager();

		void addMaterial(std::string& sName, float fDensity, float fRestitution, float fStaticFriction, float fDynamicFriction);
		void removeMaterial(std::string sName);
		void clearMaterials();
		Material* getMaterial(std::string sName);

	protected:

	private:
		std::map<std::string, Material> m_materials;
};

#endif