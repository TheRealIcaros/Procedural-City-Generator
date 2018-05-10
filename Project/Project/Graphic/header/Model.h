#ifndef MODEL_H
#define MODEL_H

//#include "Texture.h"
#include "../../glew.h"
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <string>



class Model
{
private:

	struct Vertex
	{
		glm::vec3 position;
		glm::vec2 uv;
		glm::vec3 normal;
		glm::vec3 tangent;
		glm::vec3 bitangent;
	};

	Vertex* vertices;
	GLuint* indices;
	GLuint vertexBuffer, indexBuffer;
	GLuint vertexArray;
	int vertexCount, indexCount;

	

public:
	Model();
	~Model();

	bool load(const std::string& path);
	void unload();
	void upload();
	void render(int instances);

	GLuint getVertexArray() const;
	int getVertexCount() const;
	int getIndexCount() const;

};

#endif
