#include "../header/Mesh.h"

//void Mesh::setupMesh()
//{
//	//glGenVertexArrays(1, &VAO);
//	//glGenBuffers(1, &VBO);
//	//glGenBuffers(1, &EBO);
//	//
//	//glBindVertexArray(VAO);
//	//glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	//
//	//glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
//	//
//	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	//glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
//	//	&indices[0], GL_STATIC_DRAW);
//	//
//	//// vertex positions
//	//glEnableVertexAttribArray(0);
//	//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//	//// vertex normals
//	//glEnableVertexAttribArray(1);
//	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
//	//// vertex texture coords
//	//glEnableVertexAttribArray(2);
//	//glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
//	//
//	//glBindVertexArray(0);
//
//	// create buffers/arrays
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	glGenBuffers(1, &EBO);
//
//	glBindVertexArray(VAO);
//	// load data into vertex buffers
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	// A great thing about structs is that their memory layout is sequential for all its items.
//	// The effect is that we can simply pass a pointer to the struct and it translates perfectly to a glm::vec3/2 array which
//	// again translates to 3/2 floats which translates to a byte array.
//	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);
//
//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
//	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);
//
//	// set the vertex attribute pointers
//	// vertex Positions
//	glEnableVertexAttribArray(0);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
//	// vertex normals
//	glEnableVertexAttribArray(1);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
//	// vertex texture coords
//	glEnableVertexAttribArray(2);
//	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
//	// vertex tangent
//	glEnableVertexAttribArray(3);
//	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
//	// vertex bitangent
//	glEnableVertexAttribArray(4);
//	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
//
//	glBindVertexArray(0);
//}
//
//Mesh::Mesh()
//{
//	// Vertex Array Object and Vertex Buffer Object
//	this->VAO = 0;
//	this->VBO = 0;
//}
//
//Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
//{
//	// Vertex Array Object and Vertex Buffer Object
//	this->VAO = 0;
//	this->VBO = 0;
//
//	this->vertices = vertices;
//	this->indices = indices;
//	this->textures = textures;
//
//	setupMesh();
//}
//
//Mesh::~Mesh()
//{
//}
//
//void Mesh::Draw(shaderCreater shader)
//{
//	//unsigned int diffuseNr = 1;
//	//unsigned int specularNr = 1;
//	//for (unsigned int i = 0; i < textures.size(); i++)
//	//{
//	//	glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
//	//									  // retrieve texture number (the N in diffuse_textureN)
//	//	std::string number;
//	//	std::string name = textures[i].type;
//	//	if (name == "texture_diffuse")
//	//		number = std::to_string(diffuseNr++);
//	//	else if (name == "texture_specular")
//	//		number = std::to_string(specularNr++);
//	//
//	//	shader.setFloat(("material." + name + number).c_str(), i);
//	//	glBindTexture(GL_TEXTURE_2D, textures[i].id);
//	//}
//	//glActiveTexture(GL_TEXTURE0);
//	//
//	//// draw mesh
//	//glBindVertexArray(VAO);
//	//glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//	//glBindVertexArray(0);
//
//	// bind appropriate textures
//	unsigned int diffuseNr = 1;
//	unsigned int specularNr = 1;
//	unsigned int normalNr = 1;
//	unsigned int heightNr = 1;
//	for (unsigned int i = 0; i < textures.size(); i++)
//	{
//		glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
//										  // retrieve texture number (the N in diffuse_textureN)
//		std::string number;
//		std::string name = textures[i].type;
//		if (name == "texture_diffuse")
//			number = std::to_string(diffuseNr++);
//		else if (name == "texture_specular")
//			number = std::to_string(specularNr++); // transfer unsigned int to stream
//		else if (name == "texture_normal")
//			number = std::to_string(normalNr++); // transfer unsigned int to stream
//		else if (name == "texture_height")
//			number = std::to_string(heightNr++); // transfer unsigned int to stream
//
//												 // now set the sampler to the correct texture unit
//		glUniform1i(glGetUniformLocation(shader.getShaderProgramID(), (name + number).c_str()), i);
//		// and finally bind the texture
//		glBindTexture(GL_TEXTURE_2D, textures[i].id);
//	}
//
//	// draw mesh
//	glBindVertexArray(VAO);
//	glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
//	glBindVertexArray(0);
//
//	// always good practice to set everything back to defaults once configured.
//	glActiveTexture(GL_TEXTURE0);
//}
//
//GLuint Mesh::getVAO()const
//{
//	return this->VAO;
//}
//
//void Mesh::deallocate()
//{
//	glDeleteVertexArrays(1, &VAO);
//	glDeleteBuffers(1, &VBO);
//	glDeleteBuffers(1, &EBO);
//}

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

	//vertex positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);

	//vertex normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));

	//vertex texture coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));

	//tangent coords
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));

	//bitangent coords
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));

	glBindVertexArray(0);
}

//Public
Mesh::Mesh()
{

}

Mesh::Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Material> materials, vec3 startPosition)
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

vec3 Mesh::getModelPosition()
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
			stringstream ss;
			string number;
			string name = materials[i].textures[j].type;
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
