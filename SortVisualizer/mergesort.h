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
    void recursiveSort(std::vector<float>& sortedData, std::vector<float>& readData, int start, int end);
};

