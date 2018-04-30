#ifndef DISTRICT_H
#define DISTRICT_H
#include "PerlinNoise.h"
#include "Array2D.h"

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
	void generate(Array2D<int>& map);
};
#endif