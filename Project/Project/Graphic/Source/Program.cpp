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

Program::Program()
{
	initiateGLFW();

	this->window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);
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

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		returnValue = false;
	}

	glViewport(0, 0, 800, 600);
	glfwSetWindowSizeLimits(window, WIDTH, HEIGHT, WIDTH, HEIGHT);	//Sets the screen to a fixed size, that can't be changed by pulling the edges
	//glfwSetFramebufferSizeCallback(window, resizeWindow);

	return returnValue;
}

bool Program::Run()
{
	keyInput(window);				//Checks if any key was pressed 


	glClearColor(0.0f, 0.3f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);

	glfwSwapBuffers(window);
	glfwPollEvents();


	return shouldRun;
}

void Program::Stop()
{
	glfwTerminate();
}

void Program::keyInput(GLFWwindow *window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		shouldRun = false;
	}

	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS && keyIsPressedF1 == false)
	{
		keyIsPressedF1 = true;
		std::cout << "HEJ HEJ" << std::endl;
	}
	else if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_RELEASE && keyIsPressedF1 == true)
	{
		keyIsPressedF1 = false;
		std::cout << "Kalle Anka" << std::endl;
	}
}

//void render()
//{
//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	// draw our first triangle
//	glUseProgram(renderPass.getShaderProgramID());
//	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//
//}