#include "insertionsort.h"

InsertionSort::InsertionSort(bool mt, bool assembly, int delay)
	: SortAlgorithm(mt, assembly, delay)
{
	this->name = "Insertion Sort";
}

void InsertionSort::sort(float data[], int size)
{
	if (useAssembly)
	{
		asminsertionsort(data, size, intDelay);
	}
	else
	{
		for (int i = 1; i < size; ++i)
		{
			for (int j = i; j > 0 && data[j - 1] > data[j]; --j)
			{
				swap(&data[j], &data[j - 1]);
			}
		}
	}
}
