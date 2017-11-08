#pragma once
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
#include <algorithm>
#include <list>
class SortAlgorithm
{
public:
	virtual void sort(std::vector<float>& data, int delay) = 0;
protected:
};