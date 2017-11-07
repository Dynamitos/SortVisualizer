#include <GL\glew.h>
#include "renderer.h"
#include "selectionsort.h"

int main(int argc, char* argv[])
{
	Renderer* renderer = new Renderer(100);
	SortAlgorithm* bubbleSort = new SelectionSort();
	renderer->init();
	renderer->setAlgorithm(bubbleSort);
	renderer->loop();
	delete renderer;
	return 0;
}