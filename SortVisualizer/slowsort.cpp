#include "slowsort.h"

SlowSort::SlowSort(bool mt, bool assembly, int delay)
    : SortAlgorithm(mt, assembly, delay)
{
    this->name = "Slowsort";
}

void SlowSort::sort(float data[], int size)
{
    this->intDelay = intDelay;
    slowsort(data, 0, size);
}

void SlowSort::slowsort(float data[], int i, int j)
{
    if (i >= j)
    {
        return;
    }

    int m = (i + j) / 2;
    
    slowsort(data, i, m);
    slowsort(data, m + 1, j);
    
    if (data[m] > data[j])
    {
        swap(&data[m], &data[j]);
    }
    slowsort(data, i, j - 1);
}
