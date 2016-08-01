/**
A MaterialBuilder is a parsing class that attempts to produce and add to a MaterialsManager a Material
from a set of strings that are typically loaded from a .txt file.
*/

#ifndef MaterialBuilder_H
#define MaterialBuilder_H

#include "Material.h"
#include "MaterialsManager.h"
#include <vector>
#include <string>

class MaterialBuilder
{
	public:
		MaterialBuilder();
		void buildMaterial(std::vector<std::string>& sStrings, MaterialsManager& mm);

	protected:

	private:

};

#endif