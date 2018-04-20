#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"

class Model
{
private:
	std::vector<Mesh> meshes;
	std::string directory;

	void loadModel(std::string path);
	void processMesh();
public:
	Model();
	Model(char* path);
	~Model();

	void Draw(shaderCreater shader);
};

#endif
