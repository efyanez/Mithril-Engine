#ifndef _TerrainObject
#define _TerrainObject

#include "AzulCore.h"
#include "Drawable.h"
#include <string>

class Collidable;

class TerrainObject
{
public:

	struct TerrainCell
	{
		Vect cellMin;
		Vect cellMax;
	};

	TerrainObject() = default;
	TerrainObject(const char * heightmapFile, std::string texKey, int RepeatU, int RepeatV, int width, int height, int scale = 1, float offsetX = 0.5f, float offsetY = 0.0f, float offsetZ = 0.5f, int channelFix = 4);
	virtual ~TerrainObject();
	TerrainObject(TerrainObject&other) = default;
	TerrainObject & operator=(TerrainObject&other) = default;

	Vect PositionToVertex(Vect & pos);

	void VisualizeTerrain();
	void PositionToCell(Collidable* col);
	void BSphereToCells(Collidable* col);

	int GridToVert(int i, int j);
	Vect IndexToCellMin(int i, int j);
	Vect IndexToCellMax(int i, int j);

	virtual void Render();

	void GetCellCandidates(Collidable* col, std::list<TerrainCell>& list);
private:
	Model* pModel;
	Texture* pTexture;
	GraphicsObject_TextureLight* grObjTerrain;
	VertexStride_VUN* pVerts;
	TriangleIndex* pTriList;

	Vect* minCellArray;
	Vect *maxCellArray;

	int rowCells;
	int rowCols;

	int imgWidth;
	int imgHeigth;
	int icomp;

	float xOffset;
	float yOffset;
	float zOffset;

	int cellSizeX;
	int cellSizeZ;
};

#endif // !_TerrainObject
