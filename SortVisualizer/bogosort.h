#pragma once
#include "selectionsort.h"

class BogoSort : public SortAlgorithm
{
public:
    BogoSort();
	virtual void sort(float data[], int size, int intDelay);
};