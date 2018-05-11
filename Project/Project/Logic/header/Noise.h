#ifndef NOISE_H
#define NOISE_H

class Noise
{
private:

public:
	Noise();
	~Noise();
	virtual double generate(double x, double y, double z) = 0;
	virtual double generate(double x, double y, double width, double height) = 0;
	virtual double generate(double x, double y, double z, double width, double height) = 0;
	virtual void setSeed(unsigned int seed) = 0;
};

#endif