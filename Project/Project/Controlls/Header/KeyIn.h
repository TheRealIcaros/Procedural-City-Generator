#ifndef KEYIN_H
#define KEYIN_H

#include <GLFW\glfw3.h>
#include "../../Logic\header/GenWindow.h"

//The struct to build up the delta time 
struct Time
{
	float deltaTime;
	float lastFrame;
	int frames;
	float duration;
	bool active;
};

class KeyIn
{
private:
	//Key input variables
	bool shouldRun;
	bool keyIsPressedF1;
	bool cameraCanMove;

	//Time variable
	Time time;

	void initiateVariables();
public:
	KeyIn();
	~KeyIn();

	void calculateDeltaTime();
	/*void keyInput(GLFWwindow* window, GenWindow* genWindow, Camera& camera, bool &shouldRun);*/
	void keyInput(GLFWwindow* window, GenWindow* genWindow, bool& shouldRun);	//Checks if any key was pressed 

};
#endif
