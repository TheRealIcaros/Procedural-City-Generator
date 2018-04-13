#ifndef KEYIN_H
#define KEYIN_H

#include <GLFW\glfw3.h>

#include "../../Singleton/GenWindow.h"
class KeyIn
{
private:
	bool shouldRun;
	bool keyIsPressedF1;

	void initiateVariables();
public:
	KeyIn();
	~KeyIn();

	void keyInput(GLFWwindow* window, GenWindow* genWindow, bool &shouldRun);
};
#endif
