#include "../header/Program.h"

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

	this->cameraOffsetX = 0.0f;
	this->cameraOffsetY = 0.0f;

	this->noise = new PerlinNoise();
	this->map = new HeightMap();
	this->seed = new SeedConverter();
	this->genWindow = new GenWindow();
	////Pitch/Yaw properties
	//firstMouse = true;
	//lastX = WIDTH / 2.0f;
	//lastY = HEIGHT / 2.0f;

	this->myKeyInput = new KeyIn();
	this->camera = new Camera();
	/*this->dataManager = new DataManager();*/
	//this->myObject = new Object();

	terrainMap.fill(0.0f);
}

void Program::initiateData()
{
	/*dataManager->addDataHolder(map);*/

	noiseGenerator(PERLIN_NOISE);
}

//void mouse_callback(GLFWwindow* window, double xpos, double ypos)
//{
//	if (firstMouse)
//	{
//		lastX = xpos;
//		lastY = ypos;
//		firstMouse = false;
//	}
//
//	float xoffset = xpos - lastX;
//	float yoffset = lastY - ypos; //Reversed since y-coordinates go from bottom to top
//	lastX = xpos;
//	lastY = ypos;
//
//	camera->mouseMovement(xoffset, yoffset);
//}


void Program::generate()
{
	if (genWindow->getInputBuf().compare("") != 0)
	{
		seed->setSeed(genWindow->getInputBuf());
	}
	/*dataManager->addData("Seed", seed->getIntegerSeed());*/
	genWindow->setSeed(seed->getIntegerSeed());
	noise->setSeed(seed->getIntegerSeed());

	map->generate(terrainMap, genWindow->getTSizeX(), genWindow->getTSizeY(), genWindow->getTerrainOctave1(),
		genWindow->getTerrainOctave2(), genWindow->getTerrainOctave3(), genWindow->getTerrainOctave4(), genWindow->getTerrainOctave5(), genWindow->getTerrainOctave6(),
		genWindow->getTerrainOctave7(), genWindow->getTerrainOctave8(), genWindow->getTerrainOctavePerc1(), genWindow->getTerrainOctavePerc2(), genWindow->getTerrainOctavePerc3(),
		genWindow->getTerrainOctavePerc4(), genWindow->getTerrainOctavePerc5(), genWindow->getTerrainOctavePerc6(), genWindow->getTerrainOctavePerc7(), genWindow->getTerrainOctavePerc8(),
		genWindow->getRedistribution());

	genWindow->setCounter(noise->getCounter());
	this->camera = new Camera();
}

void Program::noiseGenerator(int generator)
{
	if (generator == PERLIN_NOISE)
	{
		map->setNoise(noise);
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

	initiateVariables();

	initiateData();

	this->window = glfwCreateWindow(WIDTH, HEIGHT, "Prelin Noise City", NULL, NULL);
	if (initiateWindow(this->window) == false)
		returnValue = false;

	glfwMakeContextCurrent(window);

	initiateImgui(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		returnValue = false;
	}
	
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetWindowSizeLimits(window, WIDTH, HEIGHT, WIDTH, HEIGHT);	//Sets the screen to a fixed size, that can't be changed by pulling the edges

	//mouse_callback(window, lastX, lastY);
	//glfwSetCursorPosCallback(window, cursor);

	//glfwSetCursorPosCallback(window, mouse_callback);
	//glfwSetCursorPos(window, camera->mouseMovement);
	//glfwGetCursorPos(window, camera->mouseMovement);


	//glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	renderPass.createShader("./Graphic/Shaders/vertex", "NULL", "./Graphic/Shaders/fragment");

	std::string const path = "./Models/Box/Box.obj";
	models.push_back(path);
	//deferred->initiateDeferred();

	return returnValue;
}

bool Program::Run()
{
	ImGui_ImplGlfwGL3_NewFrame();
	
	myKeyInput->keyInput(window, genWindow, shouldRun);		//Checks if any key was pressed 

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
	delete this->seed;
	delete this->myKeyInput;
	delete this->genWindow;
	//delete this->dataManager;
	//delete this->myObject;
	delete this->camera;

	glfwTerminate();
}

void Program::render()
{
	//Cleans the color buffer and set the defaultbacgroundcolor
	glClearColor(0.3f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Rendering the Deferred part
	//deferred->render();
	//glBindVertexArray(myObject->getVAO()); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	//glBindVertexArray(models);
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	
	//// draw our first triangle
	glUseProgram(renderPass.getShaderProgramID());

	glm::mat4 projection = glm::perspective(FOV, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
	glm::mat4 view = camera->getView();
	renderPass.setMat4("projection", projection);
	renderPass.setMat4("view", view);

	glm::mat4 model;
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f));	  // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));			 // it's a bit too big for our scene, so scale it down
	renderPass.setMat4("model", model);

	
	for (int i = 0; i < models.size(); i++)
		models[i].Draw(renderPass);

	//ImGui that handles the graphical interface
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}