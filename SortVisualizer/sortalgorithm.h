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
    SortAlgorithm(bool mt, bool assembly, int delay)
        : useMultithreading(mt)
        , useAssembly(assembly)
        , intDelay(delay)
    {}
	virtual void sort(float data[], int size) = 0;
    std::string getName() { return name; }
    
    inline void swap(float* left, float* right) const
    {
        if (useAssembly)
        {
            asmswap(left, right);
        }
        else
        {
            float tmp = *left;
            *left = *right;
            *right = tmp;
        }

        if (intDelay > 0)
        {
            std::this_thread::sleep_for(std::chrono::microseconds(intDelay));
        }
    }
protected:
    int intDelay;
	const bool useMultithreading;
	const bool useAssembly;
    std::string name;

	friend class CommandParser;
};