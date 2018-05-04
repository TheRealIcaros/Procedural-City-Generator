#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H
#include "../../Logic/header/Noise.h"
#include "Array2D.h"
#include "Array.h"
#include <vector>
#pragma region Comment
/*
Class: HeightMap
Description:
This class creates a greyscale map which decides the elevation of each point in the real map.
*/
#pragma endregion Description of class

class HeightMap
{
private:
	Noise* noise;
public:
	HeightMap();
	HeightMap(Noise* noise);
	~HeightMap();
	void generate(Array2D<float>& terrainMap, int width, int height, Array<float> oct, Array<float> perc, float redistribution);
	void setNoise(Noise* noise);
};

#endif