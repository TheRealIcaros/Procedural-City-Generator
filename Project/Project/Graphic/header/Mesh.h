#ifndef MESH_H
#define MESH_H

#include "shaderCreater.h"

#include <vector>
#include <glm.hpp>
#include <string>

struct Vertex {
	// position
	glm::vec3 Position;
	// normal
	glm::vec3 Normal;
	// texCoords
	glm::vec2 TexCoords;
	// tangent
	glm::vec3 Tangent;
	// bitangent
	glm::vec3 Bitangent;
};

struct Texture {
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh
{
private:
	//Vertex Array Object and Vertex Buffer Object
	GLuint VAO;
	GLuint VBO;
	GLuint EBO;

	void setupMesh();
public:

	Mesh();
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	~Mesh();

	//Mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	void Draw(shaderCreater shader);
	GLuint getVAO()const;
};

#endif
