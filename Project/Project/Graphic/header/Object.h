#ifndef OBJECT_H
#define OBJECT_H

//General includes
#include <glad\glad.h>
#include <GLFW\glfw3.h>

//Assimp includes
#include <../assimp/Importer.hpp>
#include <../assimp/scene.h>
#include <../assimp/postprocess.h>

class Object
{
private:
	

	void initiateVariables();

public:
	Object();
	~Object();

	void createT();

	
};

#endif
