#include <GL\glew.h>
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <cstdio>

#include "gradientvisualization.h"
#include "col"
#include "renderer.h"
#include "selectionsort.h"
#include "bogosort.h"
#include "bubblesort.h"
#include "radixsort.h"
#include "rapidquicksort.h"
#include "stdsort.h"
#include "quicksort.h"
#include "mergesort.h"

int main(int argc, char* argv[])
{
    Visualization* renderer = new ColumnVisualizer(10000000);
    MergeSort sort;
    renderer->init(0);
    renderer->setAlgorithm(&sort);
    renderer->loop();
    delete renderer;
    return 0;

    /*// Test1: Integer test
    const int SIZE = 500000000;
    int* data1 = new int[SIZE];
    int* data2 = new int[SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        data1[i] = i;
    }

    auto timePoint = std::chrono::high_resolution_clock::now();
   
    copyData(data2, data1, SIZE);
    //memcpy(data2, data1, sizeof(int) * SIZE);
    //for (int i = 0; i < SIZE; i++) { data2[i] = data1[i]; }

    long millis = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - timePoint).count();

    for (int i = SIZE-10; i < SIZE; i++)
    {
        printf("%d\n", data2[i]);
    }

    delete data1;
    delete data2;

    std::cout << "It took " << millis << " ms to copy" << std::endl;

    // Test2: Float test
    float dataf1[4]{ 1.1f, 1.2f, 1.3f, 1.4f };
    float dataf2[4]{ 1.5f, 1.6f, 1.7f, 1.8f };

    copyDataf(dataf1, dataf2, 4);

    std::cout << dataf1[0] << " " << dataf1[1] << " " << dataf1[2] << " " << dataf1[3] << std::endl;*/

    system("PAUSE");

	/**/
}