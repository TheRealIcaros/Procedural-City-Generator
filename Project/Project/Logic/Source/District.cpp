#include "..\header\District.h"

District::District()
{
	this->noise = nullptr;
	for (int i = 0; i < DISTRICT_AMOUNT; i++)
	{
		this->positions.add(glm::vec2());
	}
}

District::District(PerlinNoise * noise)
{
	this->noise = noise;
	for (int i = 0; i < DISTRICT_AMOUNT; i++)
	{
		this->positions.add(glm::vec2());
	}
}

District::~District()
{
}

void District::setDistrict(float width, float height)
{
	// gives districts initial position 
	this->width = width;
	this->height = height;

	double noise = 20 * this->noise->generate(1.134, 1.22, 1, 1); // Some noise with nice spread
	this->positions[0].x = (noise - floor(noise)) * width;

	noise = 10 * this->noise->generate(1.476, 1.687, 0.88, 1);
	this->positions[0].y = (noise - floor(noise)) * height;

	noise = 20 * this->noise->generate(6.745, 4.9345, 0.77, 1);
	this->positions[1].x = (noise - floor(noise)) * width;

	noise = 10 * this->noise->generate(2.975, 2.626, 0.6, 1);
	this->positions[1].y = (noise - floor(noise)) * height;

	noise = 20 * this->noise->generate(3.153, 3.754, 0.55, 1);
	this->positions[2].x = (noise - floor(noise)) * width;

	noise = 10 * this->noise->generate(4.242, 7.965, 0.44, 1);
	this->positions[2].y = (noise - floor(noise)) * height;
}

void District::setNoise(PerlinNoise * noise)
{
	this->noise = noise;
}

void District::calculateMap(Array2D<int>& map)
{
}

void District::generate(Array2D<int>& map, float width, float height)
{
	setDistrict(width, height);
}
