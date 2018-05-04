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
	void processNode(aiNode *node, const aiScene *scene, glm::vec3 startPosition);
	Mesh processMesh(aiMesh *mesh, const aiScene *scene, glm::vec3 startPosition);
	std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName);

	unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma);
public:
	Model();
	~Model();

	Model(std::string const &path, glm::vec3 startPosition, bool gamma = false);
	void loadModel(std::string path, glm::vec3 startPosition);
	//Model(char *path);

	std::vector<Texture> textures_loaded;
	std::vector<Mesh> meshes;
	std::string directory;
	bool gammaCorrection;
	void Draw(shaderCreater shader);
};

#endif
