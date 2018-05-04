#ifndef CAMERA_H
#define CARERA_H

#include "..\..\Controlls\Header\Mouse.h"

#include <GLFW\glfw3.h>
#include "..\..\Defines.h"


class Camera
{
private:
	//Mouse movements
	Mouse* myMouse;


	glm::mat4 View;

	glm::vec3 cameraPosition;
	glm::vec3 lookAtVector;
	glm::vec3 upVector;

	float yaw;
	float pitch;
	float sensitivity;
	float speed;

	

public:
	Camera(GLFWwindow* window);
	Camera(glm::vec3 cameraPosition, glm::vec3 lookAtVector, GLFWwindow* window);
	Camera(glm::vec3 cameraPosition, glm::vec3 lookAtVector, glm::vec3 upVector, GLFWwindow* window);
	~Camera();
	void setLookAtVector(glm::vec3 lookAtVector);
	void moveCameraPosition(glm::vec3 movement);
	void mouseMovement(GLFWwindow* window, float xoffset, float yoffset);

	// - GET/SET
	void setYaw(float yaw);
	void setPitch(float pitch);
	float getYaw()const;
	float getPitch()const;
	glm::mat4 getView()const;
	float getSpeed()const;
	glm::vec3 getLookAtVector()const;
	glm::vec3 getUpVector()const;
	glm::vec3 getPosition()const;
	void setPosition(glm::vec3 position);
	void setCameraPosition(float xaxis, float yaxis, float zaxis);
	void setHeight(float Y);


	//Mic functions
	//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
};

#endif
