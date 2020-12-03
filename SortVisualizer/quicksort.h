#pragma once
#include "sortalgorithm.h"

class QuickSort : public SortAlgorithm
{
public:
	QuickSort(bool mt, bool assembly, int delay);
	virtual void sort(float data[], int size);
private:
	void quicksort(float* arr, int left, int right);
	int partition(float* arr, int left, int right);
};