//Includes
#include "Graphic\header\Program.h"
#include <crtdbg.h>

#/*include "Graphic\header\shaderCreater.h"
#include "Defines.h"

void initiateGLFW();

bool initiateWindow(GLFWwindow* window);
void render();
void createTriangle();
void createShader(std::string vertexShader, std::string geometryShader, std::string fragmentShader);
GLuint getShaderProgramID();

shaderCreater renderPass;
GLuint VAO = 0;
GLuint VBO = 0;
GLuint programID = 0;*/

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	 /*initiateGLFW();
	
	GLFWwindow* window;
	window = glfwCreateWindow(WIDTH, HEIGHT, "Prelin Noise City", NULL, NULL);
	
	if (initiateWindow(window) == false)
	{
		std::system("PAUSE");
		return -1;
	}
		
	glfwMakeContextCurrent(window);
	
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		std::system("PAUSE");
		return -1;
	}
	
	createTriangle();
	createShader("Graphic/Shaders/vertex", "NULL", "Graphic/Shaders/fragment");
	//renderPass.createShader("Graphic/Shaders/vertex", "NULL", "Graphic/Shaders/fragment");
	
	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetWindowSizeLimits(window, WIDTH, HEIGHT, WIDTH, HEIGHT);
	
	
	//createTriangleData();
	//
	while (!glfwWindowShouldClose(window))
	{
		//inputs from the keyboard
		//keyInput(window);
	
		//rendering happens here...
		render();
		
		//Checks the call events and swap the buffers
		glfwPollEvents();
		glfwSwapBuffers(window);
	} */

	Program* myProgram = new Program();
	
	if (myProgram == nullptr)
		return NULL;
	
	if (!myProgram->Start())
		return NULL;
	
	//The main loop
	while (myProgram->Run());
	
	//Delete and cleanup
	myProgram->Stop();
	delete myProgram;

	std::system("PAUSE");

	return 0;
}

//void initiateGLFW()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);	 //This sets the Major requierments of Opengl to Version 4.x
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);	//This sets the Minor requierments of Opengl to Version x.3
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//}
//
//bool initiateWindow(GLFWwindow* window)
//{
//	bool returnValue = true;
//
//	if (window == NULL)
//	{
//		std::cout << "Failed to create GLFW window" << std::endl;
//		glfwTerminate();
//		returnValue = false;
//	}
//
//
//	return returnValue;
//}
//
//void render()
//{
//	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//
//	 //draw our first triangle
//	/*glUseProgram(renderPass.getShaderProgramID());*/
//	glUseProgram(getShaderProgramID());
//	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
//	glDrawArrays(GL_TRIANGLES, 0, 3);
//	
//}
//
//void createTriangle()
//{
//	float vertices[] = {
//
//		-0.5f, -0.5f, 0.0f,
//		0.5f, -0.5f, 0.0f,
//		0.0f,  0.5f, 0.0f
//	};
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	 //bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	 //note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	 //You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//	 //VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//	glBindVertexArray(0);
//}
//
//void createShader(std::string vertexShader, std::string geometryShader, std::string fragmentShader)
//{
//	GLint success = 0;
//	char infoLog[512];
//
//	//Vertex shader
//	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
//	//Open glsl file and put it in a string
//	std::ifstream shaderFile(vertexShader + ".glsl");
//	//std::ifstream shaderFile(vertexShader);
//	std::string shaderText((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
//	shaderFile.close();
//	//Make a double pointer (only valid here)
//	const char* shaderTextPtr = shaderText.c_str();
//	//Ask GL to load this
//	glShaderSource(vs, 1, &shaderTextPtr, nullptr);
//
//	//Compile shader
//	glCompileShader(vs);
//
//	//Test if compilation of shader-file went ok
//	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
//	if (success == GL_FALSE || shaderText == "")
//	{
//		glGetShaderInfoLog(vs, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//		system("PAUSE");
//		glDeleteShader(vs);
//		exit(-1);
//	}
//
//	std::cout << shaderText << std::endl;
//
//	//Geometry shader
//	GLuint gs = 0;
//	if (geometryShader != "NULL")
//	{
//		//Geometry shader
//		gs = glCreateShader(GL_GEOMETRY_SHADER);
//		//Open glsl file and put it in a string
//		shaderFile.open(geometryShader + ".glsl");
//		shaderText.assign((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
//		shaderFile.close();
//		//Make a double pointer (only valid here)
//		shaderTextPtr = shaderText.c_str();
//		//Ask GL to load this
//		glShaderSource(gs, 1, &shaderTextPtr, nullptr);
//
//		//////Compile shader
//		glCompileShader(gs);
//
//		////Test if compilation of shader-file went ok
//		glGetShaderiv(gs, GL_COMPILE_STATUS, &success);
//		if (success == GL_FALSE)
//		{
//			glGetShaderInfoLog(gs, 512, NULL, infoLog);
//			std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
//			system("PAUSE");
//			glDeleteShader(gs);
//			exit(-1);
//		}
//	}
//
//	//Fragment shader
//	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
//	//Open glsl file and put it in a string
//	shaderFile.open(fragmentShader + ".glsl");
//	shaderText.assign((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
//	shaderFile.close();
//	//Make a double pointer (only valid here)
//	shaderTextPtr = shaderText.c_str();
//	//Ask GL to load this
//	glShaderSource(fs, 1, &shaderTextPtr, nullptr);
//
//	//Compile shader
//	glCompileShader(fs);
//
//	//Test if compilation of shader-file went ok
//	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
//	if (success == GL_FALSE)
//	{
//		glGetShaderInfoLog(fs, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//		system("PAUSE");
//		glDeleteShader(fs);
//		exit(-1);
//	}
//
//	std::cout << "\n" << shaderText << std::endl;
//
//	//Link shader-program (connect vs,(gs) and fs)
//	programID = glCreateProgram();
//	glAttachShader(programID, vs);
//	if (geometryShader != "NULL")
//		glAttachShader(programID, gs);
//	glAttachShader(programID, fs);
//	glLinkProgram(programID);
//
//	////Create a Uniform Buffer Object(UBO)
//	////Create a buffer name
//	//glGenBuffers(1, &UBO);
//	////Bind buffer to work further with it
//	//glBindBuffer(GL_UNIFORM_BUFFER, UBO);
//	////Allocate memory for the buffer in the GPU
//	//glBufferData(GL_UNIFORM_BUFFER, sizeof(valuesFromCPUToGPU), NULL, GL_STATIC_DRAW);
//	////Because we hard-coded "Binding = 3" in the shader we can do this:
//	////Bind Uniform Buffer to binding point 3 (without caring about index of UBO)
//	//glBindBufferBase(GL_UNIFORM_BUFFER, 3, UBO);
//	////Good practice , unbind buffer
//	//glBindBuffer(GL_UNIFORM_BUFFER, 0);
//
//	//Checks if the linking between the shaders works
//	glGetProgramiv(programID, GL_LINK_STATUS, &success);
//	if (!success) {
//		glGetProgramInfoLog(programID, 512, NULL, infoLog);
//		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
//		system("PAUSE");
//		exit(-1);
//	}
//
//	// in any case (compile sucess or not), we only want to keep the 
//	// Program around, not the shaders.
//	glDetachShader(programID, vs);
//	if (geometryShader != "NULL")
//		glDetachShader(programID, gs);
//	glDetachShader(programID, fs);
//	glDeleteShader(vs);
//	if (geometryShader != "NULL")
//		glDeleteShader(gs);
//	glDeleteShader(fs);
//
//
//}
//
//GLuint getShaderProgramID()
//{
//	return programID;
//}  