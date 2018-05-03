#ifndef BUILDING_H
#define BUILDING_H
#include "Noise.h"
#include "Array2D.h"
#include"../../LogicDefines.h"

#pragma region Comment
/*
Class: Building
Description:
This class checks which tiles of the map are to have a building on it. This is decided by 
the checking the generated treshhold against the district density. In addition it also checks
against the heightmap and its treshhold to decide if the angled elevation is too steep.
*/
#pragma endregion Description of class

class Building
{
private:
	Noise * noise;
	int districtMinHeights[MAX_DISTRICTS];
	int districtMaxHeights[MAX_DISTRICTS];
	float districtDensities[MAX_DISTRICTS];

	int buildings[MAX_DISTRICTS];
	int grassTiles[MAX_DISTRICTS];

	const float HEIGHTMAP_TRESHHOLD = 0.05f;
public:
	Building();
	~Building();
	void setHeight(int district, int minHeight, int maxHeight);
	void setDensity(int district, float density);
	void generate(Array2D<int>& map, Array2D<float>& terrainMap, int width, int height);
	void setNoise(Noise* noise);
	int* getBuildings() { return buildings; }
	int* getGrassTiles() { return grassTiles; }
};
#endif