#ifndef PERLINNOISE_H
#define PERLINNOISE_H
#include <vector>
#include <glm.hpp>
#include "../../Singleton/Values.h"

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
	// Get a noise value, for 2D images z can have any value
	double noise(double x, double y, double z);
};

#endif