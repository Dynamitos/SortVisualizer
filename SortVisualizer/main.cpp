#include <GL\glew.h>
#include "renderer.h"
#include "selectionsort.h"
#include "bogosort.h"
#include "bubblesort.h"
#include "stdsort.h"

int main(int argc, char* argv[])
{
	Renderer* renderer = new Renderer(1000000);
	SortAlgorithm* bubbleSort = new StdSort();
	renderer->init(0);
	renderer->setAlgorithm(bubbleSort);
	renderer->loop();
	delete renderer;
	return 0;
}