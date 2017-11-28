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
#include <openoptimize\asmutil.h>


int main(int argc, char* argv[])
{
    //asmtests();
    //return 0;

    Visualization* renderer = new GradientVisualization(100000);
	BubbleSort sort;
	renderer->init(0);
	renderer->setAlgorithm(&sort);
	renderer->loop();
	delete renderer;
	system("PAUSE");
	return 0;
}