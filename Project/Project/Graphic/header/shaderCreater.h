#ifndef SHADERCREATER_H
#define SHADERCREATER_H

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <string>
#include <iostream>
#include <fstream>

class shaderCreater
{
private:
	GLuint programID;

public:
	shaderCreater();
	~shaderCreater();

	GLuint getShaderProgramID()const;
	void createShader(std::string vertexShader, std::string geometryShader, std::string fragmentShader);
	void setFloat(std::string name, int value)const;
};

#endif
