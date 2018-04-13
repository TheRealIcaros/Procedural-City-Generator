#ifndef OBJECT_H
#define OBJECT_H

//3D-math
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../header/shaderCreater.h"

class Object
{
private:
	//Shaders
	shaderCreater renderPass;

	//Graphic stuff
	GLuint VAO;
	GLuint VBO;

	void intitiateVariables();
	void createData();
	void createShaderData();

public:
	Object();
	~Object();

	void renderObject();
};

#endif
