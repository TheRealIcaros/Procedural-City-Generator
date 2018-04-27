#ifndef DISTRICT_H
#define DISTRICT_H
#include "PerlinNoise.h"
#include "Array2D.h"
#include "Array.h"
class District
{
private:
	PerlinNoise * noise;
	const int DISTRICT_AMOUNT = 3;
	Array<glm::vec2> positions;
	double width;
	double height;
public:
	District();
	District(PerlinNoise* noise);
	~District();
	void setDistrict(float width, float height);
	void setNoise(PerlinNoise* noise);
	void calculateMap(Array2D<int>& map);
	void generate(Array2D<int>& map, float width, float height);
};

#endif