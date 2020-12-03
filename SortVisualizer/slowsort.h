#pragma once
#include "sortalgorithm.h"

class SlowSort : public SortAlgorithm
{
public:
	SlowSort(bool mt, bool assembly, int delay);
	virtual void sort(float data[], int size);
private:
	void slowsort(float data[], int i, int j);
};