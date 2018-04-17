#include "..\header\PerlinNoise.h"
#include <random>
#include <numeric>


PerlinNoise::PerlinNoise()
{
	pn = {
		151,160,137,91,90,15,131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,
		8,99,37,240,21,10,23,190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,
		35,11,32,57,177,33,88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,
		134,139,48,27,166,77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,
		55,46,245,40,244,102,143,54, 65,25,63,161,1,216,80,73,209,76,132,187,208, 89,
		18,169,200,196,135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,
		250,124,123,5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,
		189,28,42,223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167,
		43,172,9,129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,
		97,228,251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,
		107,49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
		138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180 };

	// Duplicate the permutation vector
	pn.insert(pn.end(), pn.begin(), pn.end());
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

float PerlinNoise::noise(glm::vec2 p)
{
	//calculate the lattice points
	glm::vec2 p0 = floor(p);
	glm::vec2 p1 = p0 + glm::vec2(1.0, 0.0);
	glm::vec2 p2 = p0 + glm::vec2(0.0, 1.0);
	glm::vec2 p3 = p0 + glm::vec2(1.0, 1.0);
	
	/* Look up gradients at lattice points. */
	float g0 = grad(p0);
	float g1 = grad(p1);
	float g2 = grad(p2);
	float g3 = grad(p3);

	float t_x = p.x - p0.x;
	float fade_x = fade(t_x); /* Used for interpolation in horizontal direction */

	float t_y = p.x - p0.x;
	float fade_y = fade(t_y); /* Used for interpolation in vertical direction. */

	///* Calculate dot products and interpolate.*/
	//float p0p1 = (1.0 - fade_x) * dot(g0, (p - p0)) + fade_x * dot(g1, (p - p1)); /* between upper two lattice points */
	//float p2p3 = (1.0 - fade_x) * dot(g2, (p - p2)) + fade_x * dot(g3, (p - p3)); /* between lower two lattice points */
	///* Calculate final result */
	//return (1.0 - fade_y) * p0p1 + fade_y * p2p3;
	return 1;
}

double PerlinNoise::fade(double t)
{
	return t * t * t * (t * (t * 6 - 15) + 10);
}

double PerlinNoise::lerp(double t, double a, double b)
{
	return a + t * (b - a);
}

float PerlinNoise::grad(glm::vec2 p)
{
	float x = p.x;
	return pn[pn[pn[(int)p.x & 255] + (int)p.y & 255]];
}
