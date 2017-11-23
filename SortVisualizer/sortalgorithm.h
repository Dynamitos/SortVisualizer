#pragma once
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <minmax.h>
#include <string>

#include "asmutil.h"

class SortAlgorithm
{
public:
	virtual void sort(float data[], int size, int intDelay) = 0;
    std::string getName() { return name; }
protected:
    int intHelper, intDelay;
    float floatHelper;
    std::string name;
};