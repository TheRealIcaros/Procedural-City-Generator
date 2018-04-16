#include "..\header\PerlinNoise.h"
#include <random>
#include <numeric>


PerlinNoise::PerlinNoise()
{
}

PerlinNoise::PerlinNoise(unsigned int seed)
{
	pn.resize(256);

	// Fill p with values from 0 to 255
	std::iota(pn.begin(), pn.end(), 0);

	// Initialize a random engine with seed
	std::default_random_engine engine(seed);

	// Suffle  using the above random engine
	std::shuffle(pn.begin(), pn.end(), engine);

	// Duplicate the permutation vector
	pn.insert(pn.end(), pn.begin(), pn.end());
}

double PerlinNoise::noise(double x, double y)
{
	//Find the square that contains the point
	int X = (int)floor(x) & 255;
	int Y = (int)floor(y) & 255;

	//Find the relative x, y point in the square
	x -= floor(x);
	y -= floor(y);

	//Alter the values with fade for smoother
	double u = fade(x);
	double v = fade(y);

	// Hash coordinates of the 4 square corners
	

	double res;

	return (res + 1.0) / 2.0;
}

double PerlinNoise::fade(double t)
{
	return 0.0;
}

double PerlinNoise::lerp(double t, double a, double b)
{
	return 0.0;
}

double PerlinNoise::grad(int hash, double x, double y)
{
	return 0.0;
}
