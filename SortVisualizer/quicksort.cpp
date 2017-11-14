#include "quicksort.h"


QuickSort::QuickSort()
{
}

void QuickSort::sort(float data[], int arraySize, int intDelay)
{
	this->intDelay = intDelay;
	quicksort(data, 0, arraySize - 1);
}

void QuickSort::quicksort(float* arr, int left, int right)
{
    int index = 0;
    index = partition(arr, left, right);
	std::this_thread::sleep_for(std::chrono::milliseconds(intDelay));
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
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}
	return i;
}
