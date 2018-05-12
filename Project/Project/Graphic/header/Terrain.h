#ifndef TERRAIN_H
#define TERRAIN_H

#include <glm.hpp>
#include <vector>

class Terrain
{
private:
	glm::vec3 terrainPosition;

	float maxHeight;
	float imageScale;
	float terrainSize;

	unsigned int heightMapID;
	unsigned char* imageData;
	int imageHeight;
	int imageWidth;

	float* *heights;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<unsigned int> indices;

public:
	Terrain();
	~Terrain();

};

#endif
