#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>

//Defines
#include "Defines.h"

void initiateGLFW();
void resizeWindow(GLFWwindow* window, int width, int height);
bool initiateWindow(GLFWwindow* window);
bool startSequence(GLFWwindow* window);
void keyInput(GLFWwindow* window);
void render();

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
}

void render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT);
}