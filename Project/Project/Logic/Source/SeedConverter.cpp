#include "..\header\SeedConverter.h"

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

unsigned int SeedConverter::getSeed()
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
}
