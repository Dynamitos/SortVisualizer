#include "benchmark.h"



Benchmark::Benchmark(int delay, std::vector<SortAlgorithm*> sortAlgorithms)
{
    this->sortAlgorithms = sortAlgorithms;

    GlobalMemoryStatusEx(&memoryStatus);
}


Benchmark::~Benchmark()
{
    delete currSortingData;
}


void Benchmark::setDelay(int intDelay)
{
    benchmarkMutex.lock();

    for (auto it = sortAlgorithms.begin(); it != sortAlgorithms.end(); it++)
    {
        //TODO:
        //(*it)->setDelay(intDelay);
    }

    benchmarkMutex.unlock();
}

void Benchmark::setCurrentSwapFile(std::string filename)
{
    benchmarkMutex.lock();

    this->swapFilename = filename;
    
    benchmarkMutex.unlock();
}

void Benchmark::addSortingAlgorithm(SortAlgorithm& sa)
{
    benchmarkMutex.lock();

    sortAlgorithms.push_back(&sa);

    benchmarkMutex.unlock();
}

template<typename Datatype>
void Benchmark::generateDataSet(Datatype type, int count)
{
    benchmarkMutex.lock();

    usedCount = count;
    requiredKBytes = (count * sizeof(type)) / 1000;

    currSortingData = new currSortingData[count];y

    benchmarkMutex.unlock();
}


void Benchmark::startBenchmark()
{
    benchmarkMutex.lock();

    int currentCount = usedCount;

    GlobalMemoryStatusEx(&memoryStatus);

    printf("Global memory status...\n\n");
    printf("Total memory: %dKB\n", memoryStatus.ullTotalPhys);
    printf("Available memory: %dKB\n\n\n", memoryStatus.ullAvailPhys);

    usedKBytes = (int)(memoryStatus.ullAvailPhys / 1.5f);
    swappedKBytes = requiredKBytes - usedKBytes;
    if (swappedKBytes < 0)
        swappedKBytes = 0;
    else if (swapFilename == "EMPTY")
    {
        printf("ERROR: Swap file needed but no swap filename given!\n\n");
        return;
    }

    ofSwapStream.open(swapFilename, std::ios_base::out | std::ios_base::binary);



    benchmarkMutex.unlock();
}
