#include "..\header\Building.h"

Building::Building()
{
}

Building::~Building()
{
}

void Building::setHeight(int district, int minHeight, int maxHeight)
{
	assert(district >= 0 && district < MAX_DISTRICTS);
	/*assert(height > 0);*/

	districtMinHeights[district] = minHeight;
	districtMaxHeights[district] = maxHeight;
}

void Building::setDensity(int district, float density)
{
	assert(district >= 0 && district < MAX_DISTRICTS);
	assert(density >= 0.0f && density <= 1.0f);

	districtDensities[district] = density;
}

void Building::generate(Array2D<int>& map, Array2D<int>& terrainMap)
{
}

void Building::setNoise(PerlinNoise * noise)
{
	this->noise = noise;
}
