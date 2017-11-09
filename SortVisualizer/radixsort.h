#pragma once
#include "sortalgorithm.h"


class RadixSort : public SortAlgorithm
{
public:
    RadixSort();
	virtual void sort(float data[], int size, int intDelay);
    virtual void sort2(float data[], int size, int intDelay);
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