//Includes
#include "Graphic\header\Program.h"

//3D-math
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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