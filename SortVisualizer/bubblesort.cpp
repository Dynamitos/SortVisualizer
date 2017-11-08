#include "bubblesort.h"

BubbleSort::BubbleSort()
{
}

void BubbleSort::sort(std::vector<float>& data, int delay)
{
	int flag = 1;
	float helper;
	for (int i = 0; (i <= data.size()) && flag; ++i)
	{
		flag = 0;
		//first data is 1 for center
		for (int j = 1; j < (data.size() - 1 - i); ++j)
		{
			if (data[j + 1] < data[j])
			{
				//std::iter_swap(data.begin() + j, data.begin() + j + 1);
				helper = data[j];
				data[j] = data[j + 1];
				data[j + 1] = helper;
				flag = 1;
			}
		}
        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
}
