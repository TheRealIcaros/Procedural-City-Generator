#ifndef MESH_H
#define MESH_H

#include "shaderCreater.h"
#include "../../Defines.h"
#include <vector>


struct TerrainVertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
	glm::vec3 Tangent;
	glm::vec3 Bitangent;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;
};

struct Material
{
	std::string name;

	std::vector<Texture> textures;

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
	Mesh(std::vector<TerrainVertex> vertices, std::vector<unsigned int> indices, std::vector<Material> materials, glm::vec3 startPosition);
	~Mesh();

	std::vector<TerrainVertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Material> materials;

	glm::vec3 getModelPosition();

	void Draw(shaderCreater shader);
	void DrawDepth(shaderCreater shader);
	void deallocate();
};


#endif
