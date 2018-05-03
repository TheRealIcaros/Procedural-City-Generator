#include "..\header\Building.h"
#include <vector>

Building::Building()
{
}

Building::~Building()
{
}

void Building::setHeight(int district, int minHeight, int maxHeight)
{
	assert(district >= 0 && district < MAX_DISTRICTS);

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
				float terrain0 = terrainMap.at(x, y);
				float terrain1 = terrainMap.at(x + 1, y);
				float terrain2 = terrainMap.at(x, y + 1);
				float terrain3 = terrainMap.at(x + 1, y + 1);

				//Check if the position is allowed to have a house on it and if the positions elevation angle isnt over the extreme point
				if (noiseResult < districtDensities[district] && abs(terrain0 - terrain1) <= HEIGHTMAP_TRESHHOLD && abs(terrain0 - terrain2) <= HEIGHTMAP_TRESHHOLD && abs(terrain0 - terrain3) <= HEIGHTMAP_TRESHHOLD)
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

void Building::setNoise(Noise * noise)
{
	this->noise = noise;
}
