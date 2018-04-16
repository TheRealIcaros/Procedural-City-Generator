#ifndef PERLINNOISE_H
#define PERLINNOISE_H
#include <vector>;

class PerlinNoise
{
	std::vector<int> pn;

private:
	double fade(double t);
	//Linear Interpolation
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y);
public:
	// Initialize with the reference values for the permutation vector
	PerlinNoise();
	// Generate a new permutation vector based on the value of seed
	PerlinNoise(unsigned int seed);
	// Get a noise value, for 2D image
	double noise(double x, double y);
};
#endif