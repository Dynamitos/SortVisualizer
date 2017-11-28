#include "rapidquicksort.h"

#define USE_ASSEMBLY 1
#define USE_INSERTION 0

RapidQuickSort::RapidQuickSort()
{
    this->name = "Rapid quick sort";
}


void RapidQuickSort::sort(float* data, int size, int delay)
{
	int numThreads = std::thread::hardware_concurrency();

	std::vector<Partition> partitions;
	partitions.push_back(Partition(data, 0, size - 1));
	while (partitions.size() < numThreads)
	{
		int max = 0;
		for (int i = 1; i < partitions.size(); ++i)
		{
			if (partitions[i].size > partitions[max].size)
			{
				max = i;
			}
		}
		divideData(partitions, max);
	}

	for (int i = 0; i < numThreads; ++i)
	{
		runningThreads.emplace_back(std::thread(&RapidQuickSort::quicksort, this, partitions[i].arr, partitions[i].left, partitions[i].right));
	}
	for (auto& t : runningThreads)
	{
		t.join();
	}
}

void RapidQuickSort::startThread(Partition part, int threadIndex)
{
	quicksort(part.arr, part.left, part.right);
	std::lock_guard<std::mutex> lock(threadLock);
	numAvaliableThreads++;
}

void RapidQuickSort::insertionSort(float* data, int left, int right)
{
	float tmp;
	for (int i = left + 1; i < right; ++i)
	{
		for (int j = i; j > left && data[j - 1] > data[j]; --j)
		{
			tmp = data[j];
			data[j] = data[j - 1];
			data[j - 1] = tmp;
		}
	}
}

void RapidQuickSort::quicksort(float* arr, int left, int right)
{
#if USE_INSERTION == 1
	if (right - left < 10)
	{
		insertionSort(arr, left, right);
		return;
	}
#endif // !USE_INSERTION

#if USE_ASSEMBLY == 1
    int index = asmpartition(arr, left, right);
#else
    int index = partition(arr, left, right);
#endif
	if (left < index - 1)
	{
		if (!numAvaliableThreads)
		{
			quicksort(arr, left, index - 1);
		}
		else
		{
			std::lock_guard<std::mutex> lock(threadLock);
			numAvaliableThreads--;
			runningThreads.push_back(std::thread(&RapidQuickSort::quicksort, this, arr, left, index - 1));
		}
	}
	if (index < right)
		quicksort(arr, index, right);
}

int RapidQuickSort::partition(float* arr, int left, int right)
{
	int i = left, j = right;
	float tmp;
	int mid = (left + right) / 2;
	if (arr[right] < arr[left])
	{
		tmp = arr[left];
		arr[left] = arr[right];
		arr[right] = tmp;
	}
	if (arr[mid] < arr[left])
	{
		tmp = arr[left];
		arr[left] = arr[mid];
		arr[mid] = tmp;
	}
	if (arr[right] < arr[mid])
	{
		tmp = arr[mid];
		arr[mid] = arr[right];
		arr[right] = tmp;
	}
	float pivot = arr[mid];
	while (i <= j)
	{
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;
		if (i <= j)
		{
			tmp = arr[i];
			arr[i] = arr[j];
			arr[j] = tmp;
			i++;
			j--;
		}
	}
	return i;
}

void RapidQuickSort::divideData(std::vector<Partition>& parts, int index)
{
	int middle = asmpartition(parts[index].arr, parts[index].left, parts[index].right);
	parts.push_back(Partition(parts[index].arr, middle, parts[index].right));
	parts[index].right = middle - 1;
	parts[index].size = parts[index].right - parts[index].left;

	std::cout << "Partitioning: " << parts.size() << "/" << std::thread::hardware_concurrency() << std::endl;
}