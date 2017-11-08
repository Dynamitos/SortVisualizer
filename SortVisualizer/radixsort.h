#pragma once
#include "sortalgorithm.h"
class RadixSort : public SortAlgorithm
{
public:
	virtual void sort(std::vector<float>& data, float delay);
};