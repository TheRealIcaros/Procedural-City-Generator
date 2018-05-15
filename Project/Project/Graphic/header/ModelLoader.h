#ifndef MODELLOADER_H
#define MODELLOADER_H

#include "Model.h"

class ModelLoader
{
private:
	int find(Array<std::string>& paths, const std::string& path);

	Array<Model> models;
	Array<std::string> modelPaths;

	Array<Texture> textures;
	Array<std::string> texturePaths;

public:
	ModelLoader();
	~ModelLoader();

	int loadModel(const std::string& path);
	void renderModel(int index, int instances);

	int loadTexture(const std::string& path);
	void bindTexture(int index);


	void unload();
};

#endif
