#pragma once

#include <vector>
#include <cmath>
#include <stdio.h>

#include "sortalgorithm.h"


class MergeSort : public SortAlgorithm
{
public:
    MergeSort(bool mt, bool assembly, int delay);
    virtual void sort(float data[], int size);

private:
    void recursiveSort(float* sortedData, float* readData, int start, int end);
    void merge(float* sortedData, float* readData, int leftStart, int right, int leftEnd, int rightEnd);
};

