#include "bogosort.h"
#include <atomic>

BogoSort::BogoSort(bool mt, bool assembly, int delay)
	: SortAlgorithm(mt, assembly, delay)
{
	this->name = "Bogo sort";
}
std::mutex mutex;
std::atomic_bool sorted = false;
int32_t sortedThreadIndex = -1;
void BogoSort::sort(float* data, int size)
{
	uint32_t numThreads = useMultithreading ? std::thread::hardware_concurrency() : 1;
	float** threadData = new float* [numThreads];
	threadData[0] = data;
	for (int i = 1; i < numThreads; ++i)
	{
		threadData[i] = new float[size];
		std::memcpy(threadData[i], data, sizeof(float) * size);
	}
	std::vector<std::thread> threads(numThreads);

	auto runLambda = [this, threadData, size](int threadIndex, bool useAssembly) {
		bool localSorted = false;
		while (!localSorted && !sorted)
		{
			int randomIndex = 0;
			for (int i = 0; i < size; i++)
			{
				randomIndex = rand() % size;
				swap(&threadData[threadIndex][i], &threadData[threadIndex][randomIndex]);
			}
			localSorted = true;
			for (int i = 0; i < size - 1; ++i)
			{
				if (threadData[threadIndex][i] > threadData[threadIndex][i + 1])
				{
					localSorted = false;
					break;
				}
			}
		}
		if (!localSorted)
			return;
		{
			std::unique_lock<std::mutex> lock(mutex);
			sorted.store(true);
			sortedThreadIndex = threadIndex;
		}
	};
	for (int i = 0; i < numThreads; ++i)
	{
		threads[i] = std::thread(runLambda, i, useAssembly);
	}
	for (int i = 0; i < numThreads; ++i)
	{
		threads[i].join();
	}
	threads.clear();
	std::memcpy(data, threadData[sortedThreadIndex], sizeof(float) * size);
	for (int i = 1; i < numThreads; ++i)
	{
		delete threadData[i];
	}
}