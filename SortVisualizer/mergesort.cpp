#include "mergesort.h"

#define USE_ASSEMBLY 0


MergeSort::MergeSort()
{
    this->name = "Merge sort";
}


void MergeSort::sort(float data[], int size, int intDelay)
{
    this->intDelay = intDelay;

    float* sortedData = new float[size];

	float realCount = std::thread::hardware_concurrency();
    int intCount = (int)realCount;
    int blockSize = size / intCount;

    std::thread* threads = new std::thread[intCount];

    if (realCount > intCount)
        intCount--;

    int i, x, y;
    for(i = 0, x = 0, y=blockSize;  i<intCount;  i++, x+=blockSize, y+=blockSize)
    {     
        threads[i] = std::thread(&MergeSort::recursiveSort, this, std::ref(sortedData), std::ref(data), x, y-1);
    }

    if(realCount > intCount)
        threads[i] = std::thread(&MergeSort::recursiveSort, this, std::ref(sortedData), std::ref(data), x, size-1);

    for (int i = 0; i < intCount; i++)
    {
        threads[i].join();  
    }

    for (int j = 2; j <= intCount; j*=2)
    {       
        int incrementer = j * blockSize;
        for (int i=0, x=0, y=x+((j*blockSize)>>1)+1;  i<intCount;  i+=j, x+=incrementer, y+=incrementer)
        {
#if USE_ASSEMBLY == 1
            asmmerge(sortedData, data, x, y, y - 1, x + j*blockSize - 1);
#else
            merge(sortedData, data, x, y, y-1, x+j*blockSize-1);
#endif
        }
    }

    printf("\n");
}




void MergeSort::recursiveSort(float* sortedData, float* readData, int start, int end)
{
/*#if USE_ASSEMBLY == 2
    asmrecursivesort(sortedData, readData, start, end);
//#else*/
    if (start == end)
        return;
    if (end & start == 1)
    {
        floatHelper = readData[start];
        readData[start] = min(readData[start], readData[end]);
        readData[end] = max(floatHelper, readData[end]);
        return;
    }

    int diff = end - start;
    int zzz = start + (diff >> 1);

    recursiveSort(sortedData, readData, start, zzz);
    recursiveSort(sortedData, readData, zzz + 1, end);

    int i = start;
    int j = zzz + 1;
    
/*#if USE_ASSEMBLY == 1
    asmmerge(sortedData, readData, start, j, zzz, end);
#else*/
    merge(sortedData, readData, start, j, zzz, end);
//#endif

    std::this_thread::sleep_for(std::chrono::nanoseconds(intDelay));
//#endif
}


void MergeSort::merge(float* sortedData, float* readData, int leftStart, int rightStart, int leftEnd, int rightEnd)
{
    int diff = (rightEnd - leftStart) + 1;
    int begin = leftStart;

    for (int x = leftStart; x <= rightEnd; x++)
    {
        if (leftStart > leftEnd)
        {
            if (rightStart > rightEnd)
                break;
            sortedData[x] = readData[rightStart++];
        }
        else if (rightStart > rightEnd)
        {
            if (leftStart > leftEnd)
                break;
            sortedData[x] = readData[leftStart++];
        }
        else if (readData[rightStart] < readData[leftStart])
            sortedData[x] = readData[rightStart++];
        else
            sortedData[x] = readData[leftStart++];
    }
    memcpy(&(readData[begin]), &(sortedData[begin]), sizeof(float) * diff);
}


 



/*void MergeSort::recursiveSort(std::vector<float>& sortedData, std::vector<float>& readData, int start, int end)
{
    if (start == end)
        return;
    if (end & start == 1)
    {
        floatHelper = readData[start];
        readData[start] = std::min(readData[start], readData[end]);
        readData[end] = std::max(floatHelper, readData[end]);
        return;
    }

    int diff = end - start;
    int zzz = start + (diff >> 1);

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

    memcpy(&(readData[start]), &(sortedData[start]), sizeof(float) * (diff + 1));

    //memoryCopy(&(readData[start]), &(sortedData[start]), sizeof(float) * (end - start + 1));

    /*int k = 1, l = 10, m = 100;
    std::vector<int> v1{ 1, 2 };
    std::vector<int> v2{ 3, 4 };

    void* f = &v1;

    memoryCopy(f, &v2, m);

    std::cout << "Hello world: " << v1[0] << " " << v1[1] << std::endl;


    std::this_thread::sleep_for(std::chrono::milliseconds(intDelay));
}*/
