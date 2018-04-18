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
	
	this->seed = new SeedConverter();
	this->value = Values::getInstance();
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

	if (value->getGenerate() == true)
	{
		// Create an empty PPM image
		/*ppm image(value->getTSizeX(), value->getTSizeY());*/
		// Create a PerlinNoise object with a random permutation vector generated with seed

		//create a seed translate function use temp seed for now

		if (value->getInputBuf().compare("") != 0)
		{
			seed->setSeed(value->getInputBuf());
		}
		PerlinNoise pn(seed->getIntegerSeed());
		unsigned int kk = 0;

		// Visit every pixel of the image and assign a color generated with Perlin noise


		//for (unsigned int i = 0; i < height; ++i) {     // y
		//	for (unsigned int j = 0; j < width; ++j) {  // x
		//		double x = (double)j / ((double)width);
		//		double y = (double)i / ((double)height);

		//		// Typical Perlin noise
		//		double n = /*20 **/ 1 * pn.noise(1/** 10*/ * x, 1 * /*10 **/ y, 0.8)
		//			+ /*20 **/ 0.5 * pn.noise(2 /** 10*/ * x, 2 * /*10 * */y, 0.8)
		//			+ /*20 **/ 0.25 * pn.noise(4 /** 10*/ * x, 2 * /*10 **/ y, 0.8);

		//		n /= 1 + 0.5 + 0.25;
		//		/*n = n - floor(n);*/

		//		////// Wood like structure
		//		//n = 20 * pn.noise(10 * x, 10 * y, 0.8);
		//		//n = n - floor(n);

		//		// Map the values to the [0, 255] interval, for simplicity we use 
		//		// tones of grey
		//		image.r[kk] = floor(255 * n);
		//		image.g[kk] = floor(255 * n);
		//		image.b[kk] = floor(255 * n);
		//		kk++;
		//	}
		//}

		//// Save the image in a binary PPM file
		//image.write("figure_7_P.ppm");

		value->setGenerate(false);
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