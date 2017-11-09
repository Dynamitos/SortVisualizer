#include "bogosort.h"

void BogoSort::sort(float* data, int size, int delay)
{
	bool sorted = false;
	while (!sorted)
	{
		//std::random_shuffle(data.begin(), data.end());

		sorted = true;
#pragma loop(hint_parallel(8))
		for (int i = 1; i < size - 1; ++i)
		{
			if (data[i] > data[i + 1])
			{
				sorted = false;
				break;
			}
		}
	}
}
