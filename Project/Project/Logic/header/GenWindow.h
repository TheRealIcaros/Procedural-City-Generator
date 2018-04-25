#ifndef GENWINDOW_H
#define GENWINDOW_H

#include "../../imgui/imgui.h"
#include "../../Defines.h"
#include <string>
#include <iostream>

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
	float terrainOctave1;
	float terrainOctave2;
	float terrainOctave3;
	float terrainOctave4;
	float terrainOctave5;
	float terrainOctave6;
	float terrainOctave7;
	float terrainOctave8;
	float terrainOctavePerc1;
	float terrainOctavePerc2;
	float terrainOctavePerc3;
	float terrainOctavePerc4;
	float terrainOctavePerc5;
	float terrainOctavePerc6;
	float terrainOctavePerc7;
	float terrainOctavePerc8;
	float redistribution;
	int houseMinHeight;
	int houseMaxHeight;
	int houseDensity;
	int houseBlockSize;
	int skyscraperMinHeight;
	int skyscraperMaxHeight;
	int skyscraperDensity;
	int skyscraperBlockSize;
	int factoriesMinHeight;
	int factoriesMaxHeight;
	int factoriesDensity;
	int factoriesBlockSize;
	int count;
	bool generate = false;

public:
	GenWindow();
	~GenWindow();
	void draw();
	void toggleDebugToDraw() { this->isDrawing = !this->isDrawing; }
	std::string getInputBuf() { return this->inputBuf; }
	bool isOpen() const { return this->isDrawing; }
	int getTSizeX() { return this->tSizeX; }
	int getTSizeY() { return this->tSizeY; }
	float getTerrainOctave1() { return this->terrainOctave1; }
	float getTerrainOctave2() { return this->terrainOctave2; }
	float getTerrainOctave3() { return this->terrainOctave3; }
	float getTerrainOctave4() { return this->terrainOctave4; }
	float getTerrainOctave5() { return this->terrainOctave5; }
	float getTerrainOctave6() { return this->terrainOctave6; }
	float getTerrainOctave7() { return this->terrainOctave7; }
	float getTerrainOctave8() { return this->terrainOctave8; }
	float getTerrainOctavePerc1() { return this->terrainOctavePerc1; }
	float getTerrainOctavePerc2() { return this->terrainOctavePerc2; }
	float getTerrainOctavePerc3() { return this->terrainOctavePerc3; }
	float getTerrainOctavePerc4() { return this->terrainOctavePerc4; }
	float getTerrainOctavePerc5() { return this->terrainOctavePerc5; }
	float getTerrainOctavePerc6() { return this->terrainOctavePerc6; }
	float getTerrainOctavePerc7() { return this->terrainOctavePerc7; }
	float getTerrainOctavePerc8() { return this->terrainOctavePerc8; }
	float getRedistribution() { return this->redistribution; }
	void setSeed(int seed) { this->seed = seed; }
	void setCounter(int count) { this->count = count; }
	bool getGenerate() { return this->generate; }
	void toggleGenerate() { this->generate = !this->generate; }
};
#endif