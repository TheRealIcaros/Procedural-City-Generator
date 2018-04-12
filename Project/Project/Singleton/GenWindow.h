#ifndef GENWINDOW_H
#define GENWINDOW_H

#include "../Imgui/imgui.h"
#include "../Defines.h"

#pragma region Comment
/*
Class: genWindow
Description:
This class creates the window containing all parameters for the generation process, it also includes the trigger to begin a generation
*/
#pragma endregion Description of class

class GenWindow
{
private:
	bool isDrawing = false;
public:
	GenWindow();
	~GenWindow();
	static GenWindow* getInstance();
	static void releaseInstance();
	void draw();
	void toggleDebugToDraw() { isDrawing = !isDrawing; }
	bool isOpen() const { return isDrawing; }
};
#endif