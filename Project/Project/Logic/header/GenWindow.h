#ifndef GENWINDOW_H
#define GENWINDOW_H

#include "../../imgui/imgui.h"
#include "../../Defines.h"
#include "Array.h"
#include <string>
#include <iostream>

#pragma region Comment
/*
Class: genWindow
Description:
This class creates the window containing all parameters for the generation process, it also includes the trigger to begin a generation
*/
#pragma endregion Description of class
#define octaveNumber 8
class GenWindow
{
private:
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
	int seed;					//Perlin Noise generation seed in integer form
	int genTime;				//Total ammount of time to generate

	char inputBuf[256] = "";
	int tSizeX;
	int tSizeY;
	float pSizeX;
	float pSizeY;
	Array<float> terrainOctave;
	Array<float> terrainOctavePerc;
	float redistribution;
	float borderPerc;
	int houseMinHeight;
	int houseMaxHeight;
	int houseDensity;
	int houseBlockSize;
	int skyscraperMinHeight;
	int skyscraperMaxHeight;
	int skyscraperDensity;
	int skyscraperBlockSize;
	int factorieMinHeight;
	int factorieMaxHeight;
	int factorieDensity;
	int factorieBlockSize;
	int count;
	bool generate = false;

public:
	GenWindow();
	~GenWindow();
	void draw();
	void toggleDebugToDraw() { this->isDrawing = !this->isDrawing; }
	std::string getInputBuf() { return this->inputBuf; }
	bool isOpen() const { return this->isDrawing; }
	int getPSizeX() { return this->pSizeX; }
	int getPSizeY() { return this->pSizeY; }
	int getTSizeX() { return this->tSizeX; }
	int getTSizeY() { return this->tSizeY; }
	Array<float> getTerrainOctave() { return this->terrainOctave; }
	Array<float> getTerrainOctavePerc() { return this->terrainOctavePerc; }
	float getRedistribution() { return this->redistribution; }
	float getBorderPerc() { return this->borderPerc; }
	int getHouseBlockSize() { return this->houseBlockSize; }
	int getSkyscraperBlockSize() { return this->skyscraperBlockSize; }
	int getFactorieBlockSize() { return this->factorieBlockSize; }
	void setSeed(int seed) { this->seed = seed; }
	void setCounter(int count) { this->count = count; }
	void setMainRoad(int roads) { this->mainRoads = roads; }
	void setSmallRoad(int roads) { this->smallRoads = roads; }
	bool getGenerate() { return this->generate; }
	void toggleGenerate() { this->generate = !this->generate; }
};
#endif