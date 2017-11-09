#include "radixsort.h"

RadixSort::RadixSort()
{
}





void RadixSort::sort2(std::vector<float>& floatData, int delay)
{
    static const int MAX_BYTES_RAM = 3000000000;
    
    const int BITS = 8;

    /*
    4 * floatData.size() * combinations <= MAX_BYTES_RAM
    (MAX_BYTES_RAM / floatData.size()) / 4 <= combinations
    */

    int max_combinations = (MAX_BYTES_RAM / floatData.size()) / 4;
    int required_combinations = 1, bits = 1;

    if (max_combinations / 2 > 256)
        return;

    for (int i = 0, c=1;  i<256;  i++, bits++, c*=2)
    {
        if (c <= max_combinations)
        {
            required_combinations = c;
        }
    }

    int* data = new int[floatData.size()];
    for (int i = 0; i < floatData.size(); i++)
    {
        data[i] = (int)(floatData[i] * 256);
    }

    const int SIZE = required_combinations;
    int* bukkets[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        bukkets[i] = new int[floatData.size()+2];
        bukkets[i][0] = 0;
        bukkets[i][1] = 2;
    }

    int id;
    int max = (1 << 8) - 1;

    for (int bits = (1 << BITS) - 1, r = 0; bits <= max; bits <<= BITS, r += BITS)
    {
        for (int i = 0; i<floatData.size(); i++)
        {
            id = data[i] & bits;
            id >>= r;

            bukkets[id][bukkets[i][1]] = data[i];
            bukkets[id][bukkets[i][1]] = bukkets[id][bukkets[i][1]] + 1;
        }

        for (int i = 0, j = 0; i<floatData.size(); j++)
        {
            int* &al = bukkets[j];
            int size = al[0] + 1;

            for (int x = 1; x<size; x++, i++)
            {
                data[i] = al[x];
            }

            al[0] = 0;
            al[1] = 2;
        }

        for (int i = 0; i < floatData.size(); i++)
        {
            floatData[i] = (float)data[i] / 256;
        }
    }
}



void RadixSort::sort(std::vector<float>& floatData, int delay)
{
	static const int BITS = 8;

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
