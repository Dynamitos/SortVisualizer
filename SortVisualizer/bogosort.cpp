#include "bogosort.h"

BogoSort::BogoSort()
{
    this->name = "Bogo sort";
}

void BogoSort::sort(float* data, int size, int delay)
{
	bool sorted = false;
	while (!sorted)
	{
        randomShuffle(data, size);

		sorted = true;
#pragma loop(hint_parallel(8))
		for (int i = 0; i < size - 1; ++i)
		{
			if (data[i] > data[i + 1])
			{
				sorted = false;
				break;
			}
		}
	}
}


void BogoSort::randomShuffle(float* data, int size)
{
    int randomIndex = 0;
    for (int i = 0; i < size; i++)
    {
        randomIndex = rand() % size;
        floatHelper = data[i];
        data[i] = data[randomIndex];
        data[randomIndex] = floatHelper;
    }
}
