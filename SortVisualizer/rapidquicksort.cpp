#include "rapidquicksort.h"

RapidQuickSort::RapidQuickSort(bool mt, bool assembly, int delay)
	: SortAlgorithm(mt, assembly, delay)
{
    this->name = "Rapid quick sort";
}

void RapidQuickSort::sort(float* data, int size)
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

void RapidQuickSort::insertionSort(float* data, int left, int right)
{
    float helper;
	for (int i = left + 1; i < right; ++i)
	{
		for (int j = i; j > left && data[j - 1] > data[j]; --j)
		{
	        asmswap(&data[j], &data[j - 1]);
		}
	}
}

void RapidQuickSort::quicksort(float* arr, int left, int right)
{
	if (right - left < 20)
	{
        //insertionSort(arr, left, right);
        asminsertionsort(&arr[left], right-left+1, 0);
		return;
	}
	int index;
	if (useAssembly) {
		index = asmpartition(arr, left, right);
	}
	else {
		index = partition(arr, left, right);
	}
	if (left < index - 1)
		quicksort(arr, left, index - 1);

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
		swap(&arr[left], &arr[right]);
	}
	if (arr[mid] < arr[left])
	{
		swap(&arr[left], &arr[mid]);
	}
	if (arr[right] < arr[mid])
	{
		swap(&arr[mid], &arr[right]);
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
			swap(&arr[i], &arr[j]);
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