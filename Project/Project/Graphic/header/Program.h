#ifndef PROGRAM_H
#define PROGRAM_H

//Own made includes
#include "shaderCreater.h"
#include "../../Defines.h"

//General includes
//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>


//#include "../../Controlls/Header/KeyIn.h"
//#include "../../Singleton/GenWindow.h"

//Imgui stuff
//#include "../../Imgui/imgui.h"
//#include "../../Imgui/imgui_impl_glfw_gl3.h"

class Program
{
private:
	GLFWwindow* window;
	//GenWindow* genWindow;
	//KeyIn* myKeyInput;
	//Object myObjects;
	bool shouldRun;

	void initiateGLFW();
	bool initiateWindow(GLFWwindow* window);
	void initiateVariables();

	//Mics
	bool keyIsPressedF1;	
	shaderCreater renderPass;
	GLuint VAO;
	GLuint VBO;
	GLuint programID;

public:
	Program();
	~Program();

	bool Start();	//Initiates the program
	bool Run();		//The main-loop/ Returns false when we exit it 
	void Stop();	//Cleans upp the memory and returns everything

	void createTriangle();
	void render();				//The render loop in the application
};

#endif
