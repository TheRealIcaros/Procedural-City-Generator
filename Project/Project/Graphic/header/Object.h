#ifndef OBJECT_H
#define OBJECT_H

#include "OBJLoader.h"
#include "Mesh.h"

class Object
{
private:
	OBJLoader objLoader;
	
public:
	Object();
	~Object();

	vector<Mesh> meshes;

	void loadObject(const char* objPath, vec3 startPosition);
	void Draw(shaderCreater shader);
	void Sort(vec3 cameraPos);
	void DrawDepth(shaderCreater shader);
	void deallocate();
};

#endif // !OBJECT_H
