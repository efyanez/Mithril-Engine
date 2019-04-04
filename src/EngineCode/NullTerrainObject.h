#ifndef _NullTerrainObject
#define _NullTerrainObject

#include "TerrainObject.h"

class NullTerrainObject : public TerrainObject
{
public:

	NullTerrainObject() = default;
	~NullTerrainObject() override;
	NullTerrainObject(NullTerrainObject&other) = default;
	NullTerrainObject & operator=(NullTerrainObject&other) = default;

	void Render() override;
};

#endif // !_NullTerrainObject
