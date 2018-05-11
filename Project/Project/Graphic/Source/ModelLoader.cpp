#include "../header/ModelLoader.h"

ModelLoader::ModelLoader()
{

}

ModelLoader::~ModelLoader()
{
}


int ModelLoader::loadModel(const std::string& path)
{
	int result = find(modelPaths, path);

	if (result < 0)
	{
		Model model;
		if (model.load(path))
		{
			model.upload();

			result = models.getSize();

			models.add(model);
			modelPaths.add(path);
		}
	}

	return result;
}

void ModelLoader::renderModel(int index, int instances)
{
	models[index].render(instances);
}

int ModelLoader::loadTexture(const std::string& path)
{
	int result = find(texturePaths, path);

	if (result < 0)
	{
		Texture texture;
		if (texture.load(path))
		{
			texture.upload();

			result = textures.getSize();

			textures.add(texture);
			texturePaths.add(path);
		}
	}

	return result;
}

void ModelLoader::bindTexture(int index)
{
	textures[index].bind();
}

void ModelLoader::unload()
{
	for (int i = 0; i<models.getSize(); i++)
	{
		models[i].unload();
	}

	for (int i = 0; i<textures.getSize(); i++)
	{
		textures[i].unload();
	}


	models.clear();
	modelPaths.clear();

	textures.clear();
	texturePaths.clear();
}

int ModelLoader::find(Array<std::string>& paths, const std::string& path)
{
	int result = -1;
	for (int i = 0; i < paths.getSize() && result < 0; i++)
	{
		if (paths[i] == path)
		{
			result = i;
		}
	}

	return result;
}