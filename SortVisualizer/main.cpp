#include <GL\glew.h>
#include "renderer.h"
#include "selectionsort.h"
#include "bogosort.h"
#include "bubblesort.h"
#include "radixsort.h"
#include "stdsort.h"

int main(int argc, char* argv[])
{
	Renderer renderer(10000);
	SelectionSort sort;
	renderer.init(1);
	renderer.setAlgorithm(&sort);
    renderer.loop();
	return 0;
}