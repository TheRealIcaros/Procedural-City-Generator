#ifndef PROGRAM_H
#define PROGRAM_H

//Own made includes
#include "Render.h"
#include "../../Logic/header/GenWindow.h"

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
	PerlinNoise* noise;
	RandomNoise* randNoise;
	HeightMap* map;
	District* district;
	Block* block;
	Building* building;
	SeedConverter* seed;
	GLFWwindow* window;
	GenWindow* genWindow;
	KeyIn* myKeyInput;
	Render* myRender;
	ModelLoader* myModels;

	//Initiation functions for the applications core functions
	void initiateGLFW();
	bool initiateWindow(GLFWwindow* window);
	void initiateImgui(GLFWwindow* window);
	void initiateVariables();
	void loadAssets();
	void loadSection(int district, const Section& section, int type);
	void addSection();

	void generate();
	void noiseGenerator(unsigned int seed);
	void addBuildingToRender();

	void render();				//The render loop in the application

	//Mics variables
	bool keyIsPressedF1;
	bool shouldRun;
	float cameraOffsetX;
	float cameraOffsetY;

	////Models and texture load-variables
	int houseMiddleSection; 
	int houseBottomSection; 
	int houseTopSection; 
	int houseTopSection2;

	// house textures
	int houseBottomTexture; 
	int houseBottomTexture2;
	int houseBottomTexture3;
	int houseMiddleTexture; 
	int houseMiddleTexture2;
	int houseMiddleTexture3;
	int houseTopTexture; 
	int houseTopTexture2;

	// skyscraper sections
	int skyBottomSection;
	int skyMiddleSection;
	int skyTopSection;  

	// skyscraper textures
	int skyBottomTexture; 
	int skyBottomTexture2;
	int skyBottomTexture3;
	int skyMiddleTexture; 
	int skyMiddleTexture2;
	int skyMiddleTexture3;
	int skyMiddleTexture4;
	int skyMiddleTexture5;
	int skyTopTexture; 
	int skyTopTexture2; 
	int skyTopTexture3; 

	// factory sections
	int factoryBottomSection;
	int factoryMiddleSection;
	int factoryTopSection;
	int factoryBottomTexture;
	int factoryMiddleTexture;
	int factoryMiddleTexture2;
	int factoryTopTexture;

	//Grass and road-tiles
	int roadModel;
	int verticalRoadTexture;
	int horizontalRoadTexture;
	int grassTexture;

	//Arrays for Models
	Array2D<float> terrainMap;
	Array2D<int> cityMap;
	Array<Structure> structure;

public:
	Program();
	~Program();

	bool Start();				//Initiates the program
	bool Run();					//The main-loop/ Returns false when we exit it 
	void Stop();				//Cleans upp the memory and returns everything

};

#endif
