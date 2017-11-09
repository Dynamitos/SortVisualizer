#include "radixsort.h"

RadixSort::RadixSort()
{
}





void RadixSort::sort(std::vector<float>& floatData, int delay)
{
    static const int MAX_BYTES_RAM = 2100000000;

    if (MAX_BYTES_RAM / 4 < floatData.size())
        return;
    
    /*
    4 * floatData.size() * combinations <= MAX_BYTES_RAM
    (MAX_BYTES_RAM / floatData.size()) / 4 <= combinations
    
    int max_combinations = (MAX_BYTES_RAM / floatData.size()) / 4;
    int required_combinations = 1, BITS = 0;

    for (int c=2;  c<=max_combinations && c<=256;  c<<=1, BITS++)
    {
        required_combinations = c;
    }

    std::cout << "Required combinations: " << required_combinations << " required bits: " << BITS << std::endl;


    int* data = new int[floatData.size()];
    for (int i = 0; i < floatData.size(); i++)
    {
        data[i] = (int)(floatData[i] * 256);
    }

    const int SIZE = required_combinations;
    int** bukkets = new int*[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        bukkets[i] = new int[floatData.size()+1];
        // curr position
        bukkets[i][0] = 1;
    }

    int id;
    int max = (1 << 8) - 1;

    for (int bits = (1 << BITS) - 1, r = 0; bits <= max; bits <<= BITS, r += BITS)
    {
        for (int i = 0; i<floatData.size(); i++)
        {
            id = data[i] & bits;
            id >>= r;

            bukkets[id][bukkets[id][0]] = data[i];
            bukkets[id][0] = bukkets[id][0] + 1;
        }

        for (int i = 0, j = 0; i<floatData.size(); j++)
        {
            int* &al = bukkets[j];
            int size = al[0];

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
	}*/

}



void RadixSort::sort2(std::vector<float>& floatData, int delay)
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
