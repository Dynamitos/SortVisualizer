#pragma once
#include "sortalgorithm.h"
class SelectionSort : public SortAlgorithm
{
public:
    SelectionSort(bool mt, bool assembly, int delay);
	virtual void sort(float data[], int size);
};