#pragma once
#include "sortalgorithm.h"

class InsertionSort : public SortAlgorithm
{
public:
	InsertionSort(bool mt, bool assembly, int delay);
	virtual void sort(float data[], int size);
};