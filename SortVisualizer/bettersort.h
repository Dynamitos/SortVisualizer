#pragma once
#include "sortalgorithm.h"
struct Partition 
{
	int position;
	int size;
};
class BetterSort : public SortAlgorithm
{
public:
	virtual void sort(std::vector<float>& data, int delay);
private:
	void quicksort(std::vector<float>& arr, int left, int right);
	int partition(std::vector<float>& arr, int left, int right);
	void mergeSort(std::vector<float>& arr, std::vector<Partition> partitions);
	void mergePartitions(Partition leftPart, Partition rightPart, std::vector<float>::iterator result);
};