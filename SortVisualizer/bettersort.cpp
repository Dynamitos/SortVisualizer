#include "bettersort.h"

void BetterSort::sort(std::vector<float>& data, int delay)
{
	/*std::vector<std::thread> threads;
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
	*/
	quicksort(data.data(), 0, data.size() - 1);

}

void BetterSort::selectionSort(float* data, int left, int right)
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

void BetterSort::quicksort(float* arr, int left, int right)
{
	if (right - left < 5)
	{
		selectionSort(arr, left, right);
		return;
	}
	int index = partition(arr, left, right);
	if (left < index - 1)
		quicksort(arr, left, index - 1);
	if (index < right)
		quicksort(arr, index, right);
}

int BetterSort::partition(float* arr, int left, int right)
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

void BetterSort::merge(std::vector<float>& arr, int numParts)
{
	std::vector<float> copy = arr;
	int sizePerPartition = arr.size() / numParts;
	std::vector<Partition> partitions(numParts);
	int position;
	for (int i = 0; i < numParts; ++i)
	{
		position = i * sizePerPartition;
		partitions[i] = Partition(&copy[position], sizePerPartition);
	}
	std::vector<float> values(numParts);
	for (int i = 0; i < values.size(); ++i)
	{
		values[i] = *partitions[i];
	}
	float min;
	int bestPos;
	for (int i = 0; i < arr.size(); ++i)
	{
		min = values[0];
		bestPos = 0;
		for (int j = 1; j < values.size(); ++j)
		{
			if (values[j] < min)
			{
				min = values[j];
				bestPos = j;
			}
		}
		arr[i] = min;
		//std::cout << min << std::endl;
		partitions[bestPos].increment();
		values[bestPos] = *partitions[bestPos];
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}

Partition::Partition()
{
}

Partition::Partition(float * ptr, int size)
	: ptr(ptr)
	, size(size)
	, counter(0)
{
}

void Partition::increment()
{
	if (counter == size)
	{
		*ptr = 1.f;
		return;
	}
	counter++;
	ptr++;
}

float Partition::operator*(void) const
{
	return *ptr;
}
