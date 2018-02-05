#include <GL\glew.h>
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <cmath>

#include "vulkancolumnvisualization.h"
#include "vulkangradientvisualization.h"
#include "linevisualization.h"
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
#include "cyclesort.h"
#include "mergesort.h"
#include "insertionsort.h"
#include "commandparser.h"

int main(int argc, char* argv[])
{
	CommandParser* parser = new CommandParser();
	parser->parseCommandLine(argc, argv);
	SortAlgorithm* algo = parser->getAlgorithm();
	Visualization* renderer = parser->getVisualization();
	renderer->init(1000);
	renderer->setAlgorithm(algo);
	renderer->loop();
	delete renderer;
	return 0;
}