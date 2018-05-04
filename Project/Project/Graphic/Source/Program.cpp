#include "../header/Program.h"
#include <Windows.h> //take away once done

void setColor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}

void Program::initiateGLFW()
{
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
	this->FOV = 0.45f * PI;

	//Values for mousemovements
	this->cameraOffsetX = 0.0f;
	this->cameraOffsetY = 0.0f;

	//Class object used by the Program class
	this->noise = new PerlinNoise();
	this->map = new HeightMap();
	this->district = new District();
	this->block = new Block();
	this->building = new Building();
	this->seed = new SeedConverter();
	this->genWindow = new GenWindow();
	//this->models = Model();

	this->myKeyInput = new KeyIn();
	this->camera = new Camera(window);
	//this->myObject = new Object();

	terrainMap.fill(0.0f);
}

void Program::initiateData()
{
	noiseGenerator(PERLIN_NOISE);
}

void Program::generate()
{
	cityMap.fill(7);
	terrainMap.fill(0);

	if (genWindow->getInputBuf().compare("") != 0)
	{
		seed->setSeed(genWindow->getInputBuf());
	}
	genWindow->setSeed(seed->getIntegerSeed());
	noise->setSeed(seed->getIntegerSeed());


	for (int i = 0; i < MAX_DISTRICTS; i++)
	{
		block->setBlockSize(i, genWindow->getBlockSize()[i]);
		building->setDensity(i, genWindow->getDensity()[i]/100.0f);
		building->setHeight(i, genWindow->getMinHeight()[i], genWindow->getMaxHeight()[i]);
	}

	map->generate(terrainMap, genWindow->getTSizeX(), genWindow->getTSizeY(), genWindow->getTerrainOctave(), genWindow->getTerrainOctavePerc(), genWindow->getRedistribution());

	cityMap = Array2D<int>(genWindow->getTSizeX(), genWindow->getTSizeY());

	district->generate(cityMap, genWindow->getPSizeX(), genWindow->getPSizeY(), genWindow->getBorderPerc());

	block->generate(cityMap, genWindow->getPSizeX(), genWindow->getPSizeY());

	building->generate(cityMap, terrainMap, genWindow->getPSizeX(), genWindow->getPSizeY());
	
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

	genWindow->setCounter(noise->getCounter());
	genWindow->setMainRoad(block->getMainRoad());
	genWindow->setSmallRoad(block->getSmallRoad());
	for (int i = 0; i < MAX_DISTRICTS; i++)
	{
		genWindow->setBuildings(i, building->getBuildings()[i]);
		genWindow->setGrass(i, building->getGrassTiles()[i]);
	}
}

void Program::noiseGenerator(int generator)
{
	if (generator == PERLIN_NOISE)
	{
		map->setNoise(noise);
		district->setNoise(noise);
		block->setNoise(noise);
		building->setNoise(noise);
	}
	else
	{
		//random
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

	initiateData();

	initiateImgui(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		returnValue = false;
	}
	
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetWindowSizeLimits(window, WIDTH, HEIGHT, WIDTH, HEIGHT);	//Sets the screen to a fixed size, that can't be changed by pulling the edges

	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	renderPass.createShader("./Graphic/Shaders/vertex", "NULL", "./Graphic/Shaders/fragment");

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
		camera->mouseMovement(window, cameraOffsetX, cameraOffsetY);

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
	delete this->map;
	delete this->district;
	delete this->block;
	delete this->building;
	delete this->seed;
	delete this->myKeyInput;
	delete this->genWindow;
	delete this->camera;
	//delete this->myObject;

	glfwTerminate();
}

void Program::render()
{
	//Cleans the color buffer and set the defaultbacgroundcolor
	glClearColor(0.3f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glUseProgram(renderPass.getShaderProgramID());

	glm::mat4 projection = glm::perspective(FOV, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera->getView();
	renderPass.setMat4("projection", projection);
	renderPass.setMat4("view", view);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));	  // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));			 // it's a bit too big for our scene, so scale it down
	renderPass.setMat4("model", model);

	//for (int i = 0; i < models.; i++)
	//Draws all the models in the application
	//models.Draw(renderPass);

	//ImGui that handles the graphical interface
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}

//// draw our first triangle
//Rendering the Deferred part
//deferred->render();
//glBindVertexArray(myObject->getVAO()); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//glBindVertexArray(models);
//glDrawArrays(GL_TRIANGLES, 0, 3);