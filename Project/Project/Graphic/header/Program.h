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
//#include "../header/Object.h"
#include "../../Controlls/Header/KeyIn.h"
#include "../../Singleton/GenWindow.h"
#include "shaderCreater.h"

class Program
{
private:
	GLFWwindow * window;
	GenWindow* genWindow;
	KeyIn* myKeyInput;
	shaderCreater renderPass;
	//Object myObjects;
	bool shouldRun;

	void initiateGLFW();
	bool initiateWindow(GLFWwindow* window);
	void initiateVariables();
	void initiateImgui(GLFWwindow* window);

	//Mics
	bool keyIsPressedF1;
	GLuint VAO;
	GLuint VBO;

public:
	Program();
	~Program();

	bool Start();	//Initiates the program
	bool Run();		//The main-loop/ Returns false when we exit it 
	void Stop();	//Cleans upp the memory and returns everything


	void createTriangle();
	void render();
};

#endif
