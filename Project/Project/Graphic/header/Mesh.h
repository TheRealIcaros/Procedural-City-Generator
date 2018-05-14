#ifndef MESH_H
#define MESH_H

#include "../../Defines.h"
#include <vector>

//Own Classes
#include "shaderCreater.h"

//using namespace std;
//using namespace glm;

struct TerrainVertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct TerrainTexture
{
	unsigned int id;
	std::string type;
	std::string path;
};

struct TerrainMaterial
{
	std::string name;

	std::vector<TerrainTexture> textures;

	glm::vec3 colorAmbient;
	glm::vec3 colorDiffuse;
	glm::vec3 colorSpecular;
	float specularExponent;
};

class Mesh
{
private:
	glm::mat4 Model;
	glm::vec3 localPosition;
	unsigned int VAO, VBO, EBO;
	void setupMesh();
public:
	Mesh();
	Mesh(std::vector<TerrainVertex> vertices, std::vector<unsigned int> indices, std::vector<TerrainMaterial> materials, glm::vec3 startPosition);
	~Mesh();

	std::vector<TerrainVertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<TerrainMaterial> materials;

	glm::vec3 getModelPosition();

	void Draw(shaderCreater shader);
	void DrawDepth(shaderCreater shader);
	void deallocate();
};

#endif // !MESH_H