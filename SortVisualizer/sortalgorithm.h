#pragma once
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <minmax.h>
#include <mutex>
#include <list>
#include <string>

#include <openoptimize\asmutil.h>

class CommandParser;
class SortAlgorithm
{
public:
	virtual void sort(float data[], int size, int intDelay) = 0;
    std::string getName() { return name; }
    
    void setDelay(int intDelay) { this->intDelay = intDelay; }
protected:
    int intHelper, intDelay;
    float floatHelper;
	bool useMultithreading;
	bool useAssembly;
    std::string name;

	friend class CommandParser;
};