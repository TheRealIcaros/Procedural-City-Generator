#ifndef GENWINDOW_H
#define GENWINDOW_H

#include "../../imgui/imgui.h"
#include "../../Defines.h"
#include <string>
#include <iostream>
#include "../../Singleton/Values.h"

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
	Values* value;
	bool isDrawing;		
	int perlinCalls;			//ammount of Perlin Calls
	int sizeX;
	int sizeY;
	int mainRoads;				//ammount of Main Roads
	int smallRoads;				//ammount of Small Roads
	int houses;					//ammount of Normal Houses
	int skyscrapers;			//ammount of Skyscrapers
	int factories;				//ammount of Factories
	int totalBuildings;			//Total ammount of Buildings
	int grassD1;				//Total ammount of Grass Tiles in District 1
	int grassD2;				//Total ammount of Grass Tiles in District 2
	int grassD3;				//Total ammount of Grass Tiles in District 3
	int grassTotal;				//Total ammount of Grass Tiles in all Districts
	int intSeed;				//Perlin Noise generation seed in integer form
	int genTime;				//Total ammount of time to generate

public:
	GenWindow();
	~GenWindow();
	void draw();
	void toggleDebugToDraw() { std::cout << "changed"; isDrawing = !isDrawing; }
	bool isOpen() const { return isDrawing; }
};
#endif