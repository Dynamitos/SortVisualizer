#include "stdsort.h"

void StdSort::sort(std::vector<float>& data, int delay)
{
	std::sort(data.begin() + 1, data.end());
}
