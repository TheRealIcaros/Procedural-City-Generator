#include "..\header\SeedConverter.h"
#include "../../Singleton/Values.h"

SeedConverter::SeedConverter()
{
	this->strSeed = "BLARGH";
	this->convertSeed();
}

SeedConverter::SeedConverter(std::string seed)
{
	this->strSeed = seed;
	this->convertSeed();
}

SeedConverter::~SeedConverter()
{
}

unsigned int SeedConverter::getIntegerSeed()
{
	return this->intSeed;
}

void SeedConverter::setSeed(std::string seed)
{
	this->strSeed = seed;
	this->convertSeed();
	
}

void SeedConverter::convertSeed()
{
	this->intSeed = hash(this->strSeed);
	Values::getInstance()->setSeed(this->intSeed);
}
