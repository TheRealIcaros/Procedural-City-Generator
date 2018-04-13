#ifndef PROGRAM_H
#define PROGRAM_H

#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <fstream>
#include <string>
#include "../../Imgui\imgui.h"

#include "../../Defines.h"

#include "../../Graphic\header\shaderCreater.h"

class Program
{
private:
	GLFWwindow * window;
	bool shouldRun;

	void initiateGLFW();
	bool initiateWindow(GLFWwindow* window);
	void initiateVariables();

	//Mics
	bool keyIsPressedF1;

public:
	Program();
	~Program();

	bool Start();	//Initiates the program
	bool Run();		//The main-loop/ Returns false when we exit it 
	void Stop();	//Cleans upp the memory and returns everything
	void keyInput(GLFWwindow *window);
};

#endif
