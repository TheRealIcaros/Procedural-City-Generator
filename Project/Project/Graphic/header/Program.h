#ifndef PROGRAM_H
#define PROGRAM_H

//General includes
#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <glm.hpp>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>


//Own made includes
//#include "Deferred.h"
#include "../../Controlls/Header/KeyIn.h"
#include "../../Singleton/GenWindow.h"


//Imgui stuff
#include "../../Imgui/imgui.h"
#include "../../Imgui/imgui_impl_glfw_gl3.h"

class Program
{
private:
	//Class objects
	GLFWwindow* window;
	GenWindow* genWindow;
	KeyIn* myKeyInput;
	//Deferred* deferred;

	//Initiation functions for the applications core functions
	void initiateGLFW();
	bool initiateWindow(GLFWwindow* window);
	void initiateImgui(GLFWwindow* window);
	void initiateVariables();

	//Mics variables
	bool keyIsPressedF1;
	bool shouldRun;

public:
	Program();
	~Program();

	bool Start();	//Initiates the program
	bool Run();		//The main-loop/ Returns false when we exit it 
	void Stop();	//Cleans upp the memory and returns everything

	void render();				//The render loop in the application
};

#endif
