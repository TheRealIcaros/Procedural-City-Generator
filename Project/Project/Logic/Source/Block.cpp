#include "..\header\Block.h"

Block::Block()
{
	noise = nullptr;
	blockSizes = Array<int>(MAX_DISTRICTS);
}

Block::~Block()
{
}

void Block::setNoise(PerlinNoise * noise)
{
	this->noise = noise;
}

void Block::generate(Array2D<int>& map, float width, float height)
{
	assert(noise != nullptr);
	const int WIDTH = map.getWidth();
	const int HEIGHT = map.getHeight();
	assert(WIDTH > 0);
	assert(HEIGHT > 0);

	//reset counters
	mainRoads = 0;
	smallRoads = 0;

	for (int x = 0; x < WIDTH; x++)
	{
		float noiseResult = noise->generate(x * 10, 0.0, width, height); //get rid of magic number

		noiseResult *= noiseResult; //Why?

		if (noiseResult > MAIN_ROAD_THRESHOLD)
		{
			for (int y = 0; y<HEIGHT; y++)
			{
				map.at(x, y) = -1;
			}

			if (x == 0 || map.at(x - 1, 0) >= 0)
			{
				mainRoads++;
			}
		}
	}
}

void Block::setBlockSize(int district, int size)
{
	assert(district >= 0 && district < MAX_DISTRICTS);
	assert(size > 0);

	blockSizes[district] = size;
}
