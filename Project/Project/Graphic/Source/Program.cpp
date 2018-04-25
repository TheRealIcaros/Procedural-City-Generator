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
	
	this->noise = new PerlinNoise();
	this->map = new HeightMap();
	this->seed = new SeedConverter();
	this->genWindow = new GenWindow();
	this->myKeyInput = new KeyIn();
	//this->myObject = new Object();
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

	deferred.initiateDeferred();

	//This creates the data to be drawm staticly
	//myObject->createT();
	//
	//this->renderPass.createShader("./Graphic/Shaders/vertex", "NULL", "./Graphic/Shaders/fragment");

	return returnValue;
}

bool Program::Run()
{
	ImGui_ImplGlfwGL3_NewFrame();
	myKeyInput->keyInput(window, genWindow, shouldRun);	//Checks if any key was pressed 

	genWindow->draw();								//Draw function for ImGui

	if (genWindow->getGenerate() == true)
	{
		if (genWindow->getInputBuf().compare("") != 0)
		{
			seed->setSeed(genWindow->getInputBuf());
		}
		genWindow->setSeed(seed->getIntegerSeed());
		noise->setSeed(seed->getIntegerSeed());

		map->setNoise(noise);

		map->generate(genWindow->getTSizeX(), genWindow->getTSizeY(),genWindow->getTerrainOctave1(),
			genWindow->getTerrainOctave2(), genWindow->getTerrainOctave3(), genWindow->getTerrainOctave4(), genWindow->getTerrainOctave5(), genWindow->getTerrainOctave6(),
			genWindow->getTerrainOctave7(), genWindow->getTerrainOctave8(), genWindow->getTerrainOctavePerc1(), genWindow->getTerrainOctavePerc2(), genWindow->getTerrainOctavePerc3(),
			genWindow->getTerrainOctavePerc4(), genWindow->getTerrainOctavePerc5(), genWindow->getTerrainOctavePerc6(), genWindow->getTerrainOctavePerc7(), genWindow->getTerrainOctavePerc8(),
			genWindow->getRedistribution());

		genWindow->toggleGenerate();
		genWindow->setCounter(noise->getCounter());
	}
	render();										//The render loop for all the graphics

	glfwSwapBuffers(window);
	glfwPollEvents();

	return shouldRun;
}

void Program::Stop()
{
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();

	delete this->noise;
	delete this->map;
	delete this->seed;
	delete this->myKeyInput;
	delete this->genWindow;
	//delete this->myObject;
}

void Program::render()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//Render the Deferred-class object here

	deferred.render();

	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

	//// draw our first triangle
	//glUseProgram(renderPass.getShaderProgramID());
	////glBindVertexArray(myObject->getVAO()); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	//glBindVertexArray(myObject->getVAO());
	//glDrawArrays(GL_TRIANGLES, 0, 3);
}