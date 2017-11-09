#pragma once

#include <vector>
#include <cmath>
#include <stdio.h>

#include "sortalgorithm.h"


class MergeSort : public SortAlgorithm
{
public:
    MergeSort();
    virtual void sort(float data[], int size, int intDelay);

private:
    void recursiveSort(float* sortedData, float* readData, int start, int end);
    void merge(float* sortedData, float* readData, int leftStart, int right, int leftEnd, int rightEnd);
};

