#include "mergesort.h"



extern "C"
{
    void memoryCopy(float* dst, float* src, int bytes);
}

/*extern "C"
{
    void memoryIntCopy(int* dst, int* src, int bytes);
}*/

/*extern "C"
{
    void memoryCopy(int* bytes);
}*/

/*void memoryCopy(float& dst, float& src, int bytes)
{
    _asm
    {
       
    }
}*/


MergeSort::MergeSort()
{
}


void MergeSort::sort(std::vector<float>& data, int intDelay)
{
    this->intDelay = intDelay;

    float* floatData = &(data[0]);
    float* sortedData = new float[data.size()];

    float realCount = std::thread::hardware_concurrency();
    int intCount = (int)realCount;
    int blockSize = data.size() / intCount;

    std::thread* threads = new std::thread[intCount];

    if (realCount > intCount)
        intCount--;

    int i, x, y;
    for(i = 0, x = 0, y=blockSize;  i<intCount;  i++, x+=blockSize, y+=blockSize)
    {     
        threads[i] = std::thread(&MergeSort::recursiveSort, this, std::ref(sortedData), std::ref(floatData), x, y-1);
    }

    if(realCount > intCount)
        threads[i] = std::thread(&MergeSort::recursiveSort, this, std::ref(sortedData), std::ref(floatData), x, data.size()-1);


    for (int i = 0; i < intCount; i++)
    {
        threads[i].join();  
    }

    for (int j = 2; j <= intCount; j*=2)
    {       
        int incrementer = j * blockSize;
        for (int i=0, x=0, y=x+((j*blockSize)>>1)+1;  i<intCount;  i+=j, x+=incrementer, y+=incrementer)
        {
            merge(sortedData, floatData, x, y, y-1, x+j*blockSize-1);
        }
    }

    //delete readData;
    //delete threads;
}




void MergeSort::recursiveSort(float* sortedData, float* readData, int start, int end)
{
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
    
    //merge(sortedData, readData, start, j, zzz, end);

    memcpy(&(readData[start]), &(sortedData[start]), sizeof(float) * (diff + 1));

    /*float* test = new float[2]{ 21, 34 };
    //memoryCopy(&(readData[start]), &(sortedData[start]), sizeof(float) * (end - start + 1));
    memoryCopy(test, test, 10);
    std::cout << test[0] << std::endl;
    delete test;

    /*int k = 1, l = 10, m = 100;
    std::vector<int> v1{ 1, 2 };
    std::vector<int> v2{ 3, 4 };

    void* f = &v1;



    mov rax, rcx
    mov rbx, rdx
    mov rcx, r8
    
    copy:
        add QWORD [rax], 1

        dec rcx
        cmp rcx, 0
        jne copy

        

    memoryCopy(f, &v2, m);

    std::cout << "Hello world: " << v1[0] << " " << v1[1] << std::endl;*/


    std::this_thread::sleep_for(std::chrono::nanoseconds(intDelay));
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
