#include "quicksort.h"

QuickSort::QuickSort()
{
}

void QuickSort::sort(std::vector<float>& data, int delay)
{
	std::vector<std::thread> threads;
	threads.resize(std::thread::hardware_concurrency());

	int dataPerThread = data.size() / threads.size();
	for (int i = 0; i < threads.size(); ++i)
	{
		std::thread& t = threads[i];
		t = std::thread(&quicksort, data.data(), i * dataPerThread, i * dataPerThread + dataPerThread);
	}
	for (auto& t : threads)
	{
		t.join();
	}
}

void QuickSort::quicksort(float arr[], int left, int right)
{
	int index = partition(arr, left, right);
	if (left < index - 1)
		quicksort(arr, left, index - 1);
	if (index < right)
		quicksort(arr, index, right);
}

int QuickSort::partition(float arr[], int left, int right)
{
	int i = left, j = right;
	float tmp;
	float pivot = arr[(left + right) / 2];
	while (i <= j)
	{
		if (arr[i] < pivot)
			i++;
		if (arr[j] > pivot)
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
