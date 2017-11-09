#pragma once
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <minmax.h>
class SortAlgorithm
{
public:
	virtual void sort(float data[], int size, int intDelay) = 0;
protected:
    int intHelper, intDelay;
    float floatHelper;
};