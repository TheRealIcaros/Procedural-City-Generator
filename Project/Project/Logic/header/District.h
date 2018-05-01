#ifndef DISTRICT_H
#define DISTRICT_H
#include "PerlinNoise.h"
#include "Array2D.h"
#include "Array.h"
#include "../../LogicDefines.h"
class District
{
private:
	PerlinNoise * noise;
	Array<glm::vec2> positions;
	double vec2SquareDistance(glm::vec2 first, glm::vec2 second);
	int closestDistrict(int x, int y);
	void findBorder(Array2D<int>& map, Array<glm::vec2>& borders);
	void alterBorders(Array2D<int>& map, Array<glm::vec2>& borders, int nodeAlterRange);
	void setDistrict(float width, float height);
	void calculateMap(Array2D<int>& map, float borderPerc);
public:
	District();
	District(PerlinNoise* noise);
	~District();
	void setNoise(PerlinNoise* noise);
	void generate(Array2D<int>& map, float width, float height, float borderPerc);
};

#endif