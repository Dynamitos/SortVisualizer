#include <GL\glew.h>
#include "renderer.h"
#include "selectionsort.h"
#include "bogosort.h"
#include "bubblesort.h"
#include "radixsort.h"
#include "bettersort.h"
#include "stdsort.h"
#include "quicksort.h"
#include "mergesort.h"

int main(int argc, char* argv[])
{
	Renderer renderer(1000000);
	RadixSort sort;
	renderer.init(0);
	renderer.setAlgorithm(&sort);
	renderer.loop();

	return 0;
}