#ifndef OBJECT_H
#define OBJECT_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>

class Object
{
private:
	GLuint VAO;
	GLuint VBO;

	void initiateVariables();

public:
	Object();
	~Object();

	void createT();

	GLuint getVAO()const;
};

#endif
