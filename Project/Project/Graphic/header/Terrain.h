#ifndef TERRAIN_H
#define TERRAIN_H

#include "Mesh.h"
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

	Mesh terrain;
public:
	Terrain();
	Terrain(glm::vec3 startPosition, const char *heightMapPath, std::string texturePath);
	~Terrain();

	void deallocate();

	unsigned char* loadHeightMap(const char *path);
	void createTerrain();
	void triangulate();
	float getPixelColor(glm::vec2 pos);

	void sendToObject();
	void Draw(shaderCreater shader);

	float getHeightOfTerrain(float worldX, float worldZ);
	float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
	void DrawDepth(shaderCreater shader);
};

#endif
