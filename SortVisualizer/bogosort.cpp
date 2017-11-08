#include "bogosort.h"

void BogoSort::sort(std::vector<float>& data, int delay)
{
	bool sorted = false;
	while (!sorted)
	{
		std::random_shuffle(data.begin(), data.end());

		sorted = true;
		for (int i = 1; i < data.size() - 1; ++i)
		{
			if (data[i] > data[i + 1])
			{
				sorted = false;
				break;
			}
		}
	}
}
