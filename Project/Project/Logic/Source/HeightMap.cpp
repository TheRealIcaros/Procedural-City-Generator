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

//void HeightMap::getData(DataManager * dataManager)
//{
//	
//}

void HeightMap::generate(Array2D<float>& terrainMap, int width, int height, float oct1, float oct2, float oct3,
	float oct4, float oct5, float oct6, float oct7, float oct8, float perc1, float perc2,
	float perc3, float perc4, float perc5, float perc6, float perc7, float perc8, float redistribution)
{
	assert(noise != nullptr);
	int offwidth = width + 1;
	int offheight = height + 1;
	terrainMap = Array2D<float>(offwidth, offheight);
	terrainMap.fill(0.0f);

	// Visit every pixel of the image and assign a color generated with Perlin noise
	for (unsigned int i = 0; i < offheight; ++i)   // y
	{
		for (unsigned int j = 0; j < offwidth; ++j)  // x
		{
			double x = (double)j / ((double)offwidth);
			double y = (double)i / ((double)offheight);

			// Typical Perlin noise
			double n = 0;

			if (perc1 != 0)
			{
				n += perc1 * noise->generate(oct1 * x, 1 * oct1 * y, 0.8);
			}
			if (perc2 != 0)
			{
				n += perc2 * noise->generate(oct2 * x, 1 * oct2 * y, 0.8);
			}
			if (perc3 != 0)
			{
				n += perc3 * noise->generate(oct3 * x, 1 * oct3 * y, 0.8);
			}
			if (perc4 != 0)
			{
				n += perc4 * noise->generate(oct4 * x, 1 * oct4 * y, 0.8);
			}
			if (perc5 != 0)
			{
				n += perc5 * noise->generate(oct5 * x, 1 * oct5 * y, 0.8);
			}
			if (perc6 != 0)
			{
				n += perc6 * noise->generate(oct6 * x, 1 * oct6 * y, 0.8);
			}
			if (perc7 != 0)
			{
				n += perc7 * noise->generate(oct7 * x, 1 * oct7 * y, 0.8);
			}
			if (perc8 != 0)
			{
				n += perc8 * noise->generate(oct8 * x, 1 * oct8 * y, 0.8);
			}

			float percTot = perc1 + perc2 + perc3 + perc4 + perc5 + perc6 + perc7 + perc8;
			if (percTot != 0)
			{
				n /= percTot;
			}

			n = pow(n, redistribution);

			terrainMap.at(x, y) = n;
		}
	}
}

void HeightMap::setNoise(PerlinNoise * noise)
{
	this->noise = noise;
}


