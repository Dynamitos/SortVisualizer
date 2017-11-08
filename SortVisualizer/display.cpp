#include "display.h"

Display::Display(int width, int height)
	:width(width), height(height)
{
}

Display::~Display()
{
}

void Display::createWindow()
{
	if (!glfwInit())
		std::cout << "Error initing glfw" << std::endl;
	
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	glfwSwapInterval(1);

	window = glfwCreateWindow(width, height, "Sort Visualizer", NULL, NULL);
	if (!window)
		std::cout << "ERROROROROROROROR" << std::endl;
	glfwShowWindow(window);
	glfwMakeContextCurrent(window);

	lastTime = glfwGetTime();
}

void Display::updateWindow()
{
	glfwPollEvents();
	nbFrames++;
	double now = glfwGetTime();
	if (now - lastTime >= 1.f)
	{
		lastTime++;
		std::cout << "Frametime: " << 1000.0f / (double)nbFrames << "ms" << std::endl;
		nbFrames = 0;
	}
	glfwSwapBuffers(window);
}

void Display::closeWindow()
{
	glfwTerminate();
}

bool Display::shouldClose()
{
	return glfwWindowShouldClose(window);
}
