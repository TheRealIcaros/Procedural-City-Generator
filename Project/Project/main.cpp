//Includes
#include "Graphic\header\Program.h"

int main()
{
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



//
//void render()
//{
//	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
//	glClear(GL_COLOR_BUFFER_BIT);
//
	//// draw our first triangle
	//glUseProgram(renderPass.getShaderProgramID());
	//glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
	//glDrawArrays(GL_TRIANGLES, 0, 3);
	
//}