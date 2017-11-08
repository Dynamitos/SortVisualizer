#include "bettersort.h"

void BetterSort::sort(std::vector<float>& data, int delay)
{
	std::vector<std::thread> threads;
	threads.resize(std::thread::hardware_concurrency());

	int dataPerThread = data.size() / threads.size();
	for (int i = 0; i < threads.size(); ++i)
	{
		threads[i] = std::thread(&BetterSort::quicksort, this, std::ref(data), i * dataPerThread, i * dataPerThread + dataPerThread);
		std::cout << "Thread " << i << " starting " << i*dataPerThread << " ending " << i*dataPerThread + dataPerThread << std::endl;
	}
	for (auto& t : threads)
	{
		t.join();
	}
	merge(data, threads.size());
}

void BetterSort::quicksort(std::vector<float>& arr, int left, int right)
{
	int index = partition(arr, left, right);
	if (left < index - 1)
		quicksort(arr, left, index - 1);
	if (index < right)
		quicksort(arr, index, right);
}

int BetterSort::partition(std::vector<float>& arr, int left, int right)
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

void BetterSort::merge(std::vector<float>& arr, int partitions)
{
	int sizePerPartition = arr.size() / partitions;
	for (int i = 0; i < partitions; ++i)
	{

	}
}

