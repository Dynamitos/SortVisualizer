#include <GL\glew.h>
#include <Windows.h>
#include <iostream>

#include "gradientvisualization.h"
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
    void copyDataf(float* dst, float* src, int size);
}

int main(int argc, char* argv[])
{
    // Test1: Integer test
    int data1[4]{ 1, 2, 3, 4 };
    int data2[4]{ 5, 6, 7, 8 };

    copyData(data1, data2, 16);

    std::cout << data1[0] << " " << data1[1] << " " << data1[2] << " " << data1[3] << std::endl;

    // Test2: Float test
    float dataf1[4]{ 1.1f, 1.2f, 1.3f, 1.4f };
    float dataf2[4]{ 1.5f, 1.6f, 1.7f, 1.8f };

    copyDataf(dataf1, dataf2, 4);

    std::cout << dataf1[0] << " " << dataf1[1] << " " << dataf1[2] << " " << dataf1[3] << std::endl;

    system("PAUSE");

	/*Visualization* renderer = new GradientVisualization(10000000);
	MergeSort sort;
	renderer->init(0);
	renderer->setAlgorithm(&sort);
	renderer->loop();
	delete renderer;
	return 0;*/
}