#ifndef DEFERRED_H
#define DEFERRED_H

//My classes
#include "shaderCreater.h"
#include "Object.h"
#include "../../Defines.h"

//Other classes
#include <glad\glad.h>
#include <GLFW\glfw3.h>

class Deferred
{
private:
	shaderCreater geometryPass;

	GLuint VAO;
	GLuint VBO;

	//Quad
	unsigned int quadVAO;
	unsigned int quadVBO;

	//Uniform Buffer Object
	GLuint UBO = 0;

	//gbuffer stuff
	unsigned int gBuffer, gPosition, gNormal, gColorSpec, gColorInfo;

	void initiateVariables();
	bool initiateDeferred();

	//Struct that sends data to the GPU

public:
	Deferred();
	~Deferred();

	void createUBP();
	void createGbuffer();

	GLuint getVAO()const;
};

#endif
