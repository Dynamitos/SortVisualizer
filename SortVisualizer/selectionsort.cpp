#include "selectionsort.h"

void SelectionSort::sort(std::vector<float>& data)
{
	float bestValue;
	int bestPosition;
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
		if(bestPosition != i)
			std::iter_swap(data.begin() + i, data.begin() + bestPosition);
	}
}
