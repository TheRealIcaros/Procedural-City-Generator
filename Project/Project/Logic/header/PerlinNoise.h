#ifndef PERLINNOISE_H
#define PERLINNOISE_H
#include "Noise.h"
#include <vector>
#include <glm.hpp>

/*
	Base Code from: SolarianProgrammer.com, upgraded by Niclas Ohlsson and Frank Elias
	for Procedural city generation using Perlin noise
*/

class PerlinNoise : public Noise
{
private:
	// The permutation vector
	std::vector<int> p;
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
	static unsigned int counter;
public:
	// Initialize with the reference values for the permutation vector
	PerlinNoise();
	// Generate a new permutation vector based on the value of seed
	PerlinNoise(unsigned int seed);
	// Get a noise value, for #D/2D images
	double generate(double x, double y, double z) override;
	double generate(double x, double y, double xMaxValue, double yMaxValue) override;
	double generate(double x, double y, double z, double xMaxValue, double yMaxValue) override;
	void setSeed(unsigned int seed) override;
	int getCounter() { return counter; }
};

#endif