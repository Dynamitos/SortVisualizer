#pragma once
#include "sortalgorithm.h"

class SlowSort : public SortAlgorithm
{
public:
	SlowSort();
	virtual void sort(float data[], int size, int intDelay);
private:
	void slowsort(float data[], int i, int j);
};