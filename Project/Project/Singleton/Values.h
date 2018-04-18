#pragma once

class Values
{
private:
	char inputBuf[256] = "";
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
	Values();
	~Values();
	static Values* getInstance();
	static void releaseInstance();
	char * getInputBufPTR() { return inputBuf; }
	int* getTSizeXPTR() { return &tSizeX; }
	int* getTSizeYPTR() { return &tSizeY; }
	float* getTerrainOctavePTR1() { return &terrainOctave1; }
	float* getTerrainOctavePTR2() { return &terrainOctave2; }
	float* getTerrainOctavePTR3() { return &terrainOctave3; }
	float* getTerrainOctavePercPTR1() { return &terrainOctavePerc1; }
	float* getTerrainOctavePercPTR2() { return &terrainOctavePerc2; }
	float* getTerrainOctavePercPTR3() { return &terrainOctavePerc3; }


};