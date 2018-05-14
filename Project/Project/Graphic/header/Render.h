#ifndef RENDER_H
#define RENDER_H

//Inlcuded classes
#include "ModelLoader.h"
#include "Terrain.h"
#include "..\..\Controlls\Header\KeyIn.h"

struct ObjectElement
{
	int32_t model;
	int32_t texture;
	glm::vec3 position;
};

struct ObjectInstance
{
	int model;
	int texture;
	int instances;
};

class Render
{
private:

	static const int MAX_INSTANCES_PER_DRAW = 100;

	// Object variables
	shaderCreater objectShader;
	shaderCreater terrainShader;
	Camera myCamera;

	Array<ObjectElement> objectElements;
	Array<ObjectInstance> objectInstances;
	Array<glm::mat4> worldMatrices;

	GLuint objectWorldLocation;
	GLuint objectProjectionLocation;
	GLuint objectViewLocation;

public:
	Render();
	~Render();

	void load(GLFWwindow* window);
	void unload();

	void begin();
	void end();

	void addElement(int model, int texture, const glm::vec3& position);
	void render(ModelLoader* models);
	void render(int texture, Terrain* terrain);
	GLuint getObjectShader();
	Camera* getCamera();
};

#endif
