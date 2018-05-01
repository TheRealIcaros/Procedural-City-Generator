#ifndef CAMERA_H
#define CARERA_H

//3D-math
#include <glm.hpp>
#include <GLFW\glfw3.h>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

#include "../../Defines.h"

class Camera
{
private:
	glm::mat4 View;

	glm::vec3 cameraPosition;
	glm::vec3 lookAtVector;
	glm::vec3 upVector;

	float yaw;
	float pitch;
	float sensitivity;
	float speed;

	// Pitch/Yaw Properties
	bool firstMouse;
	float lastX;
	float lastY;

public:
	Camera();
	Camera(glm::vec3 cameraPosition, glm::vec3 lookAtVector);
	Camera(glm::vec3 cameraPosition, glm::vec3 lookAtVector, glm::vec3 upVector);
	~Camera();
	void setLookAtVector(glm::vec3 lookAtVector);
	void moveCameraPosition(glm::vec3 movement);
	void mouseMovement(float xoffset, float yoffset);

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
