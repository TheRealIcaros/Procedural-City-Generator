#include "..\header\Block.h"

Block::Block()
{
	noise = nullptr;
}

Block::~Block()
{
}

void Block::setNoise(Noise * noise)
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

	int next = 0;

	//reset counters
	mainRoads = 0;
	smallRoads = 0;
	for (int x = 0; x < WIDTH; x++)
	{
		float noiseResult = noise->generate(x * 10.0f, 0.0f, width, height);

		noiseResult *= noiseResult; //Why?
		if (next > 0)
		{
			next--;
		}
		else
		{
			if (noiseResult > MAIN_ROAD_THRESHOLD) //check if the generated value allows Main Road
			{
				for (int y = 0; y < HEIGHT; y++)
				{
					map.at(x, y) = 9;
				}

				if (x == 0 || map.at(x - 1, 0) >= 0)
				{
					mainRoads++;

					if (noiseResult >((1 - MAIN_ROAD_THRESHOLD) / 2) + MAIN_ROAD_THRESHOLD)  //Pseudo Random addition to the next block
					{
						next = minRoadDistance + 1;
					}
					else
					{
						next = minRoadDistance;
					}
				}
			}
		}
	}

	next = 0;
	for (int x = 0; x < WIDTH; x++)
	{
		int startX = x;
		while (x < WIDTH && map.at(x, 0) != 9) //search for the next Main Road and count til its found
		{
			x++;
		}

		int endX = x;

		if (startX != endX)
		{
			for (int y = 0; y < HEIGHT; y++)
			{
				if (next > 0)
				{
					next--;
				}
				else
				{
					float noiseResult = noise->generate(x * 10.0f, y * 10.0f, width, height);
					if (noiseResult > SMALL_ROAD_THRESHOLD) //check if the generated value allows Small Road
					{
						const int DISTRICT = map.at(startX, y);

						for (int i = startX; i< endX; i++)
						{
							map.at(i, y) = 8;
						}

						smallRoads++;

						if (noiseResult > ((1 - SMALL_ROAD_THRESHOLD) / 2) + SMALL_ROAD_THRESHOLD)  //Pseudo Random addition to the next block
						{
							next = blockSizes[DISTRICT] + 1;
						}
						else
						{
							next = blockSizes[DISTRICT];
						}
					}
				}
			}
		}
	}

}

void Block::setBlockSize(int district, int size)
{
	assert(district >= 0 && district < MAX_DISTRICTS);
	assert(size > 0);

	blockSizes[district] = size;
	int k = blockSizes[district];
}

void Block::setminRoadDistance(int size)
{
	this->minRoadDistance = size;
}
