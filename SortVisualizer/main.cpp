#include <GL\glew.h>
#include "renderer.h"
#include "selectionsort.h"
#include "bogosort.h"
#include "bubblesort.h"
#include "stdsort.h"

int main(int argc, char* argv[])
{
	Renderer* renderer = new Renderer(10000);
	SortAlgorithm* sort = new BogoSort();
	renderer->init(0);
	renderer->setAlgorithm(sort);
	renderer->loop();
	delete renderer;
	return 0;
}