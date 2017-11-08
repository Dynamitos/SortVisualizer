#include "quicksort.h"

QuickSort::QuickSort()
{
}

void QuickSort::sort(std::vector<float>& data, int delay)
{
	/*std::vector<std::thread> threads;
	threads.resize(std::thread::hardware_concurrency() -1);

	int dataPerThread = data.size() / threads.size();
	for (int i = 0; i < threads.size(); ++i)
	{
		threads[i] = std::thread(&QuickSort::quicksort, this, std::ref(data), i * dataPerThread, i * dataPerThread + dataPerThread);//std::thread([=] { quicksort(data, i * dataPerThread, i * dataPerThread + dataPerThread); });
	}
	for (auto& t : threads)
	{
		t.join();
	}*/
	quicksort(data, 1, data.size() - 1);
}

void QuickSort::quicksort(std::vector<float>& arr, int left, int right)
{
	int index = partition(arr, left, right);
	if (left < index - 1)
		quicksort(arr, left, index - 1);
	if (index < right)
		quicksort(arr, index, right);
}

int QuickSort::partition(std::vector<float>& arr, int left, int right)
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
