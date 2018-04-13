#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Imgui/imgui.h"
#include "Imgui/imgui_impl_glfw_gl3.h"
#include "Singleton\GenWindow.h"

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
void createShaders();
void createTriangleData();
void render();

//IMGUI stuffs
GenWindow* genWindow = GenWindow::getInstance();
bool keyIsPressedF1 = false;

//shader values
unsigned int vertexShader;
unsigned int fragmentShader;
unsigned int shaderProgram;

//Global values
unsigned int VBO;
GLuint gVertexAttribute = 0;
GLuint gShaderProgram = 0;

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
	initiateGLFW();
	
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);


	if (startSequence(window) == false)
	{
		glfwTerminate();
		return -1;
	}

	createShaders();

	createTriangleData();

	while (!glfwWindowShouldClose(window))
	{
		ImGui_ImplGlfwGL3_NewFrame();

		//inputs from the keyboard
		keyInput(window);

		genWindow->draw();

		//rendering happens here...
		render();
		
		//Checks the call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}

void initiateGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
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

	// Setup ImGui binding
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplGlfwGL3_Init(window, true);

	// Setup style
	ImGui::StyleColorsDark();

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
		genWindow->toggleDebugToDraw();
	}
	else if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_RELEASE && keyIsPressedF1 == true)
	{
		keyIsPressedF1 = false;
	}
}

void createShaders()
{
	
}

void createTriangleData()
{
	float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}