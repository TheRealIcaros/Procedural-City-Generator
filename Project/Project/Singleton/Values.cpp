#include "Values.h"

Values::Values()
{
}

Values::~Values()
{
}

Values * Values::getInstance()
{
	static Values instance;
	return &instance;
}

void Values::releaseInstance()
{
}
