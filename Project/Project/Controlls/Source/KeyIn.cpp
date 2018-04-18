#include "../Header/KeyIn.h"

void KeyIn::initiateVariables()
{
	this->keyIsPressedF1 = false; //The button isn't pressed from the start 
}

KeyIn::KeyIn()
{
	initiateVariables();
}

KeyIn::~KeyIn()
{
}

void KeyIn::keyInput(GLFWwindow* window, GenWindow* genWindow, bool &shouldRun)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		shouldRun = false;
	}

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