#include "selectionsort.h"

void SelectionSort::sort(std::vector<float>& data, int delay)
{
	float bestValue;
	int bestPosition;
	float helper;
	for (int i = 1; i < data.size() - 1; ++i)
	{
		bestValue = data[i];
		bestPosition = i;
		for (int j = i+1; j < data.size(); ++j)
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
