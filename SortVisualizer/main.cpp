#include <GL\glew.h>
#include "renderer.h"

int main(int argc, char* argv[])
{
	Renderer* renderer = new Renderer(10000);
	renderer->start();
	delete renderer;
	return 0;
}