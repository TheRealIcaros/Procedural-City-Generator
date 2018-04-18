#ifndef PERLINNOISE_H
#define PERLINNOISE_H
#include <vector>
#include <glm.hpp>
#include "../../Singleton/Values.h"

/*
	Base Code from: SolarianProgrammer.com, upgraded by Niclas Ohlsson and Frank Elias
	for Procedural city generation using Perlin noise
*/

class PerlinNoise 
{
private:
	// The permutation vector
	std::vector<int> p;
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
public:
	// Initialize with the reference values for the permutation vector
	PerlinNoise();
	// Generate a new permutation vector based on the value of seed
	PerlinNoise(unsigned int seed);
	// Get a noise value, for #D/2D images
	double noise(double x, double y, double z);
	double noise(double x, double y, double xMaxValue, double yMaxValue);
	double noise(double x, double y, double z, double xMaxValue, double yMaxValue);

	void seed(unsigned int seed);

	static unsigned int counter;
};

#endif