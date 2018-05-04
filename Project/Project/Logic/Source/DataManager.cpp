#include "..\header\DataManager.h"

DataManager::DataManager()
{
	this->dataHolder = new Array<DataHolder*>();
	this->data = new std::map<std::string, float>();
}

DataManager::~DataManager()
{
	delete this->dataHolder;
	delete this->data;
}

void DataManager::addDataHolder(DataHolder * dataHolder)
{
}

void DataManager::collectData()
{
}

void DataManager::showData()
{
}

void DataManager::addData(std::string name, float value)
{
}

void DataManager::incrementData(std::string name, float value)
{
}

float DataManager::getData(std::string name)
{
	return 0.0f;
}
