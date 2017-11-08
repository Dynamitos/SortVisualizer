#include "mergesort.h"



MergeSort::MergeSort()
{
}


void MergeSort::sort(std::vector<float>& data, int intDelay)
{
    data = recursiveSort(data, 0, data.size() - 1);
}


std::vector<float> MergeSort::recursiveSort(std::vector<float> data, int start, int end)
{
    if (start == end)
        return std::vector<float>{data[start]};
    else if (end - start == 1)
        return std::vector<float>{std::min(data[start], data[end]), std::max(data[start], data[end])};

    int zzz = start + (end - start) / 2, i = 0, j = 0;
    std::vector<float> leftArray, rightArray;

    leftArray = recursiveSort(data, start, zzz);
    rightArray = recursiveSort(data, zzz + 1, end);

    int length = leftArray.size() + rightArray.size();
    std::vector<float> sortedArray(length);
    for (int x = 0; x < length; x++)
    {
        if (i >= leftArray.size())
        {
            if (j >= rightArray.size())
                break;
            sortedArray[x] = rightArray[j++];
        }
        else if (j >= rightArray.size())
        {
            if (i >= leftArray.size())
                break;
            sortedArray[x] = leftArray[i++];
        }
        else if (rightArray[j] < leftArray[i])
            sortedArray[x] = rightArray[j++];
        else
            sortedArray[x] = leftArray[i++];
    }

    return sortedArray;
}
