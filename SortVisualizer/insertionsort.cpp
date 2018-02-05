#include "insertionsort.h"

InsertionSort::InsertionSort()
{
	this->name = "Insertion Sort";
}

void InsertionSort::sort(float data[], int size, int intDelay)
{
	printf("\n");
	if (useAssembly)
	{
		asminsertionsort(data, size, intDelay);
	}
	else
	{
		for (int i = 1; i < size; ++i)
		{
			for (int j = i; j > 0 && data[j - 1] > data[j]; --j)
			{
				asmswap(&data[j], &data[j - 1]);
			}
		}
	}
}
