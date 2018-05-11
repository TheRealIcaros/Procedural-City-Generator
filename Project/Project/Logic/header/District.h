#ifndef DISTRICT_H
#define DISTRICT_H
#include "Noise.h"
#include "Array2D.h"
#include "Array.h"
#include "../../LogicDefines.h"
#include <glm.hpp>
#pragma region Comment
/*
Class: District
Description:
This class creates 3 seperate district start points on the map. It then generates the points to be 
of the same district as the starting point closest to it. After this the borders are found and mixed 
as to create a more naturall looking border.
*/
#pragma endregion Description of class

class District
{
private:
	Noise * noise;
	Array<glm::vec2> positions;
	double vec2SquareDistance(glm::vec2 first, glm::vec2 second);
	int closestDistrict(int x, int y);
	void findBorder(Array2D<int>& map, Array<glm::vec2>& borders);
	void alterBorders(Array2D<int>& map, Array<glm::vec2>& borders, int nodeAlterRange);
	void setDistrict(float width, float height);
	void calculateMap(Array2D<int>& map, float borderPerc);
public:
	District();
	District(Noise* noise);
	~District();
	void setNoise(Noise* noise);
	void generate(Array2D<int>& map, float width, float height, float borderPerc);
};

#endif