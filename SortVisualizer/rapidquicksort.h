#pragma once
#include "sortalgorithm.h"
struct Partition
{
	Partition(float* arr, int left, int right)
		: arr(arr)
		, left(left)
		, right(right)
	{
		size = right - left;
	}
	float* arr;
	int left, right;
	int size;
};
class RapidQuickSort : public SortAlgorithm
{
public:
    RapidQuickSort();
	virtual void sort(float data[], int size, int intDelay);
private:
	void insertionSort(float* data, int left, int right);
	void quicksort(float *data, int left, int right);
	int partition(float* data, int left, int right);
	void divideData(std::vector<Partition>& parts, int index);
};