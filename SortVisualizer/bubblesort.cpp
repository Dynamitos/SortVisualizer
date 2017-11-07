#include "bubblesort.h"

BubbleSort::BubbleSort()
{
}

void BubbleSort::sort(std::vector<float>& data)
{
	int flag = 1;
	float helper;
	for (int i = 1; (i <= data.size()) && flag; ++i)
	{
		flag = 0;
		//first data is 1 for center
		for (int j = 1; j < (data.size() - 1 - i); ++j)
		{
			if (data[j + 1] < data[j])
			{
				std::iter_swap(data.begin() + j, data.begin() + j + 1);
				flag = 1;
			}
		}
	}
}
