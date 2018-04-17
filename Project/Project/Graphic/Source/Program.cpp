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

	//window = glfwCreateWindow(WIDTH, HEIGHT, "Perlin stuff", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		returnValue = false;
	}

	return returnValue;
}

//GLFWwindow* Program::createWindow()
//{
//	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Perlin stuff", NULL, NULL);
//	if (window == NULL)
//	{
//		std::cout << "Failes to create GLFW window" << std::endl;
//		glfwTerminate();
//		std::exit(-1);
//	}
//	glfwMakeContextCurrent(window);
//
//	return window;
//}

void Program::initiateVariables()
{
	//Mics
	this->keyIsPressedF1 = false;
	this->shouldRun = true;
	this->VAO = 0;
	this->VBO = 0;
	this->programID = 0;
	
	//this->genWindow = GenWindow::getInstance();
	//this->myKeyInput = new KeyIn();
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

	//initiateImgui(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		returnValue = false;
	}

	//createTriangle();
	////renderPass.createShader("../Shaders/vertex", "NULL", "../Shaders/fragment");
	//createShader("../Shaders/vertex", "NULL", "../Shaders/fragment");

	glViewport(0, 0, WIDTH, HEIGHT);
	glfwSetWindowSizeLimits(window, WIDTH, HEIGHT, WIDTH, HEIGHT);	//Sets the screen to a fixed size, that can't be changed by pulling the edges
	
	return returnValue;
}

bool Program::Run()
{
	//ImGui_ImplGlfwGL3_NewFrame();
	//myKeyInput->keyInput(window, genWindow, shouldRun);	//Checks if any key was pressed 

	//myKeyInput->keyInput(window, shouldRun);

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
	//glUseProgram(renderPass.getShaderProgramID());
	glUseProgram(getShaderProgramID());
	glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

GLuint Program::getShaderProgramID()const
{
	return this->programID;
}

void Program::createShader(std::string vertexShader, std::string geometryShader, std::string fragmentShader)
{
	GLint success = 0;
	char infoLog[512];

	//Vertex shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	//Open glsl file and put it in a string
	std::ifstream shaderFile(vertexShader + ".glsl");
	//std::ifstream shaderFile(vertexShader);
	std::string shaderText((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();
	//Make a double pointer (only valid here)
	const char* shaderTextPtr = shaderText.c_str();
	//Ask GL to load this
	glShaderSource(vs, 1, &shaderTextPtr, nullptr);

	//Compile shader
	glCompileShader(vs);

	//Test if compilation of shader-file went ok
	glGetShaderiv(vs, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderInfoLog(vs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		system("PAUSE");
		glDeleteShader(vs);
		exit(-1);
	}

	std::cout << "Vertex shader code:\n" << shaderText << std::endl;

	//Geometry shader
	GLuint gs = 0;
	if (geometryShader != "NULL")
	{
		//Geometry shader
		gs = glCreateShader(GL_GEOMETRY_SHADER);
		//Open glsl file and put it in a string
		shaderFile.open(geometryShader + ".glsl");
		shaderText.assign((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
		shaderFile.close();
		//Make a double pointer (only valid here)
		shaderTextPtr = shaderText.c_str();
		//Ask GL to load this
		glShaderSource(gs, 1, &shaderTextPtr, nullptr);

		//////Compile shader
		glCompileShader(gs);

		////Test if compilation of shader-file went ok
		glGetShaderiv(gs, GL_COMPILE_STATUS, &success);
		if (success == GL_FALSE)
		{
			glGetShaderInfoLog(gs, 512, NULL, infoLog);
			std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
			system("PAUSE");
			glDeleteShader(gs);
			exit(-1);
		}
	}

	//Fragment shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	//Open glsl file and put it in a string
	shaderFile.open(fragmentShader + ".glsl");
	//shaderFile.open(fragmentShader);
	shaderText.assign((std::istreambuf_iterator<char>(shaderFile)), std::istreambuf_iterator<char>());
	shaderFile.close();
	//Make a double pointer (only valid here)
	shaderTextPtr = shaderText.c_str();
	//Ask GL to load this
	glShaderSource(fs, 1, &shaderTextPtr, nullptr);

	//Compile shader
	glCompileShader(fs);

	//Test if compilation of shader-file went ok
	glGetShaderiv(fs, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		glGetShaderInfoLog(fs, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		system("PAUSE");
		glDeleteShader(fs);
		exit(-1);
	}

	std::cout << "\nFragment shader code:\n" << shaderText << std::endl;

	//Link shader-program (connect vs,(gs) and fs)
	this->programID = glCreateProgram();
	glAttachShader(this->programID, vs);
	if (geometryShader != "NULL")
		glAttachShader(this->programID, gs);
	glAttachShader(this->programID, fs);
	glLinkProgram(this->programID);

	////Create a Uniform Buffer Object(UBO)
	////Create a buffer name
	//glGenBuffers(1, &UBO);
	////Bind buffer to work further with it
	//glBindBuffer(GL_UNIFORM_BUFFER, UBO);
	////Allocate memory for the buffer in the GPU
	//glBufferData(GL_UNIFORM_BUFFER, sizeof(valuesFromCPUToGPU), NULL, GL_STATIC_DRAW);
	////Because we hard-coded "Binding = 3" in the shader we can do this:
	////Bind Uniform Buffer to binding point 3 (without caring about index of UBO)
	//glBindBufferBase(GL_UNIFORM_BUFFER, 3, UBO);
	////Good practice , unbind buffer
	//glBindBuffer(GL_UNIFORM_BUFFER, 0);

	//Checks if the linking between the shaders works
	glGetProgramiv(this->programID, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(this->programID, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::COMPILATION_FAILED\n" << infoLog << std::endl;
		system("PAUSE");
		exit(-1);
	}

	// in any case (compile sucess or not), we only want to keep the 
	// Program around, not the shaders.
	glDetachShader(this->programID, vs);
	if (geometryShader != "NULL")
		glDetachShader(this->programID, gs);
	glDetachShader(this->programID, fs);
	glDeleteShader(vs);
	if (geometryShader != "NULL")
		glDeleteShader(gs);
	glDeleteShader(fs);
}