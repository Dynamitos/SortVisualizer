#pragma once
#include "sortalgorithm.h"
class Partition
{
public:
	Partition();
	Partition(float* ptr, int size);
	void increment();
	float operator*(void) const;
private:
	float* ptr;
	int size;
	int counter;
};
class BetterSort : public SortAlgorithm
{
public:
	virtual void sort(std::vector<float>& data, int delay);
private:
	void selectionSort(float* data, int left, int right);
	void quicksort(float *data, int left, int right);
	int partition(float* data, int left, int right);
	void merge(std::vector<float>& arr, int partitions);
};