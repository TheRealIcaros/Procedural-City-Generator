#ifndef MESH_H
#define MESH_H

//Own headers
#include "shaderCreater.h"
#include "../../Defines.h"

//General includes
#include <glm.hpp>
#include <vector>
#include <iostream>

struct Vertex
{
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	std::string type;
	std::string path;  // we store the path of the texture to compare with other textures
};

class Mesh
{
private:
	unsigned int VAO;
	unsigned int VBO;
	unsigned int EBO;

	glm::mat4 Model;
	glm::vec3 localPosition;

	void setupMesh();
public:
	Mesh();
	~Mesh();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, glm::vec3 startPosition);
	void Draw(shaderCreater shader);
};

#endif
