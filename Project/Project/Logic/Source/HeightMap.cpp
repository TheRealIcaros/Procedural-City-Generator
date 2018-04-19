#include "..\header\HeightMap.h"

HeightMap::HeightMap()
{
	value = Values::getInstance();
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
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for (unsigned int i = 0; i < value->getTSizeY(); ++i)   // y
	{
		for (unsigned int j = 0; j < value->getTSizeX(); ++j)  // x
		{
			double x = (double)j / ((double)value->getTSizeY());
			double y = (double)i / ((double)value->getTSizeX());

			// Typical Perlin noise
			double n = value->getTerrainOctavePerc1() * noise->generate(value->getTerrainOctave1() * x, 1 * value->getTerrainOctave1() * y, 0.8)
				+ value->getTerrainOctavePerc2() * noise->generate(value->getTerrainOctave2() * x, value->getTerrainOctave2() * y, 0.8)
				+ value->getTerrainOctavePerc3() * noise->generate(value->getTerrainOctave3() * x, value->getTerrainOctave3() * y, 0.8);

			n /= value->getTerrainOctavePerc1() + value->getTerrainOctavePerc2() + value->getTerrainOctavePerc3();

			n = pow(n, value->getRedistribution());
		}
	}
}

void HeightMap::setNoise(PerlinNoise * noise)
{
	this->noise = noise;
}


