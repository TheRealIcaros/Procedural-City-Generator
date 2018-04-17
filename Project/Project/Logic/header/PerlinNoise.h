#ifndef PERLINNOISE_H
#define PERLINNOISE_H
#include <vector>;
#include <glm.hpp>

class PerlinNoise
{
	std::vector<int> pn;

private:
	double fade(double t);
	//Linear Interpolation
	double lerp(double t, double a, double b);
	float grad(glm::vec2 p);
public:
	// Initialize with the reference values for the permutation vector
	PerlinNoise();
	// Generate a new permutation vector based on the value of seed
	PerlinNoise(unsigned int seed);
	// Get a noise value, for 2D image
	float noise(glm::vec2 p);
};
#endif