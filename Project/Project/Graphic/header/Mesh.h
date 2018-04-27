#ifndef MESH_H
#define MESH_H


#include "../../Defines.h"
#include <vector>

//Own Classes
#include "ShaderCreater.h"

using namespace std;
using namespace glm;

struct Vertex
{
	vec3 Position;
	vec3 Normal;
	vec2 TexCoords;
	vec3 Tangent;
	vec3 Bitangent;
};

struct Texture
{
	unsigned int id;
	string type;
	string path;
};

struct Material
{
	string name;

	vector<Texture> textures;

	vec3 colorAmbient;
	vec3 colorDiffuse;
	vec3 colorSpecular;
	float specularExponent;
};

class Mesh
{
private:
	mat4 Model;
	vec3 localPosition;
	unsigned int VAO, VBO, EBO;
	void setupMesh();
public:
	Mesh();
	Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Material> materials, vec3 startPosition);
	~Mesh();

	vector<Vertex> vertices;
	vector<unsigned int> indices;
	vector<Material> materials;

	vec3 getModelPosition();

	void Draw(shaderCreater shader);
	void DrawDepth(shaderCreater shader);
	void deallocate();
};



//#include "shaderCreater.h"
//
//#include <vector>
//#include <glm.hpp>
//#include <string>
//
//struct Vertex {
//	// position
//	glm::vec3 Position;
//	// normal
//	glm::vec3 Normal;
//	// texCoords
//	glm::vec2 TexCoords;
//	// tangent
//	glm::vec3 Tangent;
//	// bitangent
//	glm::vec3 Bitangent;
//};
//
//struct Texture {
//	unsigned int id;
//	std::string type;
//	std::string path;
//};
//
//class Mesh
//{
//private:
//	//Vertex Array Object and Vertex Buffer Object
//	GLuint VAO;
//	GLuint VBO;
//	GLuint EBO;
//
//	void setupMesh();
//public:
//
//	Mesh();
//	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
//	~Mesh();
//
//	//Mesh data
//	std::vector<Vertex> vertices;
//	std::vector<unsigned int> indices;
//	std::vector<Texture> textures;
//
//	void Draw(shaderCreater shader);
//	GLuint getVAO()const;
//	void deallocate();
//};
//
//#endif



#endif
