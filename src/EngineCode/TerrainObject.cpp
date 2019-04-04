#include "TerrainObject.h"
#include "ShaderManager.h"
#include "TextureManager.h"
#include "SceneManager.h"
#include "GpuVertTypes.h"
#include "TextureTGA.h"
#include "MathTools.h"
#include "Visualizer.h"
#include "ColorLibrary.h"
#include "Collidable.h"

TerrainObject::TerrainObject(const char * heightmapFile, std::string texKey, int RepeatU, int RepeatV, int width, int height, int scale, float offsetX, float offsetY, float offsetZ, int channelFix)
{
	int nverts = width * width;
	pVerts = new VertexStride_VUN[nverts];

	int ntri = ((width - 1) * (width - 1)) * 2;
	pTriList = new TriangleIndex[ntri];

	unsigned int dtype;
	GLbyte* imgData = gltReadTGABits(heightmapFile, &imgWidth, &imgHeigth, &icomp, &dtype);
	assert(imgWidth == imgHeigth && imgWidth != 0); // We need square images for heightmaps

	float h_val;

	rowCells = width - 1;
	rowCols = width - 1;

	xOffset = -rowCols * offsetX;
	yOffset = offsetY;
	zOffset = rowCells * offsetZ;

	cellSizeX = scale;
	cellSizeZ = scale;

	float du = 1.0f / (width - 1);
	float dv = 1.0f / (width - 1);

	int k = 0;
	for (float i = 0; i < width; ++i) {

		for (float j = 0; j < width; ++j)
		{
			size_t myI = (size_t)i;
			size_t myJ = (size_t)j;
			h_val = static_cast<unsigned char>(imgData[channelFix * (myJ * imgHeigth + myI)]);
			float yVal = (float)h_val;
			pVerts[k].set(j * cellSizeX + xOffset, (yVal / 255.0f) * height + yOffset, -i * cellSizeZ + zOffset, i * du * RepeatU, j * dv * RepeatV, 1, 1, 1);
			++k;
		}
	}

	k = 0;
	for (DWORD i = 0; i < (DWORD)rowCells; ++i)
	{
		for (DWORD j = 0; j < (DWORD)rowCols; ++j)
		{
			pTriList[k].set(i * width + j, i * width + j + 1, (i + 1) * width + j);
			pTriList[k + 1].set((i + 1) * width + j, i * width + j + 1, (i + 1) * width + j + 1);
			k += 2;
		}
	}

	for (int i = 0; i < ntri; i++)
	{
		int index1 = pTriList[i].v0;
		int index2 = pTriList[i].v1;
		int index3 = pTriList[i].v2;

		Vect side1 = Vect(pVerts[index1].x - pVerts[index3].x, pVerts[index1].y - pVerts[index3].y, pVerts[index1].z - pVerts[index3].z);
		Vect side2 = Vect(pVerts[index1].x - pVerts[index2].x, pVerts[index1].y - pVerts[index2].y, pVerts[index1].z - pVerts[index2].z);
		Vect mynormal = side2.cross(side1);

		pVerts[index1].nx = 0;
		pVerts[index2].ny = 0;
		pVerts[index3].nz = 0;

		pVerts[index1].nx += mynormal.X();
		pVerts[index2].ny += mynormal.Y();
		pVerts[index3].nz += mynormal.Z();
	}

	Vect lightCol = Vect(1, 1, 1);
	Vect lightPos = Vect(-300, 1000, 0);

	pModel = new Model(pVerts, nverts, pTriList, ntri);
	pTexture = TextureManager::GetTexture(texKey);
	grObjTerrain = new GraphicsObject_TextureLight(pModel, ShaderManager::GetShader(ShaderManager::DefaultShader::LightRender), pTexture, lightCol, lightPos);
}

TerrainObject::~TerrainObject()
{
	delete pModel;
	delete[] pVerts;
	delete[] pTriList;
}

Vect TerrainObject::PositionToVertex(Vect & pos)
{
	Vect vert;
	vert.X() = ((pos.X() * rowCells) / imgWidth);
	vert.Y() = ((pos.Y() * rowCells) / imgWidth);
	vert.Z() = ((pos.Z() * rowCells) / imgWidth);
	return vert;
}

void TerrainObject::VisualizeTerrain()
{
	for (int i = 0; i < imgWidth - 1; i++)
	{
		for (int j = 0; j < imgHeigth - 1; j++)
		{

			Vect min = IndexToCellMin(i, j);
			Vect max = IndexToCellMax(i, j);

			Visualizer::VisualizeMe(min, max, Colors::White);
		}
	}
}

void TerrainObject::PositionToCell(Collidable* col)
{

	Vect pos = Vect(col->GetDefaultBSphere()->GetCenter().X() - cellSizeX - xOffset, col->GetDefaultBSphere()->GetCenter().Y(), col->GetDefaultBSphere()->GetCenter().Z() - cellSizeZ - zOffset);

	int i = (int)((((-pos.Z()) / cellSizeZ) - zOffset / rowCells));
	int j = (int)((((pos.X()) / cellSizeX) - xOffset / rowCells));

	Vect min = IndexToCellMin(i, j);
	Vect max = IndexToCellMax(i, j);

	Visualizer::VisualizeMe(min, max, Colors::White);
}

void TerrainObject::BSphereToCells(Collidable* col)
{
	Vect ogMin = col->GetDefaultBSphere()->GetAABBMin();
	Vect ogMax = col->GetDefaultBSphere()->GetAABBMax();

	Vect bsMin = Vect(ogMin.X() - cellSizeX - xOffset, ogMin.Y(), ogMin.Z() - cellSizeZ - zOffset);
	Vect bsMax = Vect(ogMax.X() - cellSizeX - xOffset, ogMax.Y(), ogMax.Z() - cellSizeZ - zOffset);

	int iMin = (int)((((-bsMax.Z()) / cellSizeZ) - zOffset / rowCells));
	int iMax = (int)((((-bsMin.Z()) / cellSizeZ) - zOffset / rowCells));

	int jMin = (int)((((bsMin.X()) / cellSizeX) - xOffset / rowCells));
	int jMax = (int)((((bsMax.X()) / cellSizeX) - xOffset / rowCells));

	Vect min, max;

	for (int i = iMin; i < iMax; i++)
	{
		for (int j = jMin; j < jMax; j++)
		{
			min = IndexToCellMin(i, j);
			max = IndexToCellMax(i, j);

			CollisionVolumeAABB myAABB;
			myAABB.ComputeData(min, max);

			if (MathTools::Intersect(myAABB, *col->GetDefaultBSphere()))
			{
				Visualizer::VisualizeMe(min, max, Colors::HotPink);
				Visualizer::VisualizeMe(col->GetDefaultBSphere(), Colors::HotPink);

				if (col->GetCollisionVolume().Intersect(myAABB))
				{
					Visualizer::VisualizeMe(min, max, Colors::Red);
					Visualizer::VisualizeMe(col->GetDefaultBSphere(), Colors::Red);
				}
				else
				{
					Visualizer::VisualizeMe(min, max, Colors::Green);
					Visualizer::VisualizeMe(col->GetDefaultBSphere(), Colors::Green);
				}

			}
			else
			{
				Visualizer::VisualizeMe(min, max, Colors::SkyBlue);
				Visualizer::VisualizeMe(col->GetDefaultBSphere(), Colors::SkyBlue);
			}

		}
	}
}

int TerrainObject::GridToVert(int i, int j)
{
	return ((i * imgHeigth) + j);
}

Vect TerrainObject::IndexToCellMin(int i, int j)
{
	Vect min;

	Vect topLeft;
	Vect topRight;
	Vect bottomLeft;
	Vect bottomRight;

	topLeft = Vect(pVerts[GridToVert(i, j)].x, pVerts[GridToVert(i, j)].y, pVerts[GridToVert(i, j)].z);
	topRight = Vect(pVerts[GridToVert(i + 1, j)].x, pVerts[GridToVert(i + 1, j)].y, pVerts[GridToVert(i + 1, j)].z);
	bottomLeft = Vect(pVerts[GridToVert(i, j + 1)].x, pVerts[GridToVert(i, j + 1)].y, pVerts[GridToVert(i, j + 1)].z);
	bottomRight = Vect(pVerts[GridToVert(i + 1, j + 1)].x, pVerts[GridToVert(i + 1, j + 1)].y, pVerts[GridToVert(i + 1, j + 1)].z);

	min = topLeft;

	min = MathTools::GetMinVect(min, topRight);
	min = MathTools::GetMinVect(min, bottomLeft);
	min = MathTools::GetMinVect(min, bottomRight);

	return min;
}

Vect TerrainObject::IndexToCellMax(int i, int j)
{
	Vect max;

	Vect topLeft;
	Vect topRight;
	Vect bottomLeft;
	Vect bottomRight;

	topLeft = Vect(pVerts[GridToVert(i, j)].x, pVerts[GridToVert(i, j)].y, pVerts[GridToVert(i, j)].z);
	topRight = Vect(pVerts[GridToVert(i + 1, j)].x, pVerts[GridToVert(i + 1, j)].y, pVerts[GridToVert(i + 1, j)].z);
	bottomLeft = Vect(pVerts[GridToVert(i, j + 1)].x, pVerts[GridToVert(i, j + 1)].y, pVerts[GridToVert(i, j + 1)].z);
	bottomRight = Vect(pVerts[GridToVert(i + 1, j + 1)].x, pVerts[GridToVert(i + 1, j + 1)].y, pVerts[GridToVert(i + 1, j + 1)].z);

	max = topLeft;

	max = MathTools::GetMaxVect(max, topRight);
	max = MathTools::GetMaxVect(max, bottomLeft);
	max = MathTools::GetMaxVect(max, bottomRight);

	return max;
}

void TerrainObject::Render()
{
	grObjTerrain->Render(SceneManager::GetCurrent3DCamera());
}

void TerrainObject::GetCellCandidates(Collidable * col, std::list<TerrainCell>& list)
{

	Vect ogMin = col->GetDefaultBSphere()->GetAABBMin();
	Vect ogMax = col->GetDefaultBSphere()->GetAABBMax();

	Vect bsMin = Vect(ogMin.X() - cellSizeX - xOffset, ogMin.Y(), ogMin.Z() - cellSizeZ - zOffset);
	Vect bsMax = Vect(ogMax.X() - cellSizeX - xOffset, ogMax.Y(), ogMax.Z() - cellSizeZ - zOffset);

	int iMin = (int)((((-bsMax.Z()) / cellSizeZ) - zOffset / rowCells));
	int iMax = (int)((((-bsMin.Z()) / cellSizeZ) - zOffset / rowCells));

	int jMin = (int)((((bsMin.X()) / cellSizeX) - xOffset / rowCells));
	int jMax = (int)((((bsMax.X()) / cellSizeX) - xOffset / rowCells));

	Vect min, max;

	for (int i = iMin; i < iMax; i++)
	{
		for (int j = jMin; j < jMax; j++)
		{
			min = IndexToCellMin(i, j);
			max = IndexToCellMax(i, j);

			TerrainCell newCell;
			newCell.cellMin = min;
			newCell.cellMax = max;

			list.push_back(newCell);

			//Visualizer::VisualizeMe(min, max, Colors::SkyBlue);
			//Visualizer::VisualizeMe(col->GetDefaultBSphere(), Colors::SkyBlue);
		}
	}

	//return newList;
}
