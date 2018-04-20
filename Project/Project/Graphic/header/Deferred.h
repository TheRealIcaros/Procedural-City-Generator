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
#include <vector>


class Deferred
{
private:
	//Class object that the Deferred class uses
	shaderCreater geometryPass;
	shaderCreater lightingPass;
	Camera* camera;
	Object object;

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
	void renderGeometryPass();
	void renderLightingPass();
	void renderQuad();

public:
	Deferred();
	~Deferred();

	bool initiateDeferred();

	void render();
};

#endif
