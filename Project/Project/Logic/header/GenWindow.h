#ifndef GENWINDOW_H
#define GENWINDOW_H

#include "../../imgui/imgui.h"
#include "../../Defines.h"
#include "Array.h"
#include <string>
#include <iostream>
#include"../../LogicDefines.h"

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
	int perlinCalls;				//ammount of Perlin Calls
	int sizeX;
	int sizeY;
	int mainRoads;					//ammount of Main Roads
	int smallRoads;					//ammount of Small Roads
	int buildings[MAX_DISTRICTS];	//house, skyscraper, factory
	int grass[MAX_DISTRICTS];		//Total ammount of Grass Tiles in a District
	unsigned int seed;						//Perlin Noise generation seed in integer form
	float genTime;					//Total ammount of time to generate

	char inputBuf[256] = "";
	int tSizeX;
	int tSizeY;
	float pSizeX;
	float pSizeY;
	Array<float> octave;
	Array<float> amplitude;
	float redistribution;
	float borderPerc;
	int minHeight[MAX_DISTRICTS];
	int maxHeight[MAX_DISTRICTS];
	int density[MAX_DISTRICTS];
	int blockSize[MAX_DISTRICTS];
	int minMainRoadDistance;
	int count;
	bool generate = false;
	bool random = false;
	bool randBuild = false;
	bool randDistrict = false;
	bool performance = false;

public:
	GenWindow();
	~GenWindow();
	void draw();
	void randomiser();
	void toggleDebugToDraw() { this->isDrawing = !this->isDrawing; }
	std::string getInputBuf() { return this->inputBuf; }
	bool isOpen() const { return this->isDrawing; }
	float getPSizeX() { return this->pSizeX; }
	float getPSizeY() { return this->pSizeY; }
	int getTSizeX() { return this->tSizeX; }
	int getTSizeY() { return this->tSizeY; }
	Array<float> getTerrainOctave() { return this->octave; }
	Array<float> getTerrainOctavePerc() { return this->amplitude; }
	float getRedistribution() { return this->redistribution; }
	float getBorderPerc() { return this->borderPerc; }
	int* getMinHeight() { return this->minHeight; }
	int* getMaxHeight() { return this->maxHeight; }
	int* getDensity() { return this->density; }
	int* getBlockSize() { return this->blockSize; }
	int getMinMainRoadDist() { return this->minMainRoadDistance; }
	void setSeed(unsigned int seed) { this->seed = seed; }
	void setCounter(int count) { this->count = count; }
	int getCounter() { return this->count; }
	void setMainRoad(int roads) { this->mainRoads = roads; }
	void setSmallRoad(int roads) { this->smallRoads = roads; }
	void setBuildings(int districts, int building) { this->buildings[districts] = building; }
	void setGrass(int districts, int grass) { this->grass[districts] = grass; }
	void setGenTime(float genTime) { this->genTime = genTime; }
	float getGenTime() { return this->genTime; }
	bool getRandom() { return this->random; }
	bool getRandBuild() { return this->randBuild; }
	bool getRandDistrict() { return this->randDistrict; }
	bool getPerformance() { return this->performance; }
	bool getGenerate() { return this->generate; }
	int getTotalBuildings() { return buildings[0] + buildings[1] + buildings[2]; }
	void toggleGenerate() { this->generate = !this->generate; }
};
#endif