#include "..\header\Building.h"
#include <vector>

Building::Building()
{
}

Building::~Building()
{
}

void Building::addSection(int district, const Section & section, int type)
{
	assert(district >= 0 && district < MAX_DISTRICTS);
	assert(type >= SECTION_BOTTOM && type <= SECTION_TOP);

	districtSections[district][type].add(section);
}

void Building::setHeight(int district, int minHeight, int maxHeight)
{
	assert(district >= 0 && district < MAX_DISTRICTS);

	districtMinHeights[district] = minHeight;
	districtMaxHeights[district] = maxHeight;
}

void Building::setDensity(int district, float density)
{
	float temp = density / 100.0f;
	assert(district >= 0 && district < MAX_DISTRICTS);
	assert(temp >= 0.0f && temp <= 1.0f);

	districtDensities[district] = temp;
}

void Building::generate(Array2D<int>& map, Array2D<float>& terrainMap, Array<Structure>& structures, int width, int height)
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
				if (noiseResult < districtDensities[district] && abs(terrain0 - terrain1) <= HEIGHTMAP_TRESHHOLD && abs(terrain0 - terrain2) <= HEIGHTMAP_TRESHHOLD &&
					abs(terrain0 - terrain3) <= HEIGHTMAP_TRESHHOLD)
				{
					Array<Section>& botSections = districtSections[district][SECTION_BOTTOM];
					Array<Section>& midSections = districtSections[district][SECTION_MIDDLE];
					Array<Section>& topSections = districtSections[district][SECTION_TOP];

					const int MIN_HEIGHT = districtMinHeights[district];
					const int MAX_HEIGHT = districtMaxHeights[district];
					const int HEIGHT_DIF = MAX_HEIGHT - MIN_HEIGHT;

					const int ARBITRARY_LARGE_NUMBER = 100;
					int sectionOffset = (int)(noiseResult*(float)ARBITRARY_LARGE_NUMBER);
					int botSection = sectionOffset % botSections.getSize();
					int midSection = sectionOffset % midSections.getSize();
					int topSection = sectionOffset % topSections.getSize();
					int structureHeight = (int)(noiseResult * (float)(HEIGHT_DIF + 0.5f)) + MIN_HEIGHT;

					if (structureHeight < 1)
					{
						structureHeight = 1;
					}

					Structure structure =
					{
						botSections[botSection],
						midSections[midSection],
						topSections[topSection],
						structureHeight,
					};

					structures.add(structure);
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

void Building::fullRandom(Array2D<int>& map, Array2D<float>& terrainMap, Array<Structure>& structures)
{
	// reset counters
	for (int i = 0; i < MAX_DISTRICTS; i++)
	{
		buildings[i] = 0;
		grassTiles[i] = 0;
	}

	const int WIDTH = map.getWidth();
	const int HEIGHT = map.getHeight();

	for (int x = 0; x<WIDTH; x++)
	{
		for (int y = 0; y<HEIGHT; y++)
		{
			int district = map.at(x, y);
			if (district < 8 && district >= 0)
			{
				float terrain0 = terrainMap.at(x, y);
				float terrain1 = terrainMap.at(x + 1, y);
				float terrain2 = terrainMap.at(x, y + 1);
				float terrain3 = terrainMap.at(x + 1, y + 1);

				if (abs(terrain0 - terrain1) <= HEIGHTMAP_TRESHHOLD && abs(terrain0 - terrain2) <= HEIGHTMAP_TRESHHOLD &&
					abs(terrain0 - terrain3) <= HEIGHTMAP_TRESHHOLD)
				{
					Array<Section>& botSections = districtSections[district][SECTION_BOTTOM];
					Array<Section>& midSections = districtSections[district][SECTION_MIDDLE];
					Array<Section>& topSections = districtSections[district][SECTION_TOP];

					int botSection = rand() % botSections.getSize();
					int midSection = rand() % midSections.getSize();
					int topSection = rand() % topSections.getSize();
					int structureHeight = rand() % 10;

					if (structureHeight < 1)
					{
						structureHeight = 1;
					}

					Structure structure =
					{
						botSections[botSection],
						midSections[midSection],
						topSections[topSection],
						structureHeight,
					};

					structures.add(structure);
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
