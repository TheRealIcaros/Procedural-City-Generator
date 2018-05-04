#ifndef RANDOMNOISE_H
#define RANDOMNOISE_H
#include "Noise.h"
#include <random>

class RandomNoise : public Noise
{
private:

public:
	RandomNoise();
	RandomNoise(unsigned int seed);
	~RandomNoise();

	//override
	double generate(double x, double y, double z) override;
	double generate(double x, double y, double width, double height) override;
	double generate(double x, double y, double z, double width, double height) override;
	void setSeed(unsigned int seed) override;
};

#endif