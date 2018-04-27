#ifndef KEYIN_H
#define KEYIN_H

#include <GLFW\glfw3.h>

#include "../../Singleton/GenWindow.h"
#include "../../Graphic/header/Camera.h"

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
	bool shouldRun;
	bool keyIsPressedF1;
	bool cameraCanMove;

	Time time;


	void initiateVariables();
public:
	KeyIn();
	~KeyIn();

	void calculateDeltaTime();
	void keyInput(GLFWwindow* window, GenWindow* genWindow, Camera* camera, bool &shouldRun);
};
#endif
