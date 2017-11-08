#include <GL\glew.h>
#include "renderer.h"
#include "selectionsort.h"
#include "bubblesort.h"

int main(int argc, char* argv[])
{
	Renderer* renderer = new Renderer(10000);
	SortAlgorithm* bubbleSort = new BubbleSort();
	renderer->init();
	renderer->setAlgorithm(bubbleSort);
	renderer->loop();
	delete renderer;
	return 0;
}