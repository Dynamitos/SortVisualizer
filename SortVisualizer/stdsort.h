#pragma once
#include "sortalgorithm.h"
class StdSort : public SortAlgorithm
{
public:
	virtual void sort(std::vector<float>& data, int delay);
};