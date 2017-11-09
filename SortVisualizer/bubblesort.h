#pragma once
#include "sortalgorithm.h"

class BubbleSort : public SortAlgorithm
{
public:
	BubbleSort();
	virtual void sort(float data[], int size, int intDelay);
};