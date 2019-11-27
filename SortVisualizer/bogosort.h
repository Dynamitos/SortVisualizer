#pragma once
#include "sortalgorithm.h"

class BogoSort : public SortAlgorithm
{
public:
    BogoSort();
	virtual void sort(float data[], int size, int intDelay);
};