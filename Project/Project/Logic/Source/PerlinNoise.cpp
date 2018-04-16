#include "..\header\PerlinNoise.h"

PerlinNoise::PerlinNoise()
{
}

PerlinNoise::PerlinNoise(unsigned int seed)
{
	p.resize(256);

	// Fill p with values from 0 to 255
	std::iota(p.begin(), p.end(), 0);

	// Initialize a random engine with seed
}

double PerlinNoise::noise(double x, double y, double z)
{
	return 0.0;
}

double PerlinNoise::fade(double t)
{
	return 0.0;
}

double PerlinNoise::lerp(double t, double a, double b)
{
	return 0.0;
}

double PerlinNoise::grad(int hash, double x, double y, double z)
{
	return 0.0;
}
