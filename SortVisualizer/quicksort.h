#pragma once
#include "sortalgorithm.h"

class QuickSort : public SortAlgorithm
{
public:
	QuickSort();
	virtual void sort(std::vector<float>& data, int delay);
private:
	void quicksort(std::vector<float>& arr, int left, int right);
	int partition(std::vector<float>& arr, int left, int right);
};