//Includes
#include "Graphic\header\Program.h"
#include <crtdbg.h>

//3D-math
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>



int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
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