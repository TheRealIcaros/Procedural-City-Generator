#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H
#include "../../Logic/header/PerlinNoise.h"
#include "Array2D.h"
#include "Array.h"
//#include "DataManager.h"

class HeightMap/* : public DataHolder*/
{
private:
	PerlinNoise* noise;
public:
	HeightMap();
	HeightMap(PerlinNoise* noise);
	~HeightMap();
	/*void getData(DataManager* dataManager) override;*/
	void generate(Array2D<float>& terrainMap, int width, int height, Array<float> oct, Array<float> perc, float redistribution);
	void setNoise(PerlinNoise* noise);
};

#endif // !