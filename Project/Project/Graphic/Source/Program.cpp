#include "../header/Program.h"
#include <Windows.h> //take away once done
#include <chrono>

void setColor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

void Program::initiateGLFW()
{
	glewExperimental = GL_TRUE;


	glfwInit();	
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);	 //This sets the Major requierments of Opengl to Version 4.x
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//This sets the Minor requierments of Opengl to Version x.3
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
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
	//this->FOV = 0.45f * PI;

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
	//this->camera = new Camera(window);
	//this->myObject = new Object();

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
	this->horizontalRoadTexture = myModels->loadTexture("./Models/textures/road_horizontal.dds");
	this->grassTexture = myModels->loadTexture("./Models/textures/grass1.dds");
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

	for (int i = 0; i < MAX_DISTRICTS; i++)
	{
		block->setBlockSize(i, genWindow->getBlockSize()[i]);
		building->setDensity(i, genWindow->getDensity()[i]);
		building->setHeight(i, genWindow->getMinHeight()[i], genWindow->getMaxHeight()[i]);
	}

	map->generate(terrainMap, genWindow->getTSizeX(), genWindow->getTSizeY(), genWindow->getTerrainOctave(), genWindow->getTerrainOctavePerc(), genWindow->getRedistribution());

	district->generate(cityMap, genWindow->getPSizeX(), genWindow->getPSizeY(), genWindow->getBorderPerc());

	block->generate(cityMap, genWindow->getPSizeX(), genWindow->getPSizeY());

	building->generate(cityMap, terrainMap, structure, genWindow->getPSizeX(), genWindow->getPSizeY());

	//Add structures render
	myRender->begin();

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

	//End renderer
	myRender->end();

	system("CLS");
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
	}
}

void Program::noiseGenerator(unsigned int seed)
{
	if (!genWindow->getRandom())
	{
		noise->setSeed(seed);
		map->setNoise(noise);
		district->setNoise(noise);
		block->setNoise(noise);
		building->setNoise(noise);
	}
	else
	{
		randNoise->setSeed(seed);
		map->setNoise(randNoise);
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

void Program::addBuildingToRender()
{
	int curStructure = 0;
	for (int x = 0; x < genWindow->getTSizeX(); x++)
	{
		for (int y = 0; y < genWindow->getTSizeY(); y++)
		{
			int cellValue = cityMap.at(x, y);
			if (0 <= cellValue && cellValue < 7)
			{
				const int NUM_STRUCTURES = structure.getSize();
				Structure& s = structure[curStructure];
				curStructure++;

				glm::vec3 position(x * 2, 0.175f, y * 2);

				// render bottom section
				myRender->addElement(s.bottom.model, s.bottom.texture, position);
				position.y += 0.175f;

				// render middle sections
				for (int i = 0; i < s.height; i++)
				{
					myRender->addElement(s.middle.model, s.middle.texture, position);
					position.y += 2.0f;
				}

				// render top section
				myRender->addElement(s.top.model, s.top.texture, position);
			}
			else
			{
				int texture = verticalRoadTexture;
				if (cellValue == 8)
				{
					texture = horizontalRoadTexture;
				}
				else if (cellValue == 7)
				{
					texture = grassTexture;
				}

				myRender->addElement(roadModel, texture, glm::vec3(x * 2, 0, y * 2));	
			}
		}

	}
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

	this->window = glfwCreateWindow(WIDTH, HEIGHT, "Prelin Noise City", NULL, NULL);
	if (initiateWindow(this->window) == false)
		returnValue = false;

	glfwMakeContextCurrent(window);

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

	//std::string const path = "./Models/Box/Box.obj";
	//models.push_back(path);
	//models.loadModel(path, glm::vec3(0.0f, 0.0f, -2.0f));
	//deferred->initiateDeferred();

	return returnValue;
}

bool Program::Run()
{
	ImGui_ImplGlfwGL3_NewFrame();
	
	myKeyInput->keyInput(window, genWindow, shouldRun);		//Checks if any key was pressed 

	if(myKeyInput->getCameraShouldMove() == true)
		myRender->getCamera()->mouseMovement(window, cameraOffsetX, cameraOffsetY);
		//camera->mouseMovement(window, cameraOffsetX, cameraOffsetY);

	genWindow->draw();										//Draw function for ImGui

	if (genWindow->getGenerate() == true)
	{
		generate();
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

	delete this->noise;
	delete this->randNoise;
	delete this->map;
	delete this->district;
	delete this->block;
	delete this->building;
	delete this->seed;
	delete this->myKeyInput;
	delete this->genWindow;
	delete this->myRender;
	delete this->myModels;
	//delete this->camera;
	//delete this->myObject;

	glfwTerminate();
}

void Program::render()
{
	//glUseProgram(myRender->getObjectShader());

	myRender->render(myModels);

	//ImGui that handles the graphical interface//
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}






//glm::mat4 projection = glm::perspective(FOV, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
//glm::mat4 view = camera->getView();
//renderPass.setMat4("projection", projection);
//renderPass.setMat4("view", view);
//
//glm::mat4 model;
//model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));	  // translate it down so it's at the center of the scene
//model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));			 // it's a bit too big for our scene, so scale it down
//renderPass.setMat4("model", model);
//
//for (int i = 0; i < models.; i++)
////Draws all the models in the application
//models.Draw(renderPass);
//
//// draw our first triangle
//Rendering the Deferred part
//deferred->render();
//glBindVertexArray(myObject->getVAO()); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//glBindVertexArray(models);
//glDrawArrays(GL_TRIANGLES, 0, 3);