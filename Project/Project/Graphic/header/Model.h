#ifndef MODEL_H
#define MODEL_H

//Own headers
#include "Mesh.h"

//Other headers
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <stb_image.h>

class Model
{
private:
	
	/*  Functions   */
	void loadModel(std::string path);
	void processNode(aiNode *node, const aiScene *scene);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene);
	//std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

	unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
public:
	Model();
	~Model();

	Model(std::string const &path, bool gamma = false);
	//Model(char *path);

	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;
	void Draw(shaderCreater shader);
};

#endif
