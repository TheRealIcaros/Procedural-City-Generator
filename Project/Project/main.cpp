//Includes
#include "Graphic\header\Program.h"

//3D-math
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Logic\header\PerlinNoise.h"
#include "Logic\header\ppm.h"



int main()
{
	// Define the size of the image
	unsigned int width = 300, height = 300;

	// Create an empty PPM image
	ppm image(width, height);

	// Create a PerlinNoise object with a random permutation vector generated with seed
	unsigned int seed = 237;
	PerlinNoise pn(seed);

	unsigned int kk = 0;
	// Visit every pixel of the image and assign a color generated with Perlin noise
	for (unsigned int i = 0; i < height; ++i) {     // y
		for (unsigned int j = 0; j < width; ++j) {  // x
			double x = (double)j / ((double)width);
			double y = (double)i / ((double)height);

			// Typical Perlin noise
			double n = /*20 **/ 1 * pn.noise(1/** 10*/ * x, 1 * /*10 **/ y, 0.8)
					+ /*20 **/ 0.5 * pn.noise(2 /** 10*/ * x, 2 * /*10 * */y, 0.8)
					+ /*20 **/ 0.25 * pn.noise(4 /** 10*/ * x, 2 * /*10 **/ y, 0.8);

			n /= 1 + 0.5 + 0.25;
			/*n = n - floor(n);*/

			////// Wood like structure
			//n = 20 * pn.noise(10 * x, 10 * y, 0.8);
			//n = n - floor(n);

			// Map the values to the [0, 255] interval, for simplicity we use 
			// tones of grey
			image.r[kk] = floor(255 * n);
			image.g[kk] = floor(255 * n);
			image.b[kk] = floor(255 * n);
			kk++;
		}
	}

	// Save the image in a binary PPM file
	image.write("figure_7_P.ppm");
	/*renderPass.createShader("Graphic/Shaders/vertexShader", "NULL", "Graphic/Shaders/fragmentShader");
	//createTriangleData();

	//while (!glfwWindowShouldClose(window))
	//{
	//	//inputs from the keyboard
	//	keyInput(window);

	//	//rendering happens here...
	//	render();
	//	
	//	//Checks the call events and swap the buffers
	//	glfwPollEvents();
	//	glfwSwapBuffers(window);
	}*/

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

	return 0;
}

//void initiateGLFW()
//{
//	glfwInit();
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
//	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
//}
//
//void resizeWindow(GLFWwindow* window, int width, int height)
//{
//	glViewport(0, 0, width, height);
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
//bool startSequence(GLFWwindow* window)
//{
//	bool returnValue = true;
//
//	if (initiateWindow(window) == false)
//		returnValue = false;
//
//	glfwMakeContextCurrent(window);
//
//	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
//	{
//		std::cout << "Failed to initialize GLAD" << std::endl;
//		returnValue = false;
//	}
//
//	glViewport(0, 0, 800, 600);
//
//	glfwSetFramebufferSizeCallback(window, resizeWindow);
//
//	return returnValue;
//}
//
//void keyInput(GLFWwindow* window)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//		glfwSetWindowShouldClose(window, true);
//
//	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS && keyIsPressedF1 == false)
//	{
//		keyIsPressedF1 = true;
//		std::cout << "HEJ HEJ" << std::endl;
//	}
//	else if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_RELEASE && keyIsPressedF1 == true)
//	{
//		keyIsPressedF1 = false;
//		std::cout << "Kalle Anka" << std::endl;
//	}
//}
//
//void createTriangleData()
//{
//	float vertices[] = {
//
//		-0.5f, -0.5f, 0.0f,
//		 0.5f, -0.5f, 0.0f,
//		 0.0f,  0.5f, 0.0f
//	};
//
//	glGenVertexArrays(1, &VAO);
//	glGenBuffers(1, &VBO);
//	// bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
//	glBindVertexArray(VAO);
//
//	glBindBuffer(GL_ARRAY_BUFFER, VBO);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
//
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
//	glEnableVertexAttribArray(0);
//
//	// note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//
//	// You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
//	// VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
//	glBindVertexArray(0);
//}
//
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