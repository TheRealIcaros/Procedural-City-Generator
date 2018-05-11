#ifndef DATAHOLDER_H
#define DATAHOLDER_H
#include "Array.h"

class DataManager;

class DataHolder
{
public:
	DataHolder();
	virtual ~DataHolder();
	virtual void getData(DataManager* dataManager) = 0;
};

#endif