#include <GL\glew.h>
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <cmath>

#include "vulkangradientvisualization.h"
#include "vulkancolumnvisualization.h"
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


#define USE_ASSEMBLY 1

extern "C"
{
    void inline asmswap(float* f1, float* f2);
}


int main(int argc, char* argv[])
{

    Visualization* renderer = new VulkanColumnVisualization(100000000);
	RapidQuickSort sort;
	renderer->init(0);
	renderer->setAlgorithm(&sort);
	renderer->loop();
	delete renderer;
	system("PAUSE");
	return 0;
    
}