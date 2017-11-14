#include "display.h"

Display::Display(int width, int height)
	:width(width), height(height)
{
}

Display::~Display()
{
}

void Display::createWindow(bool noContext)
{
	this->noContext = noContext;
    if (!glfwInit())
        std::cout << "Error initing glfw" << std::endl;

    glfwWindowHint(GLFW_SAMPLES, 4);
	if (noContext)
	{
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
	}
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    window = glfwCreateWindow(width, height, "Sort Visualizer", NULL, NULL);
    if (!window)
        std::cout << "ERROROROROROROROR" << std::endl;

    glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE) glfwSetWindowShouldClose(window, GLFW_TRUE); });

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
		//std::cout << "Frametime: " << 1000.0f / (double)nbFrames << "ms" << std::endl;
		nbFrames = 0;
	}
	if (!noContext)
	{
		glfwSwapBuffers(window);
	}
}

void Display::closeWindow()
{
	glfwTerminate();
}

bool Display::shouldClose()
{
	return glfwWindowShouldClose(window);
}

GLFWwindow * Display::getWindow()
{
	return window;
}

void Display::showWindow()
{
	glfwShowWindow(window);
}
