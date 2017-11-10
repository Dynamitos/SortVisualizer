#include "rapidquicksort.h"

void RapidQuickSort::sort(float* data, int size, int delay)
{
	int numThreads = std::thread::hardware_concurrency();
	std::thread* threads = new std::thread[numThreads];
	
	std::vector<Partition> partitions;
	partitions.push_back(Partition(data, 0, size - 1));
	std::vector<Partition> newPartitions;
	while (partitions.size() < numThreads)
	{
		for (auto& part : partitions)
		{
			divideData(newPartitions, part);
			if (newPartitions.size() == numThreads)
			{
				break;
			}
		}
		partitions = newPartitions;
	}

	for (int i = 0; i < numThreads; ++i)
	{
		threads[i] = std::thread(&RapidQuickSort::quicksort, this, partitions[i].arr, partitions[i].left, partitions[i].right);
	}
	for (int i = 0; i < numThreads; ++i)
	{
		threads[i].join();
	}
}

void RapidQuickSort::selectionSort(float* data, int left, int right)
{
	float bestValue;
	int bestPosition;
	float helper;
	for (int i = left; i < right; ++i)
	{
		bestValue = data[i];
		bestPosition = i;
		for (int j = i + 1; j < right; ++j)
		{
			if (data[j] < bestValue)
			{
				bestValue = data[j];
				bestPosition = j;
			}
		}
		if (bestPosition != i)
		{
			helper = data[i];
			data[i] = data[bestPosition];
			data[bestPosition] = helper;
		}
	}

}

void RapidQuickSort::quicksort(float* arr, int left, int right)
{
	/*if (right - left < 5)
	{
		selectionSort(arr, left, right);
		return;
	}*/
	int index = partition(arr, left, right);
	if (left < index - 1)
		quicksort(arr, left, index - 1);
	if (index < right)
		quicksort(arr, index, right);
}

int RapidQuickSort::partition(float* arr, int left, int right)
{
	int i = left, j = right;
	float tmp;
	float pivot = arr[(left + right) / 2];
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
void RapidQuickSort::divideData(std::vector<Partition>& parts, Partition & part)
{
	int middle = partition(part.arr, part.left, part.right);
	parts.push_back(Partition(part.arr, middle, part.right));
	part.right = middle - 1;
	parts.push_back(part);
}