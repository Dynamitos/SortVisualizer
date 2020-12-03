#include "quicksort.h"


QuickSort::QuickSort(bool mt, bool assembly, int delay)
	: SortAlgorithm(mt, assembly, delay)
{
    this->name = "Quick sort";
}

void QuickSort::sort(float data[], int arraySize)
{
	quicksort(data, 0, arraySize - 1);
}

void QuickSort::quicksort(float* arr, int left, int right)
{
    int index = 0;
    index = partition(arr, left, right);
    //index = asmpartition(arr, left, right);
	if (left < index - 1)
		quicksort(arr, left, index - 1);
	if (index < right)
		quicksort(arr, index, right);
}

int QuickSort::partition(float* arr, int left, int right)
{
	int i = left, j = right;
	float tmp;
	float pivot = arr[(left + right) / 2];
	while (i <= j)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j)
		{
			swap(&arr[i], &arr[j]);
			i++;
			j--;
		}
	}
	return i;
}
