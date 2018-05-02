#include "../Header/Mouse.h"

Mouse::Mouse(GLFWwindow* window)
{
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	this->firstMouse = true;
	this->lastX = WIDTH / 2.0f;
	this->lastY = HEIGHT / 2.0f;

	this->xPos = 0.0f;
	this->yPos = 0.0f;
}

Mouse::~Mouse()
{
}

void Mouse::moveMouse(GLFWwindow* window, float &xoffset, float &yoffset)
{
	glfwGetCursorPos(window, &xPos, &yPos);
	if (firstMouse)
	{
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	xoffset = xPos - lastX;
	yoffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;
	
}