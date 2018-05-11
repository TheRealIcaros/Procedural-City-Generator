#ifndef SEEDCONVERTER_H
#define SEEDCONVERTER_H
#include <string>

/*
Base Code from: Niclas Ohlsson and Frank Elias for Procedural city generation using Perlin noise
*/

class SeedConverter
{
private:
	unsigned int intSeed;
	std::string strSeed;
	std::hash<std::string> hash;

	void convertSeed();
public:
	SeedConverter();
	SeedConverter(std::string seed);
	~SeedConverter();

	unsigned int getSeed();
	void setSeed(std::string seed);
};
#endif