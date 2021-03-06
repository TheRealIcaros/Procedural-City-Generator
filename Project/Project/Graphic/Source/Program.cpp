#include "../header/Program.h"
#include <Windows.h> //take away once done
#include <chrono>
#include <iostream>


void setColor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

void Program::initiateGLFW()
{
	glewExperimental = GL_TRUE;

	glfwInit();
	glShadeModel(GL_SMOOTH);
	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);	 //This sets the Major requierments of Opengl to Version 4.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//This sets the Minor requierments of Opengl to Version x.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	
}

bool Program::initiateWindow(GLFWwindow* window)
{
	bool returnValue = true;

	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		returnValue = false;
	}

	return returnValue;
}

void Program::initiateVariables()
{
	//Mics
	this->keyIsPressedF1 = false;
	this->shouldRun = true;

	//Values for mousemovements
	this->cameraOffsetY = 0.0f;
	this->cameraOffsetX = 0.0f;
	
	//Class object used by the Program class
	this->noise = new PerlinNoise();
	this->randNoise = new RandomNoise();
	this->map = new HeightMap();
	this->district = new District();
	this->block = new Block();
	this->building = new Building();
	this->seed = new SeedConverter();
	this->genWindow = new GenWindow();
	this->myKeyInput = new KeyIn();
	this->myRender =  new Render();
	this->myModels = new ModelLoader();
	
	//this->myTerrain = new Terrain();

	terrainMap.fill(0.0f);
}

void Program::loadAssets()
{
	this->houseBottomSection = myModels->loadModel("./Models/models/house_bot_section.model");
    this->houseMiddleSection = myModels->loadModel("./Models/models/house_mid_section.model");
    this->houseTopSection = myModels->loadModel("./Models/models/house_top_section.model");
    this->houseTopSection2 = myModels->loadModel("./Models/models/house_top_section2.model");
	
    //house textures
    this->houseBottomTexture = myModels->loadTexture("./Models/textures/concrete1.dds");
    this->houseBottomTexture2 = myModels->loadTexture("./Models/textures/concrete2.dds");
    this->houseBottomTexture3 = myModels->loadTexture("./Models/textures/concrete3.dds");
    this->houseMiddleTexture = myModels->loadTexture("./Models/textures/bricks1.dds");
    this->houseMiddleTexture2 = myModels->loadTexture("./Models/textures/bricks2.dds");
    this->houseMiddleTexture3 = myModels->loadTexture("./Models/textures/bricks3.dds");
    this->houseTopTexture = myModels->loadTexture("./Models/textures/roof1.dds");
    this->houseTopTexture2 = myModels->loadTexture("./Models/textures/roof2.dds");

	//skyscraper sections
    this->skyBottomSection = myModels->loadModel("./Models/models/skyscraper_bot_section.model");
    this->skyMiddleSection = myModels->loadModel("./Models/models/skyscraper_mid_section.model");
    this->skyTopSection = myModels->loadModel("./Models/models/skyscraper_top_section.model");
	
    //skyscraper textures
    this->skyBottomTexture = houseBottomTexture;
    this->skyBottomTexture2 = houseBottomTexture2;
    this->skyBottomTexture3 = houseBottomTexture3;
    this->skyMiddleTexture = myModels->loadTexture("./Models/textures/skyscraper1.dds");
    this->skyMiddleTexture2 = myModels->loadTexture("./Models/textures/skyscraper2.dds");
    this->skyMiddleTexture3 = myModels->loadTexture("./Models/textures/skyscraper3.dds");
    this->skyMiddleTexture4 = myModels->loadTexture("./Models/textures/skyscraper4.dds");
    this->skyMiddleTexture5 = myModels->loadTexture("./Models/textures/skyscraper5.dds");
    this->skyTopTexture = houseBottomTexture;
    this->skyTopTexture2 = houseBottomTexture2;
    this->skyTopTexture3 = houseBottomTexture3;
	
    //factory sections
    this->factoryBottomSection = houseBottomSection;
    this->factoryMiddleSection = houseMiddleSection;
    this->factoryTopSection = skyTopSection;
	
    this->factoryBottomTexture = houseBottomTexture;
    this->factoryMiddleTexture = myModels->loadTexture("./Models/textures/bricks_large1.dds");
    this->factoryMiddleTexture2 = myModels->loadTexture("./Models/textures/bricks_large2.dds");
    this->factoryTopTexture = houseBottomTexture2;

	//Grass and road sections
	this->roadModel = myModels->loadModel("./Models/models/house_bot_section.model");
	this->verticalRoadTexture = myModels->loadTexture("./Models/textures/road_vertical.dds");
	//this->verticalRoadTexture = myModels->loadTexture("./Models/textures/g.dds");
	//this->horizontalRoadTexture = myModels->loadTexture("./Models/textures/g.dds");
	this->horizontalRoadTexture = myModels->loadTexture("./Models/textures/road_horizontal.dds");
	//this->grassTexture = myModels->loadTexture("./Models/textures/grass1.dds");
	this->grassTexture = myModels->loadTexture("./Models/textures/g.dds");
}

void Program::loadSection(int district, const Section& section, int type)
{
	building->addSection(district, section, type);
}

void Program::addSection()
{
	building->addSection(0, { houseBottomSection, houseBottomTexture }, SECTION_BOTTOM);
	building->addSection(0, { houseBottomSection, houseBottomTexture2 }, SECTION_BOTTOM);
	building->addSection(0, { houseBottomSection, houseBottomTexture3 }, SECTION_BOTTOM);

	// add some house middle sections
	building->addSection(0, { houseMiddleSection, houseMiddleTexture }, SECTION_MIDDLE);
	building->addSection(0, { houseMiddleSection, houseMiddleTexture2 }, SECTION_MIDDLE);
	building->addSection(0, { houseMiddleSection, houseMiddleTexture3 }, SECTION_MIDDLE);

	// add some house top sections
	building->addSection(0, { houseTopSection, houseTopTexture }, SECTION_TOP);
	building->addSection(0, { houseTopSection, houseTopTexture2 }, SECTION_TOP);
	building->addSection(0, { houseTopSection2, houseTopTexture }, SECTION_TOP);
	building->addSection(0, { houseTopSection2, houseTopTexture2 }, SECTION_TOP);

	// add some skyscraper bottom sections
	building->addSection(1, { skyBottomSection, skyBottomTexture }, SECTION_BOTTOM);
	building->addSection(1, { skyBottomSection, skyBottomTexture2 }, SECTION_BOTTOM);
	building->addSection(1, { skyBottomSection, skyBottomTexture3 }, SECTION_BOTTOM);

	// add some skyscraper middle sections
	building->addSection(1, { skyMiddleSection, skyMiddleTexture }, SECTION_MIDDLE);
	building->addSection(1, { skyMiddleSection, skyMiddleTexture2 }, SECTION_MIDDLE);
	building->addSection(1, { skyMiddleSection, skyMiddleTexture3 }, SECTION_MIDDLE);
	building->addSection(1, { skyMiddleSection, skyMiddleTexture4 }, SECTION_MIDDLE);
	building->addSection(1, { skyMiddleSection, skyMiddleTexture5 }, SECTION_MIDDLE);

	// add some skyscraper top sections
	building->addSection(1, { skyTopSection, skyTopTexture }, SECTION_TOP);
	building->addSection(1, { skyTopSection, skyTopTexture2 }, SECTION_TOP);
	building->addSection(1, { skyTopSection, skyTopTexture3 }, SECTION_TOP);


	// add some factory bottom sections
	building->addSection(2, { factoryBottomSection, factoryBottomTexture }, SECTION_BOTTOM);

	// add some factory middle sections
	building->addSection(2, { factoryMiddleSection, factoryMiddleTexture }, SECTION_MIDDLE);
	building->addSection(2, { factoryMiddleSection, factoryMiddleTexture2 }, SECTION_MIDDLE);

	// add some factory top sections
	building->addSection(2, { factoryTopSection, factoryTopTexture }, SECTION_TOP);
}

void Program::generate()
{
	structure.clear();
	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
	cityMap.fill(7);
	terrainMap.fill(0);
	cityMap = Array2D<int>(genWindow->getTSizeX(), genWindow->getTSizeY());

	if (genWindow->getInputBuf().compare("") != 0)
	{
		seed->setSeed(genWindow->getInputBuf());
	}
	else
	{
		seed->setSeed("BLARGH");
	}
	noiseGenerator(seed->getSeed());

	district->setBorderPerc(genWindow->getBorderPerc());
	block->setminRoadDistance(genWindow->getMinMainRoadDist());
	for (int i = 0; i < MAX_DISTRICTS; i++)
	{
		block->setBlockSize(i, genWindow->getBlockSize()[i]);
		building->setDensity(i, genWindow->getDensity()[i]);
		building->setHeight(i, genWindow->getMinHeight()[i], genWindow->getMaxHeight()[i]);
	}

	map->generate(terrainMap, genWindow->getTSizeX(), genWindow->getTSizeY(), genWindow->getTerrainOctave(), genWindow->getTerrainOctavePerc(), genWindow->getRedistribution());

	if (genWindow->getRandDistrict())
	{
		district->randGenerate(cityMap, genWindow->getPSizeX(), genWindow->getPSizeY());
	}
	else
	{
		district->generate(cityMap, genWindow->getPSizeX(), genWindow->getPSizeY());
	}

	block->generate(cityMap, genWindow->getPSizeX(), genWindow->getPSizeY());

	if (genWindow->getRandBuild())
	{
		building->fullRandom(cityMap, terrainMap, structure);
	}
	else
	{
		building->generate(cityMap, terrainMap, structure, genWindow->getPSizeX(), genWindow->getPSizeY());
	}

	//Creates the height-map to be used in the terrain
	ppm image(terrainMap.getWidth(), terrainMap.getHeight());

	for (int kk = 0; kk < terrainMap.getWidth() * terrainMap.getHeight(); kk++)
	{
		float n = terrainMap[kk];
		image.r[kk] = floor(255 * n);
		image.g[kk] = floor(255 * n);
		image.b[kk] = floor(255 * n);
	}
	//The height-map in .bmp format
	image.write("HeightMapA.bmp");

	////Add structures render
	myRender->begin();

	
	//Add in the terrain to the render pipeline
	addTerrainToRender();

	//Add in the buildings to the render pipeline
	addBuildingToRender();

	//For adding info to the left-side of the app window
	std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
	genWindow->setGenTime(std::chrono::duration<float>(end - start).count());
	genWindow->setCounter(noise->getCounter());
	genWindow->setMainRoad(block->getMainRoad());
	genWindow->setSmallRoad(block->getSmallRoad());
	genWindow->setSeed(seed->getSeed());

	//For adding info to the left-side of the app window
	for (int i = 0; i < MAX_DISTRICTS; i++)
	{
		genWindow->setBuildings(i, building->getBuildings()[i]);
		genWindow->setGrass(i, building->getGrassTiles()[i]);
	}

	////End renderer
	myRender->end();
	
	//This is for testing the layout of the City-map-layout
	/*system("CLS");
	for (int j = 0; j < genWindow->getTSizeY(); j++)
	{
		for (int i = 0; i < genWindow->getTSizeX(); i++)
		{
			if (cityMap.at(i, j) == 0)
			{
				setColor(11);
			}
			else if (cityMap.at(i, j) == 1)
			{
				setColor(14);
			}
			else if (cityMap.at(i, j) == 2)
			{
				setColor(4);
			}
			else if (cityMap.at(i, j) == 7)
			{
				setColor(2);
			}
			else if (cityMap.at(i, j) == 8)
			{
				setColor(13);
			}
			else if (cityMap.at(i, j) == 9)
			{
				setColor(5);
			}
			std::cout << cityMap.at(i, j);
			if (i == genWindow->getTSizeY() - 1)
			{
				std::cout << "\n";
			}
		}
	}*/
}

void Program::noiseGenerator(unsigned int seed)
{
	if (!genWindow->getRandom())
	{
		if (genWindow->getRandDistrict() || genWindow->getRandBuild())
		{
			randNoise->setSeed(seed);
		}
		noise->setSeed(seed);

		map->setNoise(noise);

		if (genWindow->getRandDistrict())
		{
			district->setNoise(randNoise);
		}
		else
		{
			district->setNoise(noise);
		}
		block->setNoise(noise);

		if (genWindow->getRandBuild())
		{
			building->setNoise(randNoise);
		}
		else
		{
			building->setNoise(noise);
		}
	}
	else
	{
		randNoise->setSeed(seed);
		noise->setSeed(seed);
		map->setNoise(noise);
		district->setNoise(randNoise);
		block->setNoise(randNoise);
		building->setNoise(randNoise);
	}
}

void Program::initiateImgui(GLFWwindow* window)
{
	//Setup Imgui
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;

	ImGui_ImplGlfwGL3_Init(window, true);

	//Setup style
	ImGui::StyleColorsDark();
}

void Program::addTerrainToRender()
{
	/*delete this->myTerrain;
	this->myTerrain = new Terrain(glm::vec3(0.0, 0.0, 0.0), terrainMap, grassTexture);*/
	
}

void Program::addBuildingToRender()
{
	int curStructure = 0;
	int texture = 0;
	for (int x = 0; x < genWindow->getTSizeX(); x++)
	{
		for (int y = 0; y < genWindow->getTSizeY(); y++)
		{
			float terrain0 = terrainMap.at(x, y);
			float terrain1 = terrainMap.at(x + 1, y);
			float terrain2 = terrainMap.at(x, y + 1);
			float terrain3 = terrainMap.at(x + 1, y + 1);

			float finalTerrain = ((terrain0 + terrain1 + terrain2 + terrain3) / 4) * 23;

			int cellValue = cityMap.at(x, y);
			if (0 <= cellValue && cellValue < 7)
			{
				const int NUM_STRUCTURES = structure.getSize();
				Structure& s = structure[curStructure];
				curStructure++;

				
				//glm::vec3 position(x * 2, 0.175f, y * 2);
				glm::vec3 position(x * 2, finalTerrain, y * 2);

				// render bottom section
				myRender->addElement(s.bottom.model, s.bottom.texture, position);
				position.y += 0.175f;

				// render middle sections
				for (int i = 0; i < s.height; i++)
				{
					myRender->addElement(s.middle.model , s.middle.texture, position);
					position.y += 2.0f;
				}

				// render top section
				myRender->addElement(s.top.model, s.top.texture, position);
			}
			else
			{
				float terrain0 = terrainMap.at(x, y);
				float terrain1 = terrainMap.at(x + 1, y);
				float terrain2 = terrainMap.at(x, y + 1);
				float terrain3 = terrainMap.at(x + 1, y + 1);

				float finalTerrain = ((terrain0 + terrain1 + terrain2 + terrain3) / 4) * 23;
				//
				////Make new renderreu piplineeruuu tto thus'eru
				
				if (cellValue == 8)
				{
					texture = horizontalRoadTexture;
					myRender->addElement(roadModel, texture, glm::vec3(x * 2, finalTerrain, y * 2));

				}
				else if(cellValue == 9)
				{
					texture = verticalRoadTexture;
					myRender->addElement(roadModel, texture, glm::vec3(x * 2, finalTerrain, y * 2));

				}
				else if (cellValue == 7)
				{
					//texture = grassTexture;
					//myRender->addElement(roadModel, texture, glm::vec3(x * 2, finalTerrain, y * 2));
				}
				
				//myRender->addElement(roadModel, texture, glm::vec3(x * 2, 0, y * 2));	
			}
		}

	}
}

void Program::collectData()
{
	Array<float> data;
	float avg = 0;
	int counter = 0;
	int buildings = 0;
	srand(static_cast <unsigned> (time(0)));
	for (int i = 0; i < 100; i++)
	{
		genWindow->randomiser();
		generate(); 
		float time = genWindow->getGenTime();
		data.add(time);
		avg += time;
		counter += genWindow->getCounter();
		buildings += genWindow->getTotalBuildings();
	}
	avg /= 100;
	counter /= 100;
	buildings /= 100;
	float deviation = 0;
	for (int i = 0; i < 100; i++)
	{
		deviation += pow(data.at(i) - avg, 2);
	}
	deviation /= 100;
	deviation = sqrt(deviation);
	toFile(avg, deviation, counter, buildings);
}

void Program::toFile(float avg, float deviation, int counter, int buildings)
{
	std::ofstream myfile;
	myfile.open(std::to_string(genWindow->getTSizeX()) + "X" + std::to_string(genWindow->getTSizeY()) + ".txt");
	myfile << "Generation time: " << std::to_string(avg) << ", Standard deviation: " << std::to_string(deviation) << ", Perlin noise calls: " << std::to_string(counter) <<
		", Buildings: " << std::to_string(buildings);
	myfile.close();
}

Program::Program()
{
	initiateGLFW();
}

Program::~Program()
{

}

bool Program::Start()
{
	bool returnValue = true;

	//Creates the window for the application
	this->window = glfwCreateWindow(WIDTH, HEIGHT, "Prelin Noise City", NULL, NULL);
	if (initiateWindow(this->window) == false)
		returnValue = false;

	glfwMakeContextCurrent(window);

	//Initiates variables that Program.h needs
	initiateVariables();

	initiateImgui(window);

	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetWindowSizeLimits(window, WIDTH, HEIGHT, WIDTH, HEIGHT);	//Sets the screen to a fixed size, that can't be changed by pulling the edges

	//Rendering parameters
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	//Initiation of glew
	glewInit();

	//This loads in all textures needed for the application
	loadAssets();
	
	//This adds the sections to the applications
	addSection();

	//Startup the renderer
	myRender->load(window);

	//this->deferredRender = new Deferred(myRender->getCamera());

	return returnValue;
}

bool Program::Run()
{
	ImGui_ImplGlfwGL3_NewFrame();
	
	myKeyInput->calculateDeltaTime();

	myKeyInput->keyInput(window, genWindow, shouldRun, myRender->getCamera());		//Checks if any key was pressed 


	if(myKeyInput->getCameraShouldMove() == true)
		myRender->getCamera()->mouseMovement(window, cameraOffsetX, cameraOffsetY);


	genWindow->draw();										//Draw function for ImGui

	if (genWindow->getGenerate() == true)
	{
		if (genWindow->getPerformance())
		{
			collectData();
		}
		else
		{
			generate();
		}
		genWindow->toggleGenerate();
	}

	render();												//The render loop for all the graphics

	glfwSwapBuffers(window);
	glfwPollEvents();

	return shouldRun;
}

void Program::Stop()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	//Delete all pointers when we close the application
	delete this->noise;
	delete this->randNoise;
	delete this->map;
	delete this->district;
	delete this->block;
	delete this->building;
	delete this->seed;
	delete this->myKeyInput;
	delete this->genWindow;
	myRender->getCamera()->deleteMouse();
	delete this->myRender;
	delete this->myModels;
	//delete this->deferredRender;
	//this->myTerrain->deallocate();
	//delete this->myTerrain;

	glfwTerminate();
}

void Program::render()
{
	//Cleans the color buffer and set the defaultbacgroundcolor
	glClearColor(0.3f, 0.3f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	//Deferred render
	//deferredRender->render(myRender->getCamera(), myTerrain);

	//Calls the reneder-pipeline for models and terrain
	myRender->render(myModels);

	//Render terrain
	//myRender->render(grassTexture, myTerrain);
	//myTerrain->Draw(terrainShader, grassTexture);

	//ImGui that handles the graphical interface//
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

//https://stackoverflow.com/questions/18557176/is-there-a-good-tutorial-on-terrain-editor
//https://www.youtube.com/watch?v=oaAN4zSkY24