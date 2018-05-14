#ifndef DEFERRED_H
#define DEFERRED_H

#include "Render.h"

#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <vector>

class Deferred
{
private:
	//Class object that the Deferred class uses
	shaderCreater geometryPass;
	shaderCreater lightingPass;

	//Camera* deferredCamera;

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

	//lightbuffer
	unsigned int lBuffer, lColor, lGlow;

	//Struct that models the lights
	struct Light
	{
		Light(glm::vec3 pos, glm::vec3 color)
		{
			lightPos = pos;
			lightColor = color;
		}

		glm::vec3 lightPos;
		glm::vec3 lightColor;
	};
	//Vector of the light-struct
	std::vector<Light> lights;

	//Render-functions
	void renderGeometryPass(Camera* camera);
	void renderLightingPass(Camera* camera);
	void renderQuad();

public:
	Deferred(Camera* camera);
	~Deferred();

	bool initiateDeferred(Camera* camera);
	GLuint getVAO()const;

	void render(Camera* camera);
};
#endif
