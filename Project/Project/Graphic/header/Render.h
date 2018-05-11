#ifndef RENDER_H
#define RENDER_H

//Inlcuded classes
#include "ModelLoader.h"
#include "Camera.h"

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

	// Object variables
	shaderCreater objectShader;
	Camera perspectiveCamera;

	Array<ObjectElement> objectElements;
	Array<ObjectInstance> objectInstances;
	Array<glm::mat4> worldMatrices;

	GLuint objectWorldLocation;
	GLuint objectProjectionLocation;
	GLuint objectViewLocation;

public:
	Render();
	~Render();

	void load();
	void unload();

	void begin();
	void end();

	void addElement(int model, int texture, const glm::vec3& position);
	void render(ModelLoader* models);
	//void render(Assets::AssetManager* assets);

	shaderCreater* getObjectShader();
	shaderCreater* getTextShader();

};

#endif
