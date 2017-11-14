#pragma once
#include "sortalgorithm.h"
class SelectionSort : public SortAlgorithm
{
public:
    SelectionSort();
	virtual void sort(float data[], int size, int intDelay);
};