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

	//Initiation of classes used by the Deferred class
	this->camera = new Camera();

	//Matrices and initiation of them
	this->World = WorldMatrix();
	this->Projection = ProjectionMatrix();
	
}

bool Deferred::initiateDeferred()
{
	bool returnValue = true;
	
	//Creates the G-Buffer for the Deferred class
	createGbuffer();

	//Creates the Uniform Buffer Object for the Deferred class
	createUBO();

	this->gpuBufferData = { World, camera->getView(), Projection };

	this->geometryPass.createShader("./Graphic/Shaders/vertex", "NULL", "./Graphic/Shaders/fragment");

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

void Deferred::renderGeometryPass()
{

}

void Deferred::renderLightingPass()
{

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

Deferred::Deferred()
{
	initiateVariables();
}

Deferred::~Deferred()
{

}

GLuint Deferred::getVAO()const
{
	return this->VAO;
}

void Deferred::render()
{
	//1. first the geometry rendering pass
	renderGeometryPass();

	//2. Then the lighting rendering pass
	renderLightingPass();


}