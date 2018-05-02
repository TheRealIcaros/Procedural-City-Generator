#ifndef MOUSE_H
#define MOUSE_H

#include <GLFW\glfw3.h>
#include "../../Defines.h"

class Mouse
{
private:
	// Pitch/Yaw Properties
	bool firstMouse;
	float lastX;
	float lastY;
	double xPos;
	double yPos;
public:
	Mouse(GLFWwindow* window);
	~Mouse();

	void moveMouse(GLFWwindow* window, float &xoffset, float &yoffset);

};


#endif
