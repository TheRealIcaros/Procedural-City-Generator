#include "../Header/KeyIn.h"

void KeyIn::initiateVariables()
{
	this->keyIsPressedF1 = false; //The button isn't pressed from the start 
	this->keyIsPressedLControl = false; //The button isn't pressed from the start 
	this->cameraCanMove = true;

	this->time.deltaTime = 0.0f;
	this->time.lastFrame = 0.0f;
	this->time.frames = 0;
	this->time.duration = 0.0f;
	this->time.deltaTime = false;
}

KeyIn::KeyIn()
{
	initiateVariables();
}

KeyIn::~KeyIn()
{
}

void KeyIn::calculateDeltaTime()
{
	float currentFrame = (float)glfwGetTime();
	time.deltaTime = currentFrame - time.lastFrame;
	time.lastFrame = currentFrame;

	time.frames++;
	time.duration += time.deltaTime;
	if (time.duration >= 1.0f && time.active)
	{
		printf("FPS: %d, dt: %d\n", time.frames, time.deltaTime);
		time.frames = 0;
		time.duration = 0.0f;
	}
}

void KeyIn::keyInput(GLFWwindow* window, GenWindow* genWindow, bool &shouldRun, Camera* camera)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
		shouldRun = false;
	}


	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS && keyIsPressedF1 == false)
	{
		this->keyIsPressedF1 = true;
		
		genWindow->toggleDebugToDraw();
		
	}
	else if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_RELEASE && keyIsPressedF1 == true)
	{
		this->keyIsPressedF1 = false;
	}

	//Mouse viseble or not
	if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_PRESS && keyIsPressedLControl == false)
	{
		this->keyIsPressedLControl = true;
		this->cameraCanMove = false;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	}
	else if (glfwGetKey(window, GLFW_KEY_LEFT_ALT) == GLFW_RELEASE && keyIsPressedLControl == true)
	{
		this->keyIsPressedLControl = false;
		this->cameraCanMove = true;
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	}


	//new View inputs for walking on terrain
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		camera->moveCameraPosition((camera->getSpeed() * time.deltaTime) * glm::normalize(camera->getLookAtVector()));
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		camera->moveCameraPosition((camera->getSpeed() * time.deltaTime) * glm::normalize(camera->getLookAtVector()) * -1.0f);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		camera->moveCameraPosition((camera->getSpeed() * time.deltaTime) * glm::normalize(glm::cross(camera->getLookAtVector(), camera->getUpVector())) * -1.0f);		
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		camera->moveCameraPosition((camera->getSpeed() * time.deltaTime) * glm::normalize(glm::cross(camera->getLookAtVector(), camera->getUpVector())));												
	}
	
}

bool KeyIn::getCameraShouldMove()const
{
	return cameraCanMove;
}

//void KeyIn::keyInput(GLFWwindow* window, GenWindow* genWindow, Camera& camera, bool &shouldRun)
//{
//	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//	{
//		glfwSetWindowShouldClose(window, true);
//		shouldRun = false;
//	}
//
//	if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_PRESS && keyIsPressedF1 == false)
//	{
//		this->keyIsPressedF1 = true;
//		this->cameraCanMove = false;
//		genWindow->toggleDebugToDraw();
//	}
//	else if (glfwGetKey(window, GLFW_KEY_F1) == GLFW_RELEASE && keyIsPressedF1 == true)
//	{
//		this->keyIsPressedF1 = false;
//		this->cameraCanMove = true;
//	}
//
	//new View inputs for walking on terrain
	//if(cameraCanMove == true)
	//{
	//	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	//	{
	//		camera->moveCameraPosition((camera->getSpeed() * time.deltaTime) * glm::normalize(camera->getLookAtVector()));		//"Normal"-Camera

	//		float height = terrain.getHeightOfTerrain(camera.getPosition().x, camera.getPosition().z);	 //Collect info about terrain height
	//		camera.setHeight(height + 2);																//Place camera 1 unit over the terrain
	//	}
	//	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	//	{
	//		camera->moveCameraPosition((camera->getSpeed() * time.deltaTime) * glm::normalize(camera->getLookAtVector()) * -1.0f);		//"Normal"-Camera

	//		float height = terrain.getHeightOfTerrain(camera.getPosition().x, camera.getPosition().z);	 //Collect info about terrain height
	//		camera.setHeight(height + 2);																//Place camera 1 unit over the terrain
	//	}
	//	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	//	{
	//		camera->moveCameraPosition((camera->getSpeed() * time.deltaTime) * glm::normalize(glm::cross(camera->getLookAtVector(), camera->getUpVector())) * -1.0f);								 //"Normal"-Camera

	//		float height = terrain.getHeightOfTerrain(camera.getPosition().x, camera.getPosition().z);	 //Collect info about terrain height
	//		camera.setHeight(height + 2);																//Place camera 1 unit over the terrain
	//	}
	//	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	//	{
	//		camera->moveCameraPosition((camera->getSpeed() * time.deltaTime) * glm::normalize(glm::cross(camera->getLookAtVector(), camera->getUpVector())));								 //"Normal"-Camera

	//		float height = terrain.getHeightOfTerrain(camera.getPosition().x, camera.getPosition().z);	 //Collect info about terrain height
	//		camera.setHeight(height + 2);																//Place camera 1 unit over the terrain
	//	}
	//}
//	
//}