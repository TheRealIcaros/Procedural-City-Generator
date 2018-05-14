#include "../Header/Terrain.h"

Terrain::Terrain()
{

}

Terrain::Terrain(glm::vec3 startPosition, Array2D<float> heightMapPath, int texturePath)
{
	this->maxHeight = 0.10f;
	this->imageScale = 200.0f;
	this->terrainSizeX = heightMapPath.getWidth();
	this->terrainSizeY = heightMapPath.getHeight();

	this->imageWidth = terrainSizeX;
	this->imageHeight = terrainSizeY;

	this->terrainPosition = startPosition;
	this->texturePath = texturePath;
	this->imageData = heightMapPath;
	//this->imageData = loadHeightMap(heightMapPath);

	//if (this->imageData != NULL)
		createTerrain();

}

//Terrain::Terrain(glm::vec3 startPosition, const char *heightMapPath, int texturePath)
//{
//	this->maxHeight = 0.10f;
//	this->imageScale = 200.0f;
//	this->terrainSize = 128;
//
//	this->terrainPosition = startPosition;
//	this->texturePath = texturePath;
//	this->imageData = loadHeightMap(heightMapPath);
//
//	if (this->imageData != NULL)
//		createTerrain();
//}

Terrain::~Terrain()
{
	deallocate();
}

void Terrain::deallocate()
{
	for (int i = 0; i < this->imageWidth; i++)
	{
		delete this->heights[i];
	}
	delete[] this->heights;
	//SOIL_free_image_data(this->imageData);
	this->terrain.deallocate();
}

//unsigned char* Terrain::loadHeightMap(const char *path)
//{
//	int nrChannels;
//	//unsigned char* data = SOIL_load_image(path, &this->imageWidth, &this->imageHeight, &nrChannels, 0);
//
//	if (this->imageWidth != this->imageHeight)
//	{
//		std::cout << "Height map not square" << std::endl;
//		//SOIL_free_image_data(data);
//		//data = NULL;
//	}
//	if (/*!data*/false)
//	{
//		std::cout << "Failed to load height map" << std::endl;
//		//SOIL_free_image_data(data);
//		//data = NULL;
//	}
//
//	unsigned char* test = nullptr;
//	//return data;
//	return test;
//}

void Terrain::createTerrain()
{
	this->heights = new float*[this->terrainSizeY];
	for (int i = 0; i < this->terrainSizeY; i++)
	{
		this->heights[i] = new float[this->terrainSizeX];
	}

	int index = 0;
	for (int z = 0; z < this->terrainSizeY-1; z++)
	{
		for (int x = 0; x < this->terrainSizeX-1; x++)
		{
			/*float gray = ((float)this->imageData[index] +
				(float)this->imageData[index + 1] +
				(float)this->imageData[index + 2]) / 3;

			index += 3;*/
			float gray = imageData[index];
			gray = gray * this->maxHeight;
			glm::vec3 position;
			position.x = (this->terrainSizeX / this->imageWidth) * x;
			position.y = gray + this->terrainPosition.y;
			position.z = (this->terrainSizeY / this->imageHeight) * z;
			vertices.push_back(position);
			this->heights[x][z] = float(position.y + this->terrainPosition.y);

			glm::vec2 uv;
			uv.x = (float)(1.0f / (float)this->imageWidth) * (float)x * this->imageScale;
			uv.y = (float)(1.0f / (float)this->imageHeight) * (float)z * this->imageScale;
			this->uvs.push_back(uv);
		}
	}
	triangulate();
	sendToObject();
}

void Terrain::triangulate()
{
	for (int z = 0; z < this->imageHeight - 1; z++)
	{
		for (int x = 0; x < this->imageWidth - 1; x++)
		{
			//First triangle
			this->indices.push_back(this->imageWidth * z + x);
			this->indices.push_back((this->imageWidth * z + x) + this->imageWidth);
			this->indices.push_back((this->imageWidth * z + x) + 1);

			//Second triangle
			this->indices.push_back((this->imageWidth * z + x) + 1);
			this->indices.push_back((this->imageWidth * z + x) + this->imageWidth);
			this->indices.push_back((this->imageWidth * z + x) + this->imageWidth + 1);

			/*printf("p0: %d, p1: %d, p2: %d\n", triangles[index], triangles[index + 1], triangles[index + 2]);
			printf("p0: %d, p1: %d, p2: %d\n\n", triangles[index + 3], triangles[index + 4], triangles[index + 5]);*/
		}
	}
}

float Terrain::getPixelColor(glm::vec2 pos)
{
	glm::vec3 color;

	color.r = (float)this->imageData[(int)pos.y * this->imageWidth + (int)pos.x];
	color.g = (float)this->imageData[(int)pos.y * this->imageWidth + (int)pos.x + 1];
	color.b = (float)this->imageData[(int)pos.y * this->imageWidth + (int)pos.x + 2];

	return (color.r + color.g + color.b) / 3;
}

void Terrain::sendToObject()
{
	std::vector<TerrainVertex> outData;
	for (int i = 0; i < vertices.size(); i++)
	{
		TerrainVertex temp;
		vertices[i].y =* imageData.getData();
		temp.Position = vertices[i];
		//temp.Position = vertices[i];
		temp.TexCoords = uvs[i];
		outData.push_back(temp);
	}

	std::vector<TerrainMaterial> materials;
	TerrainMaterial material;
	material.name = "Terrain";
	TerrainTexture tempTexture;
	tempTexture.id = texturePath;
	//tempTexture.id = objLoader.TextureFromFile(this->texturePath.c_str());
	tempTexture.type = "texture_diffuse";
	tempTexture.path = this->texturePath;
	material.textures.push_back(tempTexture);

	material.colorAmbient  = glm::vec3(0.5, 0.2, 0.2);
	material.colorDiffuse  = glm::vec3(0.4, 0.8, 0.8);
	material.colorSpecular = glm::vec3(0.1, 0.8, 0.8);
	material.specularExponent = 32;

	materials.push_back(material);

	this->terrain = Mesh(outData, this->indices, materials, this->terrainPosition);
}

void Terrain::Draw(shaderCreater shader, int textID)
{
	glUseProgram(shader.getShaderProgramID());
	this->terrainTexture.bind(textID);
	this->terrain.Draw(shader);
}

float Terrain::getHeightOfTerrain(float worldX, float worldZ)
{
	float terrainX = worldX - this->terrainPosition.x;
	float terrainZ = worldZ - this->terrainPosition.z;
	float gridSquareSize = this->terrainSizeX / (this->imageWidth - 1);

	int gridX = (int)floor(terrainX / gridSquareSize);
	int gridZ = (int)floor(terrainZ / gridSquareSize);

	if (gridX >= this->imageWidth - 1 || gridZ >= this->imageHeight - 1 || gridX < 0 || gridZ < 0)
	{
		return 0.0f;
	}

	float xCoord = fmod(terrainX, gridSquareSize) / gridSquareSize;
	float zCoord = fmod(terrainZ, gridSquareSize) / gridSquareSize;

	float result;

	if (xCoord <= (1 - zCoord))
	{
		result = this->barryCentric(glm::vec3(0.0, this->heights[gridX][gridZ], 0.0),
			glm::vec3(1.0, this->heights[gridX + 1][gridZ], 0.0),
			glm::vec3(0.0, this->heights[gridX][gridZ + 1], 1.0),
			glm::vec2(xCoord, zCoord));
	}
	else
	{
		result = this->barryCentric(glm::vec3(1.0, this->heights[gridX + 1][gridZ], 0.0),
			glm::vec3(1.0, this->heights[gridX + 1][gridZ + 1], 1.0),
			glm::vec3(0.0, this->heights[gridX][gridZ + 1], 1.0),
			glm::vec2(xCoord, zCoord));
	}

	return result;
}

float Terrain::barryCentric(glm::vec3 p1, glm::vec3 p2, glm::vec3 p3, glm::vec2 pos)
{
	float det = (p2.z - p3.z) * (p1.x - p3.x) + (p3.x - p2.x) * (p1.z - p3.z);
	float l1 = ((p2.z - p3.z) * (pos.x - p3.x) + (p3.x - p2.x) * (pos.y - p3.z)) / det;
	float l2 = ((p3.z - p1.z) * (pos.x - p3.x) + (p1.x - p3.x) * (pos.y - p3.z)) / det;
	float l3 = 1.0f - l1 - l2;
	return l1 * p1.y + l2 * p2.y + l3 * p3.y;
}

void Terrain::DrawDepth(shaderCreater shader)
{
	this->terrain.DrawDepth(shader);
}

//unsigned int Terrain::TextureFromFile(const char* texturePath)
//{
//	//unsigned int textureID;
//	//glGenTextures(1, &textureID);
//	//
//	////int width, height, nrComponents;
//	////unsigned char *data = SOIL_load_image(texturePath, &width, &height, &nrComponents, SOIL_LOAD_AUTO);
//	////if (data)
//	//{
//	//	/*GLenum format;
//	//	if (nrComponents == 1)
//	//		format = GL_RED;
//	//	else if (nrComponents == 3)
//	//		format = GL_RGBA;
//	//	else if (nrComponents == 4)
//	//		format = GL_RGBA;*/
//	//
//	//	//glBindTexture(GL_TEXTURE_2D, textureID);
//	//	////glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
//	//	//glGenerateMipmap(GL_TEXTURE_2D);
//	//
//	//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//	//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//	//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
//	//	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//	//
//	//	//SOIL_free_image_data(data);
//	//}
//	///*else
//	//{
//	//	std::cout << "Texture failed to load at path: " << texturePath << std::endl;
//	//	SOIL_free_image_data(data);
//	//}*/
//	//
//	//return textureID;
//	return unsigned int 0
//}