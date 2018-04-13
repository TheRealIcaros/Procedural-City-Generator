#ifndef PROGRAM_H
#define PROGRAM_H

//General includes
#include <glad/glad.h>
#include <fstream>
#include <string>

//Imgui stuff
#include "../../Imgui/imgui.h"
#include "../../Imgui/imgui_impl_glfw_gl3.h"

//Own made includes
#include "../../Defines.h"
#include "../../Graphic\header\shaderCreater.h"
#include "../../Controlls/Header/KeyIn.h"
#include "../../Singleton/GenWindow.h"

class Program
{
private:
	GLFWwindow * window;
	GenWindow* genWindow;
	KeyIn* myKeyInput;
	bool shouldRun;

	void initiateGLFW();
	bool initiateWindow(GLFWwindow* window);
	void initiateVariables();
	void initiateImgui(GLFWwindow* window);

	//Mics
	bool keyIsPressedF1;

public:
	Program();
	~Program();

	bool Start();	//Initiates the program
	bool Run();		//The main-loop/ Returns false when we exit it 
	void Stop();	//Cleans upp the memory and returns everything

	void render();
};

#endif
