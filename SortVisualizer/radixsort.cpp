#include "radixsort.h"

RadixSort::RadixSort()
{
}

void RadixSort::sort(std::vector<float>& floatData, int delay)
{
	static const int BITS = 8;

    const int SIZE = 1 << BITS;
    std::vector<int> bukkets[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        bukkets[i] = std::vector<int>();
        bukkets[i].push_back(0);
    }

    int id;
    int max = (1 << 24) - 1;

    for (int bits = (1 << BITS) - 1, r = 0; bits <= max; bits <<= BITS, r += BITS)
    {
        for (int i = 0; i<floatData.size(); i++)
        {
            id = (int)(floatData[i] * 256) & bits;
            id >>= r;

            bukkets[id].push_back(floatData[i]);
            bukkets[id][0] = bukkets[id][0] + 1;
        }

        for (int i = 0, j = 0; i<floatData.size(); j++)
        {
            std::vector<int> &al = bukkets[j];
            int size = al[0] + 1;

            for (int x = 1; x<size; x++, i++)
            {
                floatData[i] = al[x];
            }

            al.clear();
            al.push_back(0);
        }
    }
}
