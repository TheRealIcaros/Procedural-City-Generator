#include "../header/Mesh.h"

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//Vertex position 
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
	// vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
	// vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	glBindVertexArray(0);
}

Mesh::Mesh()
{
}

Mesh::Mesh(std::vector <Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures, glm::vec3 startPosition)
{
	this->vertices = vertices;
	this->indices = indices;
	this->textures = textures;

	this->localPosition = startPosition;
	this->Model = glm::translate(this->Model, this->localPosition);

	setupMesh();
}

Mesh::~Mesh()
{
}

void Mesh::Draw(shaderCreater shader)
{
	unsigned int diffuseNr = 1;
	unsigned int specularNr = 1;

		for (unsigned int i = 0; i < textures.size(); i++)
		{
			glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
												  // retrieve texture number (the N in diffuse_textureN)
			std::string number;
			std::string name = textures[i].type;
			if (name == "texture_diffuse")
				number = std::to_string(diffuseNr++);
			else if (name == "texture_specular")
				number = std::to_string(specularNr++);

			shader.setFloat(("material." + name + number).c_str(), i);
			GLuint pos = glGetUniformLocation(shader.getShaderProgramID(), (name + number).c_str());
			glUniform1i(pos, i);
			glBindTexture(GL_TEXTURE_2D, textures[i].id);
		}

	//glActiveTexture(GL_TEXTURE0);
	GLuint pos = glGetUniformLocation(shader.getShaderProgramID(), "Model");
	glUniformMatrix4fv(pos, 1, GL_FALSE, &this->Model[0][0]);

	// draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}