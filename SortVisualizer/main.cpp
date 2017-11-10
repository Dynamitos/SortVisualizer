#include <GL\glew.h>
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <cstdio>

#include "gradientvisualization.h"
#include "columnvisualization.h"
#include "renderer.h"
#include "selectionsort.h"
#include "bogosort.h"
#include "bubblesort.h"
#include "radixsort.h"
#include "rapidquicksort.h"
#include "stdsort.h"
#include "quicksort.h"
#include "mergesort.h"

extern "C"
{
    void copyData(int* dst, int* src, int size);
    //void copyDataf(float* dst, float* src, int size);
}

int main(int argc, char* argv[])
{
	Visualization* renderer = new ColumnVisualization(10000000);
	MergeSort sort;
	renderer->init(0);
	renderer->setAlgorithm(&sort);
	renderer->loop();
	delete renderer;
	return 0;*/
}