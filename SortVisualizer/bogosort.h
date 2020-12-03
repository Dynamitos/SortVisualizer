#pragma once
#include "sortalgorithm.h"

class BogoSort : public SortAlgorithm
{
public:
    BogoSort(bool mt, bool assembly, int delay);
	virtual void sort(float data[], int size);
};