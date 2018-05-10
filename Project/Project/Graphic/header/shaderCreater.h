#ifndef SHADERCREATER_H
#define SHADERCREATER_H

#include <GL\glew.h>
#include <GLFW/glfw3.h>
#include <gtc\type_ptr.hpp>
#include <glm.hpp>
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

	void unload();
	GLuint getShaderProgramID()const;
	GLuint getUniform(const std::string& name);
	void createShader(std::string vertexShader, std::string geometryShader, std::string fragmentShader);
	void setFloat(std::string name, GLfloat value)const;
	void setMat4(const std::string &name, const glm::mat4 &mat) const;
	void setMat4(GLuint location, const glm::mat4& value);
	void setMat4v(GLuint location, const glm::mat4* value, int n);
};

#endif
