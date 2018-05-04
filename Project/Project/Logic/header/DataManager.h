#ifndef DATAMANAGER_H
#define DATAMANAGER_H
#include "DataHolder.h"
#include <iostream>
#include <map>

class DataManager
{
private:
	Array<DataHolder*>* dataHolder;
	std::map<std::string, float>* data;

public:
	DataManager();
	~DataManager();
	void addDataHolder(DataHolder* dataHolder);
	void collectData();
	void showData();
	void addData(std::string name, float value);
	void incrementData(std::string name, float value);
	float getData(std::string name);
};
#endif