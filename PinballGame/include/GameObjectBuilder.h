/**
The GameObjectBuilder is a factory class for the production of GameObjects.

The builder should be used to parse vectors of strings and return pointers to created
GameObjects, and should not be expected to produce the correct GameObjects when invalid
parameter sets are supplied.

The builder is also not a file reader. Parsing strings from a file should be handled
externally.
*/

#ifndef GameObjectBuilder_H
#define GameObjectBuilder_H

#include "GameObject.h"
#include "MaterialsManager.h"
#include "TextureManager.h"
#include "AudioManager.h"
#include "Vector2D.h"
#include <vector>
#include <string>

class GameObjectBuilder
{
	public:
		GameObjectBuilder(MaterialsManager& mm);

		virtual GameObject* build(std::vector<std::string>& strings);

	protected:		
		TextureManager* tm;
		AudioManager* am;
		MaterialsManager& m_MaterialsManager;
	
	private:

};

#endif