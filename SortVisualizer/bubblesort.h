#pragma once
#include "sortalgorithm.h"

class BubbleSort : public SortAlgorithm
{
public:
	BubbleSort();
	virtual void sort(std::vector<float>& data);
};