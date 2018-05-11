#ifndef GENWINDOW_H
#define GENWINDOW_H

#include "../Imgui/imgui.h"
#include "../Defines.h"
#include <string>
//#include <iostream>;

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

	char m_inputBuf[256] = "";
	int tSizeX = 25;
	int tSizeY = 25;
	float terrainOctave1 = 1.0;
	float terrainOctave2 = 1.0;
	float terrainOctave3 = 1.0;
	float terrainOctavePerc1 = 0.50;
	float terrainOctavePerc2 = 0.35;
	float terrainOctavePerc3 = 0.15;
	float redistribution = 1.0;
	int houseMinHeight = 1;
	int houseMaxHeight = 2;
	int houseDensity = 100;
	int houseBlockSize = 2;
	int skyscraperMinHeight = 1;
	int skyscraperMaxHeight = 2;
	int skyscraperDensity = 100;
	int skyscraperBlockSize = 2;
	int factoriesMinHeight = 1;
	int factoriesMaxHeight = 2;
	int factoriesDensity = 100;
	int factoriesBlockSize = 2;
	bool generate = false;

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