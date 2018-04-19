#ifndef VALUES_H
#define VALUES_H

#include <iostream>
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
	int count = 0;
	bool generate = false;
	int seed = 0;
public:
	Values();
	~Values();
	static Values* getInstance();
	static void releaseInstance();
	char * getInputBufPTR() { return inputBuf; }
	std::string getInputBuf() { return inputBuf; }
	int* getTSizeXPTR() { return &tSizeX; }
	int* getTSizeYPTR() { return &tSizeY; }
	float* getTerrainOctavePTR1() { return &terrainOctave1; }
	float* getTerrainOctavePTR2() { return &terrainOctave2; }
	float* getTerrainOctavePTR3() { return &terrainOctave3; }
	float* getTerrainOctavePercPTR1() { return &terrainOctavePerc1; }
	float* getTerrainOctavePercPTR2() { return &terrainOctavePerc2; }
	float* getTerrainOctavePercPTR3() { return &terrainOctavePerc3; }
	float* getRedistributionPTR() { return &redistribution; }
	int* getHouseMinHeightPTR() { return &houseMinHeight; }
	int* getHouseMaxHeightPTR() { return &houseMaxHeight; }
	int* getHouseDensityPTR() { return &houseDensity; }
	int* getHouseBlockSizePTR() { return &houseBlockSize; }
	int* getSkyscraperMinHeightPTR() { return &skyscraperMinHeight; }
	int* getSkyscraperMaxHeightPTR() { return &skyscraperMaxHeight; }
	int* getSkyscraperDensityPTR() { return &skyscraperDensity; }
	int* getSkyscraperBlockSizePTR() { return &skyscraperBlockSize; }
	int* getFactoriesMinHeightPTR() { return &factoriesMinHeight; }
	int* getFactoriesMaxHeightPTR() { return &factoriesMaxHeight; }
	int* getFactoriesDensityPTR() { return &factoriesDensity; }
	int* getFactoriesBlockSizePTR() { return &factoriesBlockSize; }

	int getTSizeX() { return tSizeX; }
	int getTSizeY() { return tSizeY; }
	float getTerrainOctave1() { return terrainOctave1; }
	float getTerrainOctave2() { return terrainOctave2; }
	float getTerrainOctave3() { return terrainOctave3; }
	float getTerrainOctavePerc1() { return terrainOctavePerc1; }
	float getTerrainOctavePerc2() { return terrainOctavePerc2; }
	float getTerrainOctavePerc3() { return terrainOctavePerc3; }
	float getRedistribution() { return redistribution; }
	int getHouseMinHeight() { return houseMinHeight; }
	int getHouseMaxHeight() { return houseMaxHeight; }
	int getHouseDensity() { return houseDensity; }
	int getHouseBlockSize() { return houseBlockSize; }
	int getSkyscraperMinHeight() { return skyscraperMinHeight; }
	int getSkyscraperMaxHeight() { return skyscraperMaxHeight; }
	int getSkyscraperDensity() { return skyscraperDensity; }
	int getSkyscraperBlockSize() { return skyscraperBlockSize; }
	int getFactoriesMinHeight() { return factoriesMinHeight; }
	int getFactoriesMaxHeight() { return factoriesMaxHeight; }
	int getFactoriesDensity() { return factoriesDensity; }
	int getFactoriesBlockSize() { return factoriesBlockSize; }

	bool getGenerate() { return generate; }
	void setGenerate(bool gen) { generate = gen; }
	int getCount() { return count; }
	void increaseCount() { count++; }
	int getSeed() { return seed; }
	void setSeed(int s) { seed = s; }
};

#endif