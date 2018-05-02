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

void Building::generate(Array2D<int>& map, Array2D<float>& terrainMap, int width, int height)
{
	// reset counters
		for (int i = 0; i < MAX_DISTRICTS; i++)
		{
			buildings[i] = 0;
			grassTiles[i] = 0;
		}

	// generate buildings
	const int WIDTH = map.getWidth();
	const int HEIGHT = map.getHeight();

	for (int x = 0; x < WIDTH; x++)
	{
		for (int y = 0; y < HEIGHT; y++)
		{
			int district = map.at(x, y);
			if (district < 8 && district >= 0)
			{
				float noiseResult = noise->generate(x * 10, y * 10, width, height);

				if (noiseResult < districtDensities[district])
				{

					buildings[district]++;
				}
				else
				{
					map.at(x, y) = 7;
					grassTiles[district]++;
				}
			}
		}
	}

}

void Building::setNoise(PerlinNoise * noise)
{
	this->noise = noise;
}
