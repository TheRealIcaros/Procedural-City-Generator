#include "..\header\HeightMap.h"

HeightMap::HeightMap()
{
	this->noise = nullptr;
}

HeightMap::HeightMap(PerlinNoise* noise)
{
	this->noise = noise;
}

HeightMap::~HeightMap()
{
}

void HeightMap::generate(int width, int height, float oct1, float oct2, float oct3,
	float oct4, float oct5, float oct6, float oct7, float oct8, float perc1, float perc2,
	float perc3, float perc4, float perc5, float perc6, float perc7, float perc8, float redistribution)
{
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for (unsigned int i = 0; i < height; ++i)   // y
	{
		for (unsigned int j = 0; j < width; ++j)  // x
		{
			double x = (double)j / ((double)height);
			double y = (double)i / ((double)width);

			// Typical Perlin noise
			double n = perc1 * noise->generate(oct1 * x, 1 * oct1 * y, 0.8)
				+ perc2 *noise->generate(oct2 * x, oct2 * y, 0.8)
				+ perc3 * noise->generate(oct3 * x, oct3 * y, 0.8);

			n /= perc1 + perc2 + perc3;

			n = pow(n, redistribution);
		}
	}
}

void HeightMap::setNoise(PerlinNoise * noise)
{
	this->noise = noise;
}


