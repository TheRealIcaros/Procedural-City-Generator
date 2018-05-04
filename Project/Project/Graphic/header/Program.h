#ifndef PROGRAM_H
#define PROGRAM_H

//Own made includes
#include "Model.h"
#include "Camera.h"
#include "../../Controlls/Header/KeyIn.h"
#include "../../Logic/header/GenWindow.h"
//#include "Deferred.h"

//Imgui stuff
#include "../../Imgui/imgui.h"
#include "../../Imgui/imgui_impl_glfw_gl3.h"

//MISC STUFF
#include "../../Logic/header/PerlinNoise.h"
#include "../../Logic/header/RandomNoise.h"
#include "../../Logic/header/SeedConverter.h"
#include "../../Logic/header/HeightMap.h"
#include "../../Logic/header/District.h"
#include "../../Logic/header/Block.h"
#include "../../Logic/header/Building.h"
#include <math.h>

enum
{
	PERLIN_NOISE = 0,
	RANDOM_NOISE
};

class Program
{
private:
	//Class objects
	PerlinNoise * noise;
	RandomNoise * randNoise;
	HeightMap * map;
	District * district;
	Block * block;
	Building * building;
	SeedConverter* seed;
	GLFWwindow* window;
	GenWindow* genWindow;
	KeyIn* myKeyInput;
	Camera* camera;
	//Model myModel;
	
	shaderCreater renderPass;
	Model models;
	//std::vector<Model> models;
	//Deferred* deferred;

	//Initiation functions for the applications core functions
	void initiateGLFW();
	bool initiateWindow(GLFWwindow* window);
	void initiateImgui(GLFWwindow* window);
	void initiateVariables();
	//static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	void generate();
	void noiseGenerator(unsigned int seed);

	//Mics variables
	bool keyIsPressedF1;
	bool shouldRun;
	float FOV;
	float cameraOffsetX;
	float cameraOffsetY;


	Array2D<float> terrainMap;
	Array2D<int> cityMap;
	Array<Structure> structure;

public:
	Program();
	~Program();

	bool Start();				//Initiates the program
	bool Run();					//The main-loop/ Returns false when we exit it 
	void Stop();				//Cleans upp the memory and returns everything

	void render();				//The render loop in the application
};

#endif
