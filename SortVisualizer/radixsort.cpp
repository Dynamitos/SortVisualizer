#include "radixsort.h"

RadixSort::RadixSort()
{
}

void RadixSort::sort(std::vector<float>& floatData, int delay)
{
	static const int BITS = 4;

    int* data = new int[floatData.size()];
    for (int i = 0; i < floatData.size(); i++)
    {
        data[i] = (int)(floatData[i] * 256);
    }

    const int SIZE = 1 << BITS;
    std::vector<int> bukkets[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        bukkets[i] = std::vector<int>();
        bukkets[i].push_back(0);
    }

    int id;
    int max = (1 << 8) - 1;

    for (int bits = (1 << BITS) - 1, r = 0; bits <= max; bits <<= BITS, r += BITS)
    {
        for (int i = 0; i<floatData.size(); i++)
        {
            id = data[i] & bits;
            id >>= r;

            bukkets[id].push_back(data[i]);
            bukkets[id][0] = bukkets[id][0] + 1;
        }

        for (int i = 0, j = 0; i<floatData.size(); j++)
        {
            std::vector<int> &al = bukkets[j];
            int size = al[0] + 1;

            for (int x = 1; x<size; x++, i++)
            {
                data[i] = al[x];
            }

            al.clear();
            al.push_back(0);
        }

        for (int i = 0; i < floatData.size(); i++)
        {
            floatData[i] = (float)data[i] / 256;
        }
    }
}
