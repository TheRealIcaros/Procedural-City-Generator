#include "../header/Model.h"

Model::Model()
	: vertexBuffer(0), indexBuffer(0), vertexArray(0), vertexCount(0), indexCount(0)
{
}

Model::~Model()
{
}

bool Model::load(const std::string& path)
{
	bool result = false;

	FILE* file = fopen(path.c_str(), "rb");
	if (file)
	{
		fread(&vertexCount, sizeof(vertexCount), 1, file);
		fread(&indexCount, sizeof(indexCount), 1, file);

		vertices = new Vertex[vertexCount];
		indices = new GLuint[indexCount];

		fread(vertices, sizeof(Vertex), vertexCount, file);
		fread(indices, sizeof(GLuint), indexCount, file);

		fclose(file);

		result = true;
	}

	return result;
}

void Model::unload()
{
	if (vertexArray > 0)
	{
		glBindVertexArray(vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		glDeleteBuffers(1, &vertexBuffer);
		glDeleteBuffers(1, &indexBuffer);
		glDeleteVertexArrays(1, &vertexArray);
	}

	vertexBuffer = indexBuffer = vertexArray = 0;
	vertexCount = indexCount = 0;
}

void Model::upload()
{
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	const int MAX_ATTRIB = 5;
	for (int i = 0; i<MAX_ATTRIB; i++)
	{
		glEnableVertexAttribArray(i);
	}

	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &indexBuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);

	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*vertexCount, vertices, GL_STATIC_DRAW);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint)*indexCount, indices, GL_STATIC_DRAW);

	// position, uv, normal, tangent, bitangent
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), 0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(GLfloat) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(GLfloat) * 5));
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(GLfloat) * 8));
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(sizeof(GLfloat) * 11));

	glBindVertexArray(0);

	delete[] vertices;
	delete[] indices;

	vertices = nullptr;
	indices = nullptr;
}

void Model::render(int instances)
{
	glBindVertexArray(vertexArray);
	glDrawElementsInstanced(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL, instances);
	//glDrawElements(GL_TRIANGLES, indexCount, GL_UNSIGNED_INT, NULL);
}

GLuint Model::getVertexArray() const
{
	return vertexArray;
}

int Model::getVertexCount() const
{
	return vertexCount;
}

int Model::getIndexCount() const
{
	return indexCount;
}