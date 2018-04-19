#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H
#include "../../Logic/header/PerlinNoise.h"

class HeightMap
{
private:
	PerlinNoise* noise;
public:
	HeightMap();
	HeightMap(PerlinNoise* noise);
	~HeightMap();
	void generate();
	void setNoise(PerlinNoise* noise);
};

#endif // !