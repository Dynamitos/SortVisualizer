#include <GL\glew.h>
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

int main(int argc, char* argv[])
{
	Visualization* renderer = new GradientVisualization(10000000);
	MergeSort sort;
	renderer->init(0);
	renderer->setAlgorithm(&sort);
	renderer->loop();
	delete renderer;
	return 0;
}