#pragma once
#include "sortalgorithm.h"
class StdSort : public SortAlgorithm
{
public:
    StdSort(bool mt, bool assembly, int delay);
	virtual void sort(float* data, int size);
};