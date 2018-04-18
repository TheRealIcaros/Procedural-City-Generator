//Includes
#include "Graphic\header\Program.h"
#include <crtdbg.h>

//3D-math
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>
#include "Logic\header\PerlinNoise.h"
#include "Logic\header\ppm.h"



int main()
{
	//// Define the size of the image
	//unsigned int width = 300, height = 300;

	//// Create an empty PPM image
	//ppm image(width, height);

	//// Create a PerlinNoise object with a random permutation vector generated with seed
	//unsigned int seed = 237;
	//PerlinNoise pn(seed);

	//unsigned int kk = 0;
	//// Visit every pixel of the image and assign a color generated with Perlin noise
	//for (unsigned int i = 0; i < height; ++i) {     // y
	//	for (unsigned int j = 0; j < width; ++j) {  // x
	//		double x = (double)j / ((double)width);
	//		double y = (double)i / ((double)height);

	//		// Typical Perlin noise
	//		double n = /*20 **/ 1 * pn.noise(1/** 10*/ * x, 1 * /*10 **/ y, 0.8)
	//				+ /*20 **/ 0.5 * pn.noise(2 /** 10*/ * x, 2 * /*10 * */y, 0.8)
	//				+ /*20 **/ 0.25 * pn.noise(4 /** 10*/ * x, 2 * /*10 **/ y, 0.8);

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

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
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