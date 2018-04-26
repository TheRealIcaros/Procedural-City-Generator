#ifndef HEIGHTMAP_H
#define HEIGHTMAP_H
#include "../../Logic/header/PerlinNoise.h"
#include "Array2D.h"
#include "DataManager.h"

class HeightMap : public DataHolder
{
private:
	PerlinNoise* noise;
	Array2D<float> terrainMap;
public:
	HeightMap();
	HeightMap(PerlinNoise* noise);
	~HeightMap();
	void getData(DataManager* dataManager) override;
	void generate(int width, int height, float oct1, float oct2, float oct3,
		float oct4, float oct5, float oct6, float oct7, float oct8, float perc1, float perc2,
		float perc3, float perc4, float perc5, float perc6, float perc7, float perc8,
		float redistribution);
	void setNoise(PerlinNoise* noise);
};

#endif // !