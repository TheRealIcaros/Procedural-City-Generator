#include "..\header\HeightMap.h"

HeightMap::HeightMap()
{
	this->noise = nullptr;
}

HeightMap::HeightMap(PerlinNoise* noise)
{
	this->noise = noise;
}

HeightMap::~HeightMap()
{
}

void HeightMap::generate()
{
}

void HeightMap::setNoise(PerlinNoise * noise)
{
	this->noise = noise;
}


