#ifndef MODEL_H
#define MODEL_H

//My includes
#include "Mesh.h"

//Other includes
//add the assimp includes here...
class Model
{
private:
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	//void processMesh(aiNode* node, const aiScene* scene);
public:
	Model();
	Model(char* path);
	~Model();

	void Draw(shaderCreater shader);
};

#endif
