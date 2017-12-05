#include "bubblesort.h"

#define USE_ASSEMBLY 1


BubbleSort::BubbleSort()
{
    this->name = "Bubble sort";
}

void BubbleSort::sort(float* data, int length, int delay)
{
#if USE_ASSEMBLY == 1
    asmbubblesort(data, length, delay);
#else
    int flag = 1;
	float helper;
	for (int i = 0; (i < length) && flag; ++i)
	{
		flag = 0;
		for (int j = 0; j < (length - 1 - i); ++j)
		{
			if (data[j + 1] < data[j])
			{
				helper = data[j];
				data[j] = data[j + 1];
				data[j + 1] = helper;
				flag = 1;
				std::this_thread::sleep_for(std::chrono::milliseconds(delay));
			}
		}
	}
#endif
}
