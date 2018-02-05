#include "CommandParser.h"
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

CommandParser::CommandParser()
	: options("SortVisualizer", "This is a program to visualize several different sorting algorithms.")
{
	options.add_options("Sorting Algorithms")
		("bogosort", "Bogo Sort, uses random swaps to sort")
		("bubblesort", "Bubble Sort, standard implementation")
		("cyclesort", "Cycle Sort, a sorting algorithm that focuses on reducing number of array access")
		("insertionsort", "Insertion Sort, standard implementation")
		("mergesort", "Merge Sort, standard implementation")
		("quicksort", "Quick Sort, standard implementation")
		("radixsort", "Radix Sort, chooses parameters for maximum performance considering available resources")
		("rapidquicksort", "Quick Sort, multithreaded implementation using Insertion Sort at high recursions")
		("selectionsort", "Selection Sort, standard implementation")
		("stdsort", "qsort() algorithm used by the c++ standard library");
	options.add_options("Visualizations")
		("g,gradient", "Gradient Visualization. An ellipse as base, every array entry is a vertex and the value of a vertex is represented by it's HSV hue value, with the sorted array being the 2D HSV colorspace")
		("c,column", "Column Visualization. Every array entry is represented by a column, with the height of the column representing it's value. The sorted array has the lower left part of the screen white and the rest black")
		("l,line", "Line Visualization. Every value is represented by a line, with the color of the line being its HSV hue value. The path of the line represents it's path through the array");
	options.add_options("Misc")
		("d,delay", "Specifies the delay after each array operation in milliseconds, does not work with assembly code", cxxopts::value<int>(delay))
		("a,assembly", "Use this to toggle assembly usage whenever possible")
		//("m,multithread", "Use this to toggle usage of multithreading whenever possible")
		("v,vulkan", "Use this to toggle usage of Vulkan for rendering whenever possible")
		("n,elements", "Specifies the number of elements to sort", cxxopts::value<int>(number))
		("h,help", "Show this page");
}

CommandParser::~CommandParser()
{
}

void CommandParser::parseCommandLine(int argc, char * argv[])
{
	auto result = options.parse(argc, argv);

	if (result.count("bogosort"))
	{
		algorithm = new BogoSort();
	}
	if (result.count("bubblesort"))
	{
		algorithm = new BubbleSort();
	}
	if (result.count("cyclesort"))
	{
		algorithm = new CycleSort();
	}
	if (result.count("insertionsort"))
	{
		algorithm = new InsertionSort();
	}
	if (result.count("mergesort"))
	{
		algorithm = new MergeSort();
	}
	if (result.count("quicksort"))
	{
		algorithm = new QuickSort();
	}
	if (result.count("radixsort"))
	{
		algorithm = new RadixSort();
	}
	if (result.count("rapidquicksort"))
	{
		algorithm = new RapidQuickSort();
	}
	if (result.count("selectionsort"))
	{
		algorithm = new SelectionSort();
	}
	if (result.count("stdsort"))
	{
		algorithm = new StdSort();
	}
	algorithm->useAssembly = a;
	algorithm->useMultithreading = mt;
	if (result.count("v"))
	{
		if (result.count("g"))
		{
			visualization = new VulkanGradientVisualization(number);
		}
		if (result.count("c"))
		{
			visualization = new VulkanColumnVisualization(number);
		}
		if (result.count("l"))
		{
			visualization = new LineVisualization(number);
		}
	}
	else
	{
		if (result.count("g"))
		{
			visualization = new GradientVisualization(number);
		}
		if (result.count("c"))
		{
			visualization = new ColumnVisualization(number);
		}
		if (result.count("l"))
		{
			visualization = new LineVisualization(number);
		}
	}
}
