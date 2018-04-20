#include "../header/Model.h"

Model::Model()
{
}

Model::~Model()
{
}

void Model::Draw(shaderCreater shader)
{
	for (unsigned int i = 0; i < meshes.size(); i++)
		meshes[i].Draw(shader);
}