#include <glad/glad.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Imgui\imgui.h"

//3D-math
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

//Defines
#include "Defines.h"

void initiateGLFW();
void resizeWindow(GLFWwindow* window, int width, int height);
bool initiateWindow(GLFWwindow* window);
bool startSequence(GLFWwindow* window);
void keyInput(GLFWwindow* window);
void createShaders();
void createTriangleData();
void render();

//Global values
GLuint gVertexBuffer = 0;
GLuint gVertexAttribute = 0;
GLuint gShaderProgram = 0;

GLuint gUbo = 0;  //Uniform Buffer Object identifyer

glm::mat4 WorldMatrix()
{
	glm::mat4 World;

	//This rotates my matrices
	World = glm::rotate(World, 180.0f, glm::vec3(0, 1, 0));

	return World;
}

glm::mat4 ViewMatrix()
{
	glm::vec3 cameraPos(0.0f, 0.0f, -2.0f);
	glm::vec3 lookAtVector(0.0f, 0.0f, 0.0f);
	glm::vec3 upVector(0.0f, 1.0f, 0.0f);

	glm::mat4 View = glm::lookAt(cameraPos, lookAtVector, upVector);

	return View;
}

glm::mat4 ProjectionMatrix()
{
	float FOV = 0.45f * PI;
	float aspectRatio = 640 / 480;

	glm::mat4 Projection = glm::perspective(FOV, aspectRatio, 0.1f, 20.0f);

	return Projection;
}

//My matrices
glm::mat4 World = WorldMatrix();
glm::mat4 View = ViewMatrix();
glm::mat4 Projection = ProjectionMatrix();

//The struct to be stored in a buffer
struct valuesFromCPUToGPU
{
	glm::mat4 World;
	glm::mat4 View;
	glm::mat4 Projection;
};

//The buffer data I send
valuesFromCPUToGPU myBufferData = { World, View, Projection };

int main()
{
	////BLARG
	initiateGLFW();
	
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "LearnOpenGL", NULL, NULL);;

	if (startSequence(window) == false)
	{
		glfwTerminate();
		return -1;
	}

	createShaders();

	createTriangleData();

	while (!glfwWindowShouldClose(window))
	{
		//inputs from the keyboard
		keyInput(window);

		//rendering happens here...
		render();
		
		//Checks the call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	}


	glfwTerminate();
	return 0;
}

void initiateGLFW()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void resizeWindow(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

bool initiateWindow(GLFWwindow* window)
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

bool startSequence(GLFWwindow* window)
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

	glfwSetFramebufferSizeCallback(window, resizeWindow);

	return returnValue;
}

void keyInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

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

void createShaders()
{
	// local buffer to store error strings when compiling
		char buff[1024];
	memset(buff, 0, 1024);

	//create vertex shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	// open glsl file and put it in a string
	std::ifstream shaderFile("vertexShader.glsl");
	std::string shaderText((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();
	// make a double pointer (only valid here)
	const char* shaderTextPtr = shaderText.c_str();
	// ask GL to load this
	glShaderSource(vs, 1, &shaderTextPtr, nullptr);

	// ask GL to compile it
	glCompileShader(vs);

	// error handling example
	GLint success = 0;
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE) {
		GLint msgSize = 0;
		glGetShaderiv(vs, GL_INFO_LOG_LENGTH, &msgSize);
		char* msg = new char[msgSize];
		glGetShaderInfoLog(vs, msgSize, nullptr, msg);
		glDeleteShader(vs);
		// Visual Studio output box
		exit(-1);
	}

	//create geometry shader
	//GLuint gs = glCreateShader(GL_GEOMETRY_SHADER);
	//shaderFile.open("geometryShader.glsl");
	//shaderText.assign((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	//shaderFile.close();
	//shaderTextPtr = shaderText.c_str();
	//glShaderSource(gs, 1, &shaderTextPtr, nullptr);
	//glCompileShader(gs);
	//
	//success = 0;
	//glGetShaderiv(gs, GL_COMPILE_STATUS, &success);
	//if (success == GL_FALSE) {
	//	GLint msgSize = 0;
	//	glGetShaderiv(gs, GL_INFO_LOG_LENGTH, &msgSize);
	//	char* msg = new char[msgSize];
	//	glGetShaderInfoLog(gs, msgSize, nullptr, msg);
	//	glDeleteShader(gs);
	//	exit(-1);
	//}

	//kaffe

	//create fragment shader | same process.
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	shaderFile.open("fragmentShader.glsl");
	shaderText.assign((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();
	shaderTextPtr = shaderText.c_str();
	glShaderSource(fs, 1, &shaderTextPtr, nullptr);
	glCompileShader(fs);

	success = 0;
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint msgSize = 0;
		glGetShaderiv(fs, GL_INFO_LOG_LENGTH, &msgSize);
		char* msg = new char[msgSize];
		glGetShaderInfoLog(fs, msgSize, nullptr, msg);
		glDeleteShader(fs);
		exit(-1);
	}

	//link shader program (connect vs and ps)
	gShaderProgram = glCreateProgram();
	glAttachShader(gShaderProgram, vs);
	//glAttachShader(gShaderProgram, gs);
	glAttachShader(gShaderProgram, fs);
	glLinkProgram(gShaderProgram);


	// NEW - CREATE Uniform Buffer Object
	// Create buffer name
	glGenBuffers(1, &gUbo);
	// bind buffer to work further with it...
	glBindBuffer(GL_UNIFORM_BUFFER, gUbo);
	// allocate memory for the buffer in the GPU
	//glBufferData(GL_UNIFORM_BUFFER, sizeof(valuesFromCPUToGPU), NULL, GL_STATIC_DRAW);
	// because we hard-coded "binding=3" in the shader code we can do this:
	// bind Uniform Buffer to binding point 3 (without caring about index of UBO)
	glBindBufferBase(GL_UNIFORM_BUFFER, 3, gUbo);
	// good practice, unbind buffer
	glBindBuffer(GL_UNIFORM_BUFFER, 0);

	//Check if the shaders works together
	success = 0;
	glGetProgramiv(gShaderProgram, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		// query information about the compilation (nothing if compilation went fine!)
		memset(buff, 0, 1024);
		glGetProgramInfoLog(gShaderProgram, 1024, nullptr, buff);
		// print to Visual Studio debug console output
		OutputDebugStringA(buff);
	}

	// in any case (compile sucess or not), we only want to keep the 
	// Program around, not the shaders.
	glDetachShader(gShaderProgram, vs);
	//glDetachShader(gShaderProgram, gs);
	glDetachShader(gShaderProgram, fs);
	glDeleteShader(vs);
	//glDeleteShader(gs);
	glDeleteShader(fs);
}

void createTriangleData()
{
	// this is how we will structure the input data for the vertex shader
	// every six floats, is one vertex.
	struct TriangleVertex
	{
		float x, y, z; // pos1
		float r, g; // col
	};
	// create the actual data in plane Z = 0
	TriangleVertex triangleVertices[6] =
	{
		// pos and color for each vertex
		{ -0.5f,  0.5f,  0.0f,  0.0f,  0.0f }, //top left
		{  0.5f, -0.5f,  0.0f,  1.0f,  1.0 }, //bottom right
		{  0.5f,  0.5f,  0.0f,  1.0f,  0.0f }, //top right
		
		{ -0.5f ,  0.5f,  0.0f,  0.0f,  0.0f }, //top left
		{ -0.5f , -0.5f,  0.0f,  0.0f,  1.0f }, //bottom left
		{  0.5f , -0.5f,  0.0f,  1.0f,  1.0f } //bottom right
	};

	// Vertex Array Object (VAO) 
	glGenVertexArrays(1, &gVertexAttribute);
	// bind == enable
	glBindVertexArray(gVertexAttribute);
	// this activates the first and second attributes of this VAO
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	// create a vertex buffer object (VBO) id
	glGenBuffers(1, &gVertexBuffer);
	// Bind the buffer ID as an ARRAY_BUFFER
	glBindBuffer(GL_ARRAY_BUFFER, gVertexBuffer);
	// This "could" imply copying to the GPU immediately, depending on what the driver wants to do...
	glBufferData(GL_ARRAY_BUFFER, sizeof(triangleVertices), triangleVertices, GL_STATIC_DRAW);

	// find out location of input vertex_position in the Vertex Shader 
	GLuint vertexPos = glGetAttribLocation(gShaderProgram, "vertex_position");
	// specify that: the vertex attribute at location "vertexPos", of 3 elements of type FLOAT, 
	// not normalized, with STRIDE != 0, starts at offset 0 of the gVertexBuffer (it is the last bound!)

	if (vertexPos == -1)
	{
		OutputDebugStringA("Error, cannot find 'vertex_position' attribute in Vertex shader\n");
		return;
	}

	glVertexAttribPointer(vertexPos, 3, GL_FLOAT, GL_FALSE, sizeof(TriangleVertex), BUFFER_OFFSET(0));

	// query where which slot corresponds to the input vertex_color in the Vertex Shader 
	GLuint vertexColor = glGetAttribLocation(gShaderProgram, "vertex_tex");
	// specify that: the vertex attribute "vertex_color", of 3 elements of type FLOAT, not normalized, with STRIDE != 0,
	//               starts at offset (12 bytes) of the gVertexBuffer 
	glVertexAttribPointer(vertexColor, 2, GL_FLOAT, GL_FALSE, sizeof(TriangleVertex), BUFFER_OFFSET(sizeof(float) * 3));
}

void render()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(gShaderProgram);

	// we do not need to bind a Buffer object (VBO), just the VAO is enough
	glBindVertexArray(gVertexAttribute);


	glBindBuffer(GL_UNIFORM_BUFFER, gUbo);

	glBufferSubData(GL_UNIFORM_BUFFER, 0, sizeof(valuesFromCPUToGPU), &myBufferData);


	glDrawArrays(GL_TRIANGLES, 0, 6);
}