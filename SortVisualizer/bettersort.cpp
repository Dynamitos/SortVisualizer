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
	int partitions = threads.size();
	std::vector<Partition> partPos;
	int dataPerPart = data.size() / partitions;
	for (int i = 0; i < partitions; ++i)
	{
		partPos.push_back(Partition{ i * dataPerPart, dataPerPart });
	}
	mergeSort(data, partPos);
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

void BetterSort::mergeSort(std::vector<float>& arr, std::vector<Partition> partitions)
{
	while (partitions.size() > 1) {
		for(int i = 0; i < partitions.size() - 1; i++)
		{
			Partition& left = partitions[i];
			Partition& right = partitions[i + 1];
			mergePartitions(left, right, arr.begin());
			left.size += right.size;
			partitions.erase(partitions.begin() + i + 1);
		}
	}
	
}

void BetterSort::mergePartitions(Partition leftPart, Partition rightPart, std::vector<float>::iterator result)
{
	std::vector<float> left;// (result + leftPart.position, result + leftPart.position + leftPart.size - 1);
	std::vector<float> right;// (result + rightPart.position, result + rightPart.position + rightPart.size - 1);
	
	for (int i = 0; i < leftPart.size; ++i)
	{
		left.push_back(result[leftPart.position + i]);
	}
	for (int i = 0; i < rightPart.size; ++i)
	{
		right.push_back(result[rightPart.position + i]);
	}
	auto l = left.begin(), r = right.begin();
	while (l != left.end() && r != right.end())
	{
		if (*l < *r)
		{
			*result = *l;
			l++;
			result++;
		}
		else
		{
			*result = *r;
			r++;
			result++;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(3));
	}
	while (l != left.end())
	{
		*result = *l;
		l++;
		result++;
	}
	while (r != right.end())
	{
		*result = *r;
		r++;
		result++;
	}
	std::cout << "Merging partition " << leftPart.position << " " << leftPart.size << " with " << rightPart.position << " " << rightPart.size << std::endl;
}