#include <GL\glew.h>
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <cmath>

#include "vulkangradientvisualization.h"
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
    void asmswap(float* f1, float* f2);
}


int main(int argc, char* argv[])
{
    float f1 = 1.5f;
    float f2 = 0.5f;
    float helper;

    auto timepoint = std::chrono::high_resolution_clock::now();

    for (unsigned int i = 0; i < 4294967294; i++)
    {
#if USE_ASSEMBLY == 1
        asmswap(&f1, &f2);
#else
        helper = f1;
        f1 = f2;
        f2 = helper;
#endif
    }

    long long duration = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now() - timepoint).count();
    std::cout << f1 << " " << f2 << " it took " << duration << "mcs to complete" << std::endl;

    system("PAUSE");

	/*
    Visualization* renderer = new GradientVisualization(100000);
	BubbleSort sort;
	renderer->init(0);
	renderer->setAlgorithm(&sort);
	renderer->loop();
	delete renderer;
	system("PAUSE");
	return 0;
    */
}