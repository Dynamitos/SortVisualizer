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
#include "slowsort.h"
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
		("slowsort", "Slow sort, a pessimistic multiply-and-surrender approach")
		("stdsort", "qsort() algorithm used by the c++ standard library");
	options.add_options("Visualizations")
		("g,gradient", "Gradient Visualization. An ellipse as base, every array entry is a vertex and the value of a vertex is represented by it's HSV hue value, with the sorted array being the 2D HSV colorspace", cxxopts::value<bool>(g))
		("c,column", "Column Visualization. Every array entry is represented by a column, with the height of the column representing it's value. The sorted array has the lower left part of the screen white and the rest black", cxxopts::value<bool>(c))
		("l,line", "Line Visualization. Every value is represented by a line, with the color of the line being its HSV hue value. The path of the line represents it's path through the array", cxxopts::value<bool>(l));
	options.add_options("Misc")
		("d,delay", "Specifies the delay after each array operation in milliseconds, does not work with assembly code", cxxopts::value<int>(delay))
		("a,assembly", "Use this to toggle assembly usage whenever possible", cxxopts::value<bool>(a))
		("m,multithread", "Use this to toggle usage of multithreading whenever possible", cxxopts::value<bool>(mt))
		("v,vulkan", "Use this to toggle usage of Vulkan for rendering whenever possible", cxxopts::value<bool>(vulkan))
		("n,elements", "Specifies the number of elements to sort", cxxopts::value<int>(number))
		("h,help", "Show this page");
}

CommandParser::~CommandParser()
{
}

void CommandParser::parseCommandLine(int argc, char * argv[])
{
	auto result = options.parse(argc, argv);

	if (result["h"].as<bool>())
	{
		std::cout << options.help({"Sorting Algorithms", "Visualizations", "Misc" }) << std::endl;
		exit(0);
	}

	if (result["bogosort"].as<bool>())
	{
		algorithm = new BogoSort();
	}
	else if (result["bubblesort"].as<bool>())
	{
		algorithm = new BubbleSort();
	}
	else if (result["cyclesort"].as<bool>())
	{
		algorithm = new CycleSort();
	}
	else if (result["insertionsort"].as<bool>())
	{
		algorithm = new InsertionSort();
	}
	else if (result["mergesort"].as<bool>())
	{
		algorithm = new MergeSort();
	}
	else if (result["quicksort"].as<bool>())
	{
		algorithm = new QuickSort();
	}
	else if (result["radixsort"].as<bool>())
	{
		algorithm = new RadixSort();
	}
	else if (result["rapidquicksort"].as<bool>())
	{
		algorithm = new RapidQuickSort();
	}
	else if (result["selectionsort"].as<bool>())
	{
		algorithm = new SelectionSort();
	}
	else if (result["slowsort"].as<bool>())
	{
		algorithm = new SlowSort();
	}
	else if (result["stdsort"].as<bool>())
	{
		algorithm = new StdSort();
	}
	algorithm->intDelay = delay;
	algorithm->useAssembly = a;
	algorithm->useMultithreading = mt;
	if (vulkan)
	{
		if (g)
		{
			visualization = new VulkanGradientVisualization(number);
		}
		else if (c)
		{
			visualization = new VulkanColumnVisualization(number);
		}
		else if (l)
		{
			visualization = new LineVisualization(number);
		}
	}
	else
	{
		if (g)
		{
			visualization = new GradientVisualization(number);
		}
		else if (c)
		{
			visualization = new ColumnVisualization(number);
		}
		else if (l)
		{
			visualization = new LineVisualization(number);
		}
	}
}
