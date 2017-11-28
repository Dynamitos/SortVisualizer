#include "cyclesort.h"

CycleSort::CycleSort()
{
	this->name = "Cycle Sort";
}

void CycleSort::sort(float data[], int size, int intDelay)
{
	int writes = 0;

	for (int cycleStart = 0; cycleStart < size - 1; ++cycleStart)
	{
		float item = data[cycleStart];

		int pos = cycleStart;
		for (int i = cycleStart + 1; i < size; ++i)
		{
			if (data[i] < item)
			{
				pos++;
			}
		}
		if(pos == cycleStart)
			continue;

		while (item == data[pos])
		{
			pos++;
		}
		asmswap(&data[pos], &item);
		writes++;
		while (pos != cycleStart)
		{
			pos = cycleStart;
			for (int i = cycleStart + 1; i < size; ++i)
			{
				if (data[i] < item)
				{
					pos++;
				}
			}
			while (item == data[pos])
			{
				pos++;
			}
			asmswap(&data[pos], &item);
			writes++;
		}
	}
	std::cout << "Writes: " << writes << std::endl;
}
