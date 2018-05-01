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
	
	////Pitch/Yaw properties
	//firstMouse = true;
	//lastX = WIDTH / 2.0f;
	//lastY = HEIGHT / 2.0f;

	this->genWindow = GenWindow::getInstance();
	this->myKeyInput = new KeyIn();
	this->camera = new Camera();
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

	//mouse_callback(window, lastX, lastY);
	//glfwSetCursorPosCallback(window, cursor);

	//glfwSetCursorPosCallback(window, camera->mouse_callback);
	

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
	
	myKeyInput->keyInput(window, genWindow, shouldRun);	//Checks if any key was pressed 

	genWindow->draw();								//Draw function for ImGui

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
	delete this->camera;
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
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, -1.0f)); // translate it down so it's at the center of the scene
	model = glm::scale(model, glm::vec3(2.0f, 2.0f, 2.0f));	// it's a bit too big for our scene, so scale it down
	renderPass.setMat4("model", model);

	
	for (int i = 0; i < models.size(); i++)
		models[i].Draw(renderPass);

	//ImGui that handles the graphical interface
	ImGui::Render();
	ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
}