#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <fstream>
#include <string>
#include "Imgui\imgui.h"

#include "Graphic\header\shaderCreater.h"

//3D-math
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//Defines
#include "Defines.h"

void initiateGLFW();
void resizeWindow(GLFWwindow* window, int width, int height);
bool initiateWindow(GLFWwindow* window);
bool startSequence(GLFWwindow* window);
void keyInput(GLFWwindow* window);
void createTriangleData();
void render();

//shader values
shaderCreater renderPass;

//Global values
GLuint VBO = 0;
GLuint VAO = 0;

GLuint gUbo = 0;  //Uniform Buffer Object identifyer

glm::mat4 WorldMatrix()
{
	glm::mat4 World;

	//This rotates my matrices
	World = glm::rotate(World, 180.0f, glm::vec3(0, 1, 0));

	return World;
}

glm::mat4 ViewMatrix()
{
	glm::vec3 cameraPos(0.0f, 0.0f, -2.0f);
	glm::vec3 lookAtVector(0.0f, 0.0f, 0.0f);
	glm::vec3 upVector(0.0f, 1.0f, 0.0f);

	glm::mat4 View = glm::lookAt(cameraPos, lookAtVector, upVector);

	return View;
}

glm::mat4 ProjectionMatrix()
{
	float FOV = 0.45f * PI;
	float aspectRatio = 640 / 480;

	glm::mat4 Projection = glm::perspective(FOV, aspectRatio, 0.1f, 20.0f);

	return Projection;
}

//My matrices
glm::mat4 World = WorldMatrix();
glm::mat4 View = ViewMatrix();
glm::mat4 Projection = ProjectionMatrix();

//The struct to be stored in a buffer
struct valuesFromCPUToGPU
{
	glm::mat4 World;
	glm::mat4 View;
	glm::mat4 Projection;
};

//The buffer data I send
valuesFromCPUToGPU myBufferData = { World, View, Projection };

int main()
{
	////BLARG
	initiateGLFW();
	
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);;

	if (startSequence(window) == false)
	{
		glfwTerminate();
		return -1;
	}

	renderPass.createShader("Graphic/Shaders/vertexShader", "NULL", "Graphic/Shaders/fragmentShader");
	createTriangleData();

	while (!glfwWindowShouldClose(window))
	{
		//inputs from the keyboard
		keyInput(window);

		//rendering happens here...
		render();
		
		//Checks the call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}


	glfwTerminate();
	return 0;
}

void initiateGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void resizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool initiateWindow(GLFWwindow* window)
{
	bool returnValue = true;
	
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		returnValue = false;
	}
	

	return returnValue;
}

bool startSequence(GLFWwindow* window)
{
	bool returnValue = true;

	if (initiateWindow(window) == false)
		returnValue = false;

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		returnValue = false;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, resizeWindow);

	return returnValue;
}

void keyInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS && keyIsPressedF1 == false)
	{
		keyIsPressedF1 = true;
		std::cout << "HEJ HEJ" << std::endl;
	}
	else if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_RELEASE && keyIsPressedF1 == true)
	{
		keyIsPressedF1 = false;
		std::cout << "Kalle Anka" << std::endl;
	}
}

void createTriangleData()
{
	float vertices[] = {

		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	// draw our first triangle
	glUseProgram(renderPass.getShaderProgramID());
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
	
}