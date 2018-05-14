#ifndef BLOCK_H
#define BLOCK_H
#include "Noise.h"
#include "Array2D.h"
#include "Array.h"
#include "../../LogicDefines.h"

#pragma region Comment
/*
Class: Block
Description:
This class creates the roads for the map and also defines the district blocks.
*/
#pragma endregion Description of class

#define MAIN_ROAD_THRESHOLD 0.35f
#define SMALL_ROAD_THRESHOLD 0.2f

class Block
{
private:
	Noise* noise;
	int mainRoads;
	int smallRoads;
	int blockSizes[MAX_DISTRICTS];
	int minRoadDistance;
public:
	Block();
	~Block();
	void setNoise(Noise* noise);
	void generate(Array2D<int>& map, float width, float height);
	void setBlockSize(int district, int size);
	void setminRoadDistance(int size);
	int getMainRoad() { return mainRoads; }
	int getSmallRoad() { return smallRoads; }
};
#endif