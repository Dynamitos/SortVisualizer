#pragma once

#include <list>
#include <string>
#include <fstream>
#include <Windows.h>
#include <mutex>

#include "sortalgorithm.h"


class Benchmark
{
public:
    Benchmark(int delay, std::vector<SortAlgorithm> sortAlgorithms);
    ~Benchmark();
    
    void setDelay(int intDelay);
    void setCurrentSwapFile(std::string filename);

    void addSortingAlgorithm(SortAlgorithm& sa);

    template<typename Datatype>
    void generateDataSet(Datatype type, int count);

    void startBenchmark();

private:
    std::chrono::high_resolution_clock::time_point startPoint;

    std::list<SortAlgorithm> sortAlgorithms;

    SortAlgorithm* currSortAlgorithm;
    float* currSortingData;
    int usedCount, usedKBytes, requiredKBytes, swappedKBytes;
    MEMORYSTATUSEX memoryStatus;

    std::string swapFilename = "EMPTY";
    std::ofstream ofSwapStream;
    std::ifstream ifSwapStream;

    std::mutex benchmarkMutex;
};

