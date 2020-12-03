#include "slowsort.h"

SlowSort::SlowSort()
{
    this->name = "Slowsort";
}

void SlowSort::sort(float data[], int size, int intDelay)
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
        if (useAssembly)
        {
            asmswap(&data[m], &data[j]);
        }
        else
        {
            float tempFloat = data[m];
            data[m] = data[j];
            data[j] = tempFloat;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(intDelay));
    }
    slowsort(data, i, j - 1);
}
