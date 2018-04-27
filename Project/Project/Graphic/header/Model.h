#ifndef MODEL_H
#define MODEL_H


//My includes
#include "Mesh.h"
#include <stb_image.h>

//Other includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


//add the assimp includes here...
class Model
{
private:
	Assimp::Importer import;


	void loadModel(std::string const &path);
	//void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma = false);

public:
	Model();
	Model(std::string const &path);
	//Model(char* path);
	~Model();

	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	void Draw(shaderCreater shader);
	void deallocate();
};

#endif
