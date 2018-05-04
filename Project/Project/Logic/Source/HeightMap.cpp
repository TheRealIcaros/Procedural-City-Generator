#include "..\header\HeightMap.h"

HeightMap::HeightMap()
{
	this->noise = nullptr;
}

HeightMap::HeightMap(Noise* noise)
{
	this->noise = noise;
}

HeightMap::~HeightMap()
{
}

void HeightMap::generate(Array2D<float>& terrainMap, int width, int height, Array<float> oct, Array<float> perc, float redistribution)
{
	assert(noise != nullptr);
	int offwidth = width + 1;
	int offheight = height + 1;
	terrainMap = Array2D<float>(offwidth, offheight);
	terrainMap.fill(0.0f);

	// Visit every pixel of the image and assign a greyscale color generated with Perlin noise
	for (unsigned int j = 0; j < offwidth; ++j)   // y
	{
		for (unsigned int i = 0; i < offheight; ++i)  // x
		{
			double x = (double)j / ((double)offwidth);
			double y = (double)i / ((double)offheight);

			double n = 0;
			float percTot = 0;
			int size = oct.getSize();
			for (int k = 0; k < size; k++)
			{
				if (perc[k] != 0) //skip octaves which have no pecentage
				{
					n += perc[k] * noise->generate(oct[k] * x, 1 * oct[k] * y, 0.8);
					percTot += perc[k];
				}
			}

			if (percTot != 0)
			{
				n /= percTot;
			}

			n = pow(n, redistribution); //lessen/increases the differences between the heightmap pixels

			terrainMap.at(j, i) = n;
		}
	}
}

void HeightMap::setNoise(Noise * noise)
{
	this->noise = noise;
}


