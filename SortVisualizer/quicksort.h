#pragma once
#include "sortalgorithm.h"

class QuickSort : public SortAlgorithm
{
public:
	QuickSort();
	virtual void sort(float data[], int size, int intDelay);
private:
	void quicksort(float* arr, int left, int right);
	int partition(float* arr, int left, int right);
};