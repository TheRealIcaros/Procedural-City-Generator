#include "../header/Mesh.h"

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(TerrainVertex), &vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

	//vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)0);

	//vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, Normal));

	//vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, TexCoords));

	//tangent coords
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, Tangent));

	//bitangent coords
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(TerrainVertex), (void*)offsetof(TerrainVertex, Bitangent));

	glBindVertexArray(0);
}

//Public
Mesh::Mesh()
{

}

Mesh::Mesh(std::vector<TerrainVertex> vertices, std::vector<unsigned int> indices, std::vector<TerrainMaterial> materials, glm::vec3 startPosition)
{
	this->vertices = vertices;
	this->indices = indices;
	this->materials = materials;

	this->localPosition = startPosition;
	this->Model = translate(this->Model, this->localPosition);

	setupMesh();
}

Mesh::~Mesh()
{

}

glm::vec3 Mesh::getModelPosition()
{
	return this->localPosition;
}

void Mesh::Draw(shaderCreater shader)
{
	unsigned int diffuseNr = 1;
	unsigned int normalNr = 1;
	for (unsigned int i = 0; i < materials.size(); i++)
	{
		//Material Properties
		glUniform3fv(glGetUniformLocation(shader.getShaderProgramID(), "material.ambient"), 1, &materials[i].colorAmbient[0]);
		glUniform3fv(glGetUniformLocation(shader.getShaderProgramID(), "material.diffuse"), 1, &materials[i].colorDiffuse[0]);
		glUniform3fv(glGetUniformLocation(shader.getShaderProgramID(), "material.specular"), 1, &materials[i].colorSpecular[0]);
		shader.setFloat("material.shininess", materials[i].specularExponent);

		for (unsigned int j = 0; j < materials[i].textures.size(); j++)
		{
			//activate proper texture unit before binding
			glActiveTexture(GL_TEXTURE0 + j);

			//retrieve texture number (the N in diffuse_textureN)
			std::stringstream ss;
			std::string number;
			std::string name = materials[i].textures[j].type;
			if (name == "texture_diffuse")
				ss << diffuseNr++;
			else if (name == "texture_normal")
				ss << normalNr++;
			number = ss.str();

			GLuint pos = glGetUniformLocation(shader.getShaderProgramID(), (name + number).c_str());
			glUniform1i(pos, j);
			glBindTexture(GL_TEXTURE_2D, materials[i].textures[j].id);
		}
	}

	GLuint pos = glGetUniformLocation(shader.getShaderProgramID(), "Model");
	glUniformMatrix4fv(pos, 1, GL_FALSE, &this->Model[0][0]);

	//Draw mesh
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::DrawDepth(shaderCreater shader)
{
	GLuint pos = glGetUniformLocation(shader.getShaderProgramID(), "Model");
	glUniformMatrix4fv(pos, 1, GL_FALSE, &this->Model[0][0]);

	//Draw depth
	glBindVertexArray(VAO);
	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

	glActiveTexture(GL_TEXTURE0);
}

void Mesh::deallocate()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
}
