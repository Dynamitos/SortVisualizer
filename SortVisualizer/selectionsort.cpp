#include "selectionsort.h"


SelectionSort::SelectionSort()
{
    this->name = "Selection sort";
}

void SelectionSort::sort(float* data, int size, int delay)
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
			helper = data[i];
			data[i] = data[bestPosition];
			data[bestPosition] = helper;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
}
