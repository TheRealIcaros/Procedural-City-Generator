#ifndef BUILDING_H
#define BUILDING_H
#include "PerlinNoise.h"
#include "Array2D.h"
#include"../../LogicDefines.h"

class Building
{
private:
	PerlinNoise * noise;
	int districtMinHeights[MAX_DISTRICTS];
	int districtMaxHeights[MAX_DISTRICTS];
	float districtDensities[MAX_DISTRICTS];

	int buildings[MAX_DISTRICTS];
	int grassTiles[MAX_DISTRICTS];
public:
	Building();
	~Building();
	void setHeight(int district, int minHeight, int maxHeight);
	void setDensity(int district, float density);
	void generate(Array2D<int>& map, Array2D<int>& terrainMap);
	void setNoise(PerlinNoise* noise);
};
#endif