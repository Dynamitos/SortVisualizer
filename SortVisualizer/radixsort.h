#pragma once
#include "sortalgorithm.h"


class RadixSort : public SortAlgorithm
{
public:
    RadixSort();
	virtual void sort(std::vector<float>& data, int delay);
};

template <typename T>
class ArrayList
{
public:
    ArrayList();
    ArrayList(int capacity);
    ~ArrayList();

    void add(T t);

private:
    int size, capacity;
};