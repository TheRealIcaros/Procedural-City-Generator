#include "../header/Deferred.h"

void Deferred::initiateVariables()
{
	// Vertex Array Object and Vertex Buffer Object
	this->VAO = 0;
	this->VBO = 0;

	//Uniform buffer Object
	this->UBO = 0;

	//Quad values
	this->quadVAO = 0;
	this->quadVBO = 0;

	//G-buffer values
	this->gBuffer = 0;
	this->gPosition = 0;
	this->gNormal = 0;
	this->gColorSpec = 0;
	this->gColorInfo = 0;

	//Light-buffer values
	this->lBuffer = 0;
	this->lColor = 0;
	this->lGlow = 0;

	//Initiation of classes used by the Deferred class
	//this->camera = new Camera();

	//Matrices and initiation of them
	this->World = WorldMatrix();
	this->Projection = ProjectionMatrix();

}

bool Deferred::initiateDeferred(Camera* camera)
{
	bool returnValue = true;

	//Creates the shader-program
	//objectShader.createShader("./Models/shaders/basic", "NULL", "./Models/shaders/basic");
	this->geometryPass.createShader("./Graphic/Shaders/GeometryPassVS", "NULL", "./Graphic/Shaders/GeometryPassFS");
	this->lightingPass.createShader("./Graphic/Shaders/LightingPassVS", "NULL", "./Graphic/Shaders/LightingPassFS");


	//Creates the G-Buffer for the Deferred class
	createGbuffer();

	//Creates the Uniform Buffer Object for the Deferred class
	createUBO();

	//Creates the buffer, that sends data from CPU o GPU
	//this->gpuBufferData = { World, camera.getView(), Projection };
	this->gpuBufferData = { World, camera->getView(), Projection };

	//This creates the lights in the scene
	lights.push_back(Light(glm::vec3(15.0, -6.0, 12.0), glm::vec3(1.0, 1.0, 1.0)));

	

	return returnValue;
}

void Deferred::createUBO()
{
	//Create a Uniform Buffer Object(UBO)
	//Create a buffer name
	glGenBuffers(1, &UBO);
	//Bind buffer to work further with it
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	//Allocate memory for the buffer in the GPU
	glBufferData(GL_UNIFORM_BUFFER, sizeof(valuesFromCPUToGPU), NULL, GL_STATIC_DRAW);
	//Because we hard-coded "Binding = 3" in the shader we can do this:
	//Bind Uniform Buffer to binding point 3 (without caring about index of UBO)
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, UBO);
	//Good practice , unbind buffer
	glBindBuffer(GL_UNIFORM_BUFFER, 0);
}

void Deferred::createGbuffer()
{
	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

	//position color buffer
	glGenTextures(1, &gPosition);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WIDTH, HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPosition, 0);

	//normal color buffer
	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, WIDTH, HEIGHT, 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

	//color buffer
	glGenTextures(1, &gColorSpec);
	glBindTexture(GL_TEXTURE_2D, gColorSpec);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, WIDTH, HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gColorSpec, 0);

	//Ambient, Diffuse, Specular och Shininess color buffer
	glGenTextures(1, &gColorInfo);
	glBindTexture(GL_TEXTURE_2D, gColorInfo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, WIDTH, HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, gColorInfo, 0);

	//tell OPENGL which color vi ska använda (av denna framebuffer) for rendering på svenska
	//TOP OF THE KOD

	unsigned int attachments[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 };
	glDrawBuffers(4, attachments);
	//add djupbufé 

	unsigned int rboDepth;
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, WIDTH, HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
}

glm::mat4 Deferred::WorldMatrix()
{
	glm::mat4 World;
	return World;
}

glm::mat4 Deferred::ProjectionMatrix()
{
	float FOV = 0.45f * PI;
	float aspectRatio = 640 / 480;

	glm::mat4 Projection = glm::perspective(FOV, aspectRatio, 0.1f, 200.0f);

	return Projection;
}

void Deferred::renderGeometryPass(Camera* camera)
{
	//Use GeometryPass Shader Program
	glUseProgram(geometryPass.getShaderProgramID());
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Bind UBO for sending GPU data to GeometryPass Program
	glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(valuesFromCPUToGPU), &gpuBufferData);

	/*
	glActiveTexture(GL_TEXTURE19);
	glUniform1i(glGetUniformLocation(geometryPass.getShaderProgramID(), "depthMap"), 19);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glUniformMatrix4fv(glGetUniformLocation(geometryPass.getShaderProgramID(), "lightSpaceMatrix"), 1, GL_FALSE, &lightSpaceTransFormMatrix[0][0]);
	*/

	//Back face culling camera pos
	//glUniform3fv(glGetUniformLocation(geometryPass.getShaderProgramID(), "cameraPos"), 1, &camera.getPosition()[0]);
	glUniform3fv(glGetUniformLocation(geometryPass.getShaderProgramID(), "cameraPos"), 1, &camera->getPosition()[0]);

	glm::vec3 lightDir = glm::vec3(5.0, -12.0, 6.0);
	glUniform3fv(glGetUniformLocation(geometryPass.getShaderProgramID(), "lightDir"), 1, &lightDir[0]);

	//terrain.Draw(geometryPass);
	//objects.Draw(geometryPass);

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Deferred::renderLightingPass(Camera* camera)
{
	glBindFramebuffer(GL_FRAMEBUFFER, lBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Use LightingPass Shader Program
	glUseProgram(lightingPass.getShaderProgramID());

	//	Bind all gBufferTextures
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gPosition);
	glUniform1i(glGetUniformLocation(lightingPass.getShaderProgramID(), "gPosition"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glUniform1i(glGetUniformLocation(lightingPass.getShaderProgramID(), "gNormal"), 1);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gColorSpec);
	glUniform1i(glGetUniformLocation(lightingPass.getShaderProgramID(), "gColorSpec"), 2);

	glActiveTexture(GL_TEXTURE3);
	glUniform1i(glGetUniformLocation(lightingPass.getShaderProgramID(), "gColorInfo"), 3);
	glBindTexture(GL_TEXTURE_2D, gColorInfo);

	//	TODO:(Fix multiple lights and send it to LightingPassFS)
	GLuint lightPos = glGetUniformLocation(lightingPass.getShaderProgramID(), "nrOfLights");
	glUniform1i(lightPos, lights.size());
	for (int i = 0; i < lights.size(); i++)
	{
		std::string lightPos = "lights[" + std::to_string(i) + "].Position";
		std::string lightColor = "lights[" + std::to_string(i) + "].Color";

		glUniform3fv(glGetUniformLocation(lightingPass.getShaderProgramID(), lightPos.c_str()), 1, &lights[i].lightPos[0]);
		glUniform3fv(glGetUniformLocation(lightingPass.getShaderProgramID(), lightColor.c_str()), 1, &lights[i].lightColor[0]);
	}

	//glUniform3f(glGetUniformLocation(lightingPass.getShaderProgramID(), "viewPos"), camera.getPosition().x, camera.getPosition().y, camera.getPosition().z);
	glUniform3f(glGetUniformLocation(lightingPass.getShaderProgramID(), "viewPos"), camera->getPosition().x, camera->getPosition().y, camera->getPosition().z);

	//glUniform1i(glGetUniformLocation(lightingPass.getShaderProgramID(), "glowKey"), glowKey);
	//glUniform1i(glGetUniformLocation(lightingPass.getShaderProgramID(), "intensityKey"), intensityKey);

	//Render To Quad
	renderQuad();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void Deferred::renderQuad()
{
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};

		// Setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}

	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

Deferred::Deferred(Camera* camera)
{
	initiateVariables();
	initiateDeferred(camera);
}

Deferred::~Deferred()
{
	//delete camera;
}

GLuint Deferred::getVAO()const
{
	return this->VAO;
}

void Deferred::render(Camera* camera)
{
	//1. first the geometry rendering pass
	renderGeometryPass(camera);

	//2. Then the lighting rendering pass
	renderLightingPass(camera);

}