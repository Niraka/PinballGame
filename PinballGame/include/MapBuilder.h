/**
A MapBuilder constructs a set of GameObjects specified in a map file that come to together to
produce a playable map.

The MapBuilder populates the vector of gameobjects and materails manager it is given whilst the
map is under construction. Additionally, any other loaded resources are added to the appropriate
singleton resource managers.
*/

#ifndef MapBuilder_H
#define MapBuilder_H

#include <string>
#include <iostream>
#include <fstream>
#include "TextureManager.h"
#include "AudioManager.h"
#include "GameObject.h"
#include "MaterialsManager.h"
#include "GameObjectBuilder.h"
#include "MaterialBuilder.h"
#include "FlipperBuilder.h"

class MapBuilder
{
	public:
		MapBuilder();

		void buildMap(std::string sMapFile, std::vector<GameObject*>& gameObjects, MaterialsManager& mm);

	protected:
	private:

};

#endif;