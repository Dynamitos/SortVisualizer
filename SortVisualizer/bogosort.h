#pragma once
#include "selectionsort.h"

class BogoSort : public SortAlgorithm
{
public:
	virtual void sort(std::vector<float>& data, int delay);
};