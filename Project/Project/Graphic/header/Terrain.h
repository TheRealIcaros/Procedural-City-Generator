#ifndef TERRAIN_H
#define TERRAIN_H

#include <glm.hpp>

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

	/*vector<vec3> vertices;
	vector<vec3> normals;
	vector<vec2> uvs;
	vector<unsigned int> indices;*/

public:
	Terrain();
	~Terrain();

};

#endif
