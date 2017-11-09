#pragma once
#include "sortalgorithm.h"
struct Partition
{
	Partition(float* arr, int left, int right)
		: arr(arr)
		, left(left)
		, right(right)
	{}
	float* arr;
	int left, right;
};
class BetterSort : public SortAlgorithm
{
public:
	virtual void sort(std::vector<float>& data, int delay);
private:
	void selectionSort(float* data, int left, int right);
	void quicksort(float *data, int left, int right);
	int partition(float* data, int left, int right);
	void divideData(std::vector<Partition>& parts, Partition& part);
	void merge(std::vector<float>& arr, int partitions);
};