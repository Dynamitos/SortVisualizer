#pragma once

#include <vector>
#include <cmath>

#include "sortalgorithm.h"


class MergeSort : public SortAlgorithm
{
public:
    MergeSort();
    virtual void sort(std::vector<float>& data, int intDelay);

private:
    void recursiveSort(float* sortedData, float* readData, int start, int end);
    void merge(float* sortedData, float* readData, int sortStart, int sortEnd, int leftStart, int right, int leftEnd, int rightEnd);
};

