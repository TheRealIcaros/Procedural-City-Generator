#ifndef BLOCK_H
#define BLOCK_H
#include "PerlinNoise.h"
#include "Array2D.h"

#define MAIN_ROAD_THRESHOLD 0.35f
#define SMALL_ROAD_THRESHOLD 0.2f

class Block
{
private:
	PerlinNoise* noise;
	int mainRoads;
	int smallRoads;
public:
	Block();
	~Block();
	void setNoise(PerlinNoise* noise);
	void generate(Array2D<int>& map, float width, float height);
	int getMainRoad() { return mainRoads; }
	int getSmallRoad() { return smallRoads; }
};
#endif