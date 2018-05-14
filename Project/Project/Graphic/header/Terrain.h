#ifndef TERRAIN_H
#define TERRAIN_H

#include "Mesh.h"
#include "Texture.h"
#include "../../Logic/header/Array2D.h"
#include <glm.hpp>
#include <vector>

class Terrain
{

private:
	shaderCreater terrainShader;
	glm::vec3 terrainPosition;
	Texture terrainTexture;
	float maxHeight;
	float imageScale;
	float terrainSizeX;
	float terrainSizeY;

	int texturePath;

	unsigned int heightMapID;
	Array2D<float> imageData;
	//unsigned char* imageData;
	int imageHeight;
	int imageWidth;

	float* *heights;

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<unsigned int> indices;

	//unsigned int TextureFromFile(const char* texturePath);

	Mesh terrain;
public:
	Terrain();
	Terrain(glm::vec3 startPosition, Array2D<float> heightMapPath, int texturePath);
	//Terrain(glm::vec3 startPosition, const char *heightMapPath, int texturePath);
	~Terrain();

	void deallocate();

	unsigned char* loadHeightMap(const char *path);
	void createTerrain();
	void triangulate();
	float getPixelColor(glm::vec2 pos);

	void sendToObject();
	void Draw(shaderCreater shader, int textID);

	float getHeightOfTerrain(float worldX, float worldZ);
	float barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos);
	void DrawDepth(shaderCreater shader);
};

#endif
