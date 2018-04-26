#ifndef MODEL_H
#define MODEL_H

//My includes
#include "Mesh.h"
#define STB_IMAGE_IMPLEMENTATION //This define makes the "stb_image.h" header to work like it was a .cpp file
#include "stb_image.h"

//Other includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma = false);

//add the assimp includes here...
class Model
{
private:
	/*struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};*/

	
	Assimp::Importer import;

	void loadModel(std::string path);
	//void loadModel(const char* path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	
public:
	Model();
	Model(char* path);
	~Model();

	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;

	void Draw(shaderCreater shader);
};

#endif
