#pragma once
#include <vector>
#include <iostream>
#include <chrono>
#include <thread>
class SortAlgorithm
{
public:
	virtual void sort(std::vector<float>& data) = 0;
protected:
};