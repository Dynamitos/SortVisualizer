#include "selectionsort.h"


SelectionSort::SelectionSort(bool mt, bool assembly, int delay)
	: SortAlgorithm(mt, assembly, delay)
{
    this->name = "Selection sort";
}

void SelectionSort::sort(float* data, int size)
{
	float bestValue;
	int bestPosition;
	float helper;
	for (int i = 0; i < size - 1; ++i)
	{
		bestValue = data[i];
		bestPosition = i;
		for (int j = i+1; j < size; ++j)
		{
			if (data[j] < bestValue)
			{
				bestValue = data[j];
				bestPosition = j;
			}
		}
		if (bestPosition != i)
		{
			swap(&data[i], &data[bestPosition]);
		}
	}
}
