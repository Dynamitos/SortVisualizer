#pragma once
#include "sortalgorithm.h"
class BetterSort : public SortAlgorithm
{
public:
	virtual void sort(std::vector<float>& data, int delay);
private:
	void quicksort(std::vector<float>& arr, int left, int right);
	int partition(std::vector<float>& arr, int left, int right);
	void merge(std::vector<float>& arr, int partitions);
};