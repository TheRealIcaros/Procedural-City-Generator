#include "..\header\RandomNoise.h"
#include <time.h>

RandomNoise::RandomNoise()
{
	srand(0);
}

RandomNoise::RandomNoise(unsigned int seed)
{
	srand(seed);
}

RandomNoise::~RandomNoise()
{
}

double RandomNoise::generate(double x, double y, double z)
{
	// return number between 0-1 just like perlin
	float dssfg = rand();
	dssfg /= static_cast<float>(RAND_MAX);
	return dssfg;
}

double RandomNoise::generate(double x, double y, double width, double height)
{
	// return number between 0-1 just like perlin
	float dssfg = rand();
	dssfg /= static_cast<float>(RAND_MAX);
	return dssfg;
}

double RandomNoise::generate(double x, double y, double z, double width, double height)
{
	// return number between 0-1 just like perlin
	float dssfg = rand();
	dssfg /= static_cast<float>(RAND_MAX);
	return dssfg;
}

void RandomNoise::setSeed(unsigned int seed)
{
	srand(seed);
}
