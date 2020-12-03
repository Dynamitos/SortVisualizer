#pragma once
#include "sortalgorithm.h"


class RadixSort : public SortAlgorithm
{
public:
    RadixSort(bool mt, bool assembly, int delay);
	virtual void sort(float data[], int size);
    virtual void sort2(float data[], int size);
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