#ifndef MESH_H
#define MESH_H

//Own headers
#include "shaderCreater.h"

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

	void setupMesh();
public:
	Mesh();
	~Mesh();

	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void Draw(shaderCreater shader);
};

#endif
