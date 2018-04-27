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
	const float PROCENTUAL_BORDER_EFFECT = 0.2;
	Array<glm::vec2> positions;
	double width;
	double height;
	double vec2SquareDistance(glm::vec2 first, glm::vec2 second);
	int closestDistrict(int x, int y);
	void findBorder(Array2D<int>& map, Array<glm::vec2>& borders);
	void alterBorders(Array2D<int>& map, Array<glm::vec2>& borders, int nodeAlterRange);
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