#pragma once
#include "sortalgorithm.h"
class RadixSort : public SortAlgorithm
{
public:
    RadixSort();
	virtual void sort(std::vector<float>& data, int delay);
};