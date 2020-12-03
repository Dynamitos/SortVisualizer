#pragma once
#include "sortalgorithm.h"

class CycleSort : public SortAlgorithm
{
public:
	CycleSort(bool mt, bool assembly, int delay);
	void sort(float data[], int size);
};