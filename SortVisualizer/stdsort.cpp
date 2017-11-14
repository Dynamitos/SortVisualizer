#include "stdsort.h"

StdSort::StdSort()
{
    this->name = "Std sort";
}

void StdSort::sort(float* data, int size, int delay)
{
	std::qsort(data, size, sizeof(float), [](const void* a, const void* b)
	{
		float arg1 = *static_cast<const float*>(a);
		float arg2 = *static_cast<const float*>(b);

		if (arg1 < arg2) return -1;
		if (arg1 > arg2) return 1;
		return 0;

		//  return (arg1 > arg2) - (arg1 < arg2); // possible shortcut
		//  return arg1 - arg2; // erroneous shortcut (fails if INT_MIN is present)
	});
	//std::sort(data.begin(), data.end());
}
