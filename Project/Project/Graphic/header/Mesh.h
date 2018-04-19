#ifndef MESH_H
#define MESH_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>
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
	
public:
	Mesh();
	~Mesh();

	//Mesh data
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> texture);
	//void Draw(Shader shader);

};

#endif
