#include "../header/Camera.h"

Camera::Camera()
{

}

Camera::Camera(GLFWwindow* window)
{
	this->cameraPosition = { 0.0f, 0.0f, 0.0f };
	this->lookAtVector = { 0.0f, 0.0f, 0.0f };
	this->upVector = { 0.0f, 1.0f, 0.0f };
	this->yaw = -90.0f;
	this->pitch = 0.0f;
	this->sensitivity = 0.05f;
	this->speed = 10.0f;

	//Projection Matrix values
	this->FOV = 0.45f;
	this->aspecRatio = WIDTH / HEIGHT;
	this->nearPlane = 0.1f;
	this->farPlane = 250.0f;

	//Initiates the mouse
	this->myMouse = new Mouse(window);

	//Matricies
	this->View = glm::lookAt(this->cameraPosition, this->cameraPosition + this->lookAtVector, this->upVector);
	this->projection = glm::perspective(FOV, aspecRatio, nearPlane, farPlane);
}

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 lookAtVector, GLFWwindow* window)
{
	this->cameraPosition = cameraPosition;
	this->lookAtVector = lookAtVector;
	this->upVector = { 0.0f, 1.0f, 0.0f };
	this->yaw = -90.0f;
	this->pitch = 0.0f;
	this->sensitivity = 0.05f;
	this->speed = 5.0f;

	//Initiates the mouse
	this->myMouse = new Mouse(window);

	this->View = glm::lookAt(this->cameraPosition, this->cameraPosition + this->lookAtVector, this->upVector);
}

Camera::Camera(glm::vec3 cameraPosition, glm::vec3 lookAtVector, glm::vec3 upVector, GLFWwindow* window)
{
	this->cameraPosition = cameraPosition;
	this->lookAtVector = lookAtVector;
	this->upVector = upVector;
	this->yaw = -90.0f;
	this->pitch = 0.0f;
	this->sensitivity = 0.05f;
	this->speed = 5.0f;

	//Initiates the mouse
	this->myMouse = new Mouse(window);

	this->View = glm::lookAt(this->cameraPosition, this->cameraPosition + this->lookAtVector, this->upVector);
}

Camera::~Camera()
{
	//delete this->myMouse;
}

void Camera::deleteMouse()
{
	delete this->myMouse;
}

void Camera::setLookAtVector(glm::vec3 lookAtVector)
{
	this->lookAtVector = lookAtVector;
	this->View = glm::lookAt(this->cameraPosition, this->cameraPosition + this->lookAtVector, this->upVector);
}

void Camera::moveCameraPosition(glm::vec3 movement)
{
	this->cameraPosition += movement;
	this->View = glm::lookAt(this->cameraPosition, this->cameraPosition + this->lookAtVector, this->upVector);
}

void Camera::mouseMovement(GLFWwindow* window, float xoffset, float yoffset)
{
	this->myMouse->moveMouse(window, xoffset, yoffset);

	xoffset *= this->sensitivity;
	yoffset *= this->sensitivity;

	this->yaw += xoffset;
	this->pitch += yoffset;

	//Check if within bounderys
	if (this->pitch > 89.0f)
		this->pitch = 89.0f;
	if (this->pitch < -89.0f)
		this->pitch = -89.0f;

	glm::vec3 front;
	front.x = cos(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));
	front.y = sin(glm::radians(this->pitch));
	front.z = sin(glm::radians(this->yaw)) * cos(glm::radians(this->pitch));

	this->setLookAtVector(glm::normalize(front));
}

// - GET/SET
void Camera::setYaw(float yaw)
{
	this->yaw = yaw;
}

float Camera::getYaw()const
{
	return this->yaw;
}

void Camera::setPitch(float pitch)
{
	this->pitch = pitch;
}

float Camera::getPitch()const
{
	return this->pitch;
}

glm::mat4 Camera::getView()const
{
	return this->View;
}

glm::mat4 Camera::getProjection()const
{
	return this->projection;
}

float Camera::getSpeed()const
{
	return this->speed;
}

glm::vec3 Camera::getLookAtVector()const
{
	return this->lookAtVector;
}

glm::vec3 Camera::getUpVector()const
{
	return this->upVector;
}

glm::vec3 Camera::getPosition()const
{
	return this->cameraPosition;
}

void Camera::setPosition(glm::vec3 position)
{
	this->cameraPosition = position;
	this->View = glm::lookAt(this->cameraPosition, this->cameraPosition + this->lookAtVector, this->upVector);
}

void Camera::setCameraPosition(float xaxis, float yaxis, float zaxis)
{
	this->cameraPosition.x = xaxis; //Set the camera xaxis position
	this->cameraPosition.y = yaxis; //Set the camera yaxis position
	this->cameraPosition.z = zaxis; //Set the camera zaxis position
	this->View = glm::lookAt(this->cameraPosition, this->cameraPosition + this->lookAtVector, this->upVector); //Update the View-matrix
}

void Camera::setHeight(float Y)
{
	this->cameraPosition.y = Y;
	this->View = glm::lookAt(this->cameraPosition, this->cameraPosition + this->lookAtVector, this->upVector);
}