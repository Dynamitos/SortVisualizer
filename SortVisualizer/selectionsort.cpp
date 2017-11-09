#include "selectionsort.h"

void SelectionSort::sort(std::vector<float>& floats, int delay)
{
	float bestValue;
	int bestPosition;
	float helper;
	float* data = floats.data();
	int size = floats.size();
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
