#include "..\header\Block.h"

Block::Block()
{
	noise = nullptr;

}

Block::~Block()
{
}

void Block::setNoise(PerlinNoise * noise)
{
	this->noise = noise;
}

void Block::generate(Array2D<int>& map)
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
		float noiseResult = noise->generate(x * 10.0f, 0.0, WIDTH, HEIGHT); //get rid of magic number
	}
}
