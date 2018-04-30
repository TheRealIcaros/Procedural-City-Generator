#ifndef OBJLOADER_H
#define OBJLOADER_H


#include "SOIL.h"
#include "Mesh.h"

 //My includes
#include <stb_image.h>
#include <vector>

//Other includes
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

using namespace std;
using namespace glm;

class OBJLoader
{
private:

public:
	OBJLoader();
	~OBJLoader();

	bool loadOBJ(const char* objPath, vector<vec3> &vertices,
		vector<vec2> &uvs, vector<vec3> &normals, vector<vec3> &tangent, vector<Material> &materials);
	bool loadMTL(const char* path, const char* mtlFile, vector<Material> &materials);
	unsigned int TextureFromFile(const char* texturePath);
};

#endif
