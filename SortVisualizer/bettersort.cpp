#include "bettersort.h"

void BetterSort::sort(std::vector<float>& data, int delay)
{
	std::vector<std::thread> threads;
	threads.resize(std::thread::hardware_concurrency());
	
	std::vector<Partition> partitions;
	partitions.push_back(Partition(data.data(), 0, data.size() - 1));
	std::vector<Partition> newPartitions;
	while (partitions.size() < threads.size())
	{
		for (auto& part : partitions)
		{
			divideData(newPartitions, part);
			if (newPartitions.size() == threads.size())
			{
				break;
			}
		}
		partitions = newPartitions;
	}

	int dataPerThread = data.size() / threads.size();
	for (int i = 0; i < threads.size(); ++i)
	{
		threads[i] = std::thread(&BetterSort::quicksort, this, partitions[i].arr, partitions[i].left, partitions[i].right);
	}
	for (auto& t : threads)
	{
		t.join();
	}
	//merge(data, threads.size());
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
void BetterSort::divideData(std::vector<Partition>& parts, Partition & part)
{
	int middle = partition(part.arr, part.left, part.right);
	parts.push_back(Partition(part.arr, middle, part.right));
	part.right = middle - 1;
	parts.push_back(part);
}
/*
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
	float min;
	int bestPos;
	for (int i = 0; i < arr.size(); ++i)
	{
		min = partitions[0].get();
		bestPos = 0;
		for (int j = 1; j < partitions.size(); ++j)
		{
			if (partitions[j].get() < min)
			{
				min = partitions[j].get();
				bestPos = j;
			}
		}
		arr[i] = min;
		std::cout << min << std::endl;
		partitions[bestPos].increment();
		//std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
}
*/