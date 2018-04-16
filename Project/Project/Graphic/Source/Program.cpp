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
	this->VAO = 0;
	this->VBO = 0;

	//System stuff
	this->window = glfwCreateWindow(WIDTH, HEIGHT, "Prelin Noise City", NULL, NULL);
	//this->genWindow = GenWindow::getInstance();
	this->myKeyInput = new KeyIn();
	//this->myObjects = Object();
}

//void Program::initiateImgui(GLFWwindow* window)
//{
//	//Setup Imgui
//	ImGui::CreateContext();
//	ImGuiIO& io = ImGui::GetIO(); (void)io;
//
//	ImGui_ImplGlfwGL3_Init(window, true);
//
//	//Setup style
//	ImGui::StyleColorsDark();
//}

Program::Program()
{
	initiateGLFW();
	initiateVariables();

	renderPass = shaderCreater();
	
}

Program::~Program()
{
}

bool Program::Start()
{
	bool returnValue = true;

	if (initiateWindow(window) == false)
		returnValue = false;

	glfwMakeContextCurrent(window);

	//initiateImgui(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		returnValue = false;
	}

	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetWindowSizeLimits(window, WIDTH, HEIGHT, WIDTH, HEIGHT);	//Sets the screen to a fixed size, that can't be changed by pulling the edges
	//glfwSetFramebufferSizeCallback(window, resizeWindow);

	renderPass.createShader("../Shaders/new", "NULL", "../Shaders/b");
	createTriangle();

	return returnValue;
}

bool Program::Run()
{
	//ImGui_ImplGlfwGL3_NewFrame();

	/*myKeyInput->keyInput(window, genWindow, shouldRun);*/		//Checks if any key was pressed 

	myKeyInput->keyInput(window, shouldRun);

	//genWindow->draw();								//Draw function for ImGui

	render();										//The render loop for all the graphics

	glfwSwapBuffers(window);
	glfwPollEvents();

	return shouldRun;
}

void Program::Stop()
{
	//ImGui_ImplGlfwGL3_Shutdown();
	//ImGui::DestroyContext();

	glfwTerminate();
}

void Program::createTriangle()
{
	float vertices[] = {

		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f,  0.5f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
	glBindVertexArray(0);
}

void Program::render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	//ImGui::Render();
	//ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

	//myObjects.renderObject();
	//// draw our first triangle
	glUseProgram(renderPass.getShaderProgramID());
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
}