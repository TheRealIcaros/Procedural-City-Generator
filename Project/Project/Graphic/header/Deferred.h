#ifndef DEFERRED_H
#define DEFERRED_H

//My classes
#include "shaderCreater.h"
#include "Camera.h"
#include "Object.h"
#include "../../Defines.h"

//Other classes
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>

class Deferred
{
private:
	//Class object that the Deferred class uses
	shaderCreater geometryPass;
	Camera* camera;

	//Vertex Array Object and Vertex Buffer Object
	GLuint VAO;
	GLuint VBO;

	//Quad values
	unsigned int quadVAO;
	unsigned int quadVBO;

	//Uniform Buffer Object
	GLuint UBO = 0;

	//gbuffer stuff
	unsigned int gBuffer, gPosition, gNormal, gColorSpec, gColorInfo;

	//Initiation-functions for the Deferred class
	void initiateVariables();
	void createUBO();
	void createGbuffer();

	//Matrices and functions for them
	glm::mat4 World, View, Projection;
	glm::mat4 WorldMatrix();
	glm::mat4 ProjectionMatrix();

	//Struct that sends data to the GPU
	struct valuesFromCPUToGPU
	{
		glm::mat4 World;
		glm::mat4 View;
		glm::mat4 Projection;
	};
	//The buffer data
	valuesFromCPUToGPU gpuBufferData;

	//Render-functions
	void renderGeometryPass();
	void renderLightingPass();
	void renderQuad();

public:
	Deferred();
	~Deferred();

	bool initiateDeferred();
	GLuint getVAO()const;

	void render();
};

#endif
