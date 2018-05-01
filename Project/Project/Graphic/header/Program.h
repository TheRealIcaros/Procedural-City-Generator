#ifndef PROGRAM_H
#define PROGRAM_H

//Own made includes
#include "Model.h"
//#include "Deferred.h"
#include "Camera.h"
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
	Camera* camera;
	//Model myModel;
	
	shaderCreater renderPass;
	std::vector<Model> models;
	//Deferred* deferred;

	//Initiation functions for the applications core functions
	void initiateGLFW();
	bool initiateWindow(GLFWwindow* window);
	void initiateImgui(GLFWwindow* window);
	void initiateVariables();

	//Mics variables
	bool keyIsPressedF1;
	bool shouldRun;
	float FOV;


public:
	Program();
	~Program();

	bool Start();				//Initiates the program
	bool Run();					//The main-loop/ Returns false when we exit it 
	void Stop();				//Cleans upp the memory and returns everything

	void render();				//The render loop in the application
};

#endif
