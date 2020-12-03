#include "bubblesort.h"

BubbleSort::BubbleSort(bool mt, bool assembly, int delay)
	: SortAlgorithm(mt, assembly, delay)
{
    this->name = "Bubble sort";
}

void BubbleSort::sort(float* data, int length)
{
	if (useAssembly)
	{
		asmbubblesort(data, length, intDelay);
	}
	else
	{
		int flag = 1;
		float helper;
		for (int i = 0; (i < length) && flag; ++i)
		{
			flag = 0;
			for (int j = 0; j < (length - 1 - i); ++j)
			{
				if (data[j + 1] < data[j])
				{
					swap(&data[j], &data[j + 1]);
					flag = 1;
				}
			}
		}
	}
}
