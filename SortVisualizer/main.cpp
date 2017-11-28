#include <GL\glew.h>
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <cmath>

#include "vulkancolumnvisualization.h"
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
#include "insertionsort.h"
#include "mergesort.h"
#include "cyclesort.h"
#include <openoptimize\asmutil.h>


int main(int argc, char* argv[])
{
	Visualization* renderer = new VulkanColumnVisualization(100000);
	CycleSort sort;
	renderer->init(0);
	renderer->setAlgorithm(&sort);
	renderer->loop();
	delete renderer;
	return 0;
}