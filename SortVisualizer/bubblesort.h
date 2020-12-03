#pragma once
#include "sortalgorithm.h"

class BubbleSort : public SortAlgorithm
{
public:
	BubbleSort(bool mt, bool assembly, int delay);
	virtual void sort(float data[], int size);
};