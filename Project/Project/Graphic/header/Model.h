#ifndef MODEL_H
#define MODEL_H

//My includes
#include "Mesh.h"

//Other includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

//add the assimp includes here...
class Model
{
private:
	struct Texture
	{
		unsigned int id;
		std::string type;
		std::string path;
	};


	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	Assimp::Importer import;

	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	//void processMesh(aiNode* node, const aiScene* scene);
public:
	Model();
	Model(char* path);
	~Model();

	void Draw(shaderCreater shader);
};

#endif
