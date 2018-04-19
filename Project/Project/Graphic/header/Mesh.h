#ifndef MESH_H
#define MESH_H

#include "shaderCreater.h"

//#include <glad\glad.h>
//#include <GLFW\glfw3.h>
#include <vector>
#include <glm.hpp>
#include <string>

struct Vertex
{
	glm::vec3 Position;
	glm::vec2 Normal;
	glm::vec2 TexCoords;
};

struct Texture
{
	unsigned int id;
	std::string TexCoords;
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
	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> texture);
	~Mesh();

	//Mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	
	void Draw(shaderCreater shader);
	GLuint getVAO()const;
};

#endif
