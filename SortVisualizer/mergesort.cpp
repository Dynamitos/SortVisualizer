#include "mergesort.h"



MergeSort::MergeSort()
{
}


void MergeSort::sort(std::vector<float>& data, int intDelay)
{
    this->intDelay = intDelay;
    recursiveSort(std::vector<float>(data.size()), data, 0, data.size() - 1);
}




void MergeSort::recursiveSort(std::vector<float>& sortedData, std::vector<float>& readData, int start, int end)
{
    if (start == end)
        return;
    if (end - start == 1)
    {
        floatHelper = readData[start];
        readData[start] = min(readData[start], readData[end]);
        readData[end] = max(floatHelper, readData[end]);
        return;
    }

    int zzz = start + (end - start) / 2;

    recursiveSort(sortedData, readData, start, zzz);
    recursiveSort(sortedData, readData, zzz + 1, end);

    int i = start;
    int j = zzz + 1;

    for (int x = start; x <= end; x++)
    {
        if (i > zzz)
        {
            if (j > end)
                break;
            sortedData[x] = readData[j++];
        }
        else if (j > end)
        {
            if (i > zzz)
                break;
            sortedData[x] = readData[i++];
        }
        else if (readData[j] < readData[i])
            sortedData[x] = readData[j++];
        else
            sortedData[x] = readData[i++];
    }

    memcpy(&(readData[start]), &(sortedData[start]), sizeof(float) * (end - start + 1));
    
    std::this_thread::sleep_for(std::chrono::milliseconds(intDelay));
}






/*std::vector<float> MergeSort::recursiveSort(std::vector<float> data, int start, int end)
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
}*/
