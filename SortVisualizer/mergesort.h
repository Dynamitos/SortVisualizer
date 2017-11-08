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
    std::vector<float> recursiveSort(std::vector<float>, int start, int end);
};

