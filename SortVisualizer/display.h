#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <chrono>
class Display
{
public:
	Display(int width = 1280, int height = 720);
	virtual ~Display();
	void createWindow();
	void updateWindow();
	void closeWindow();
	bool shouldClose();
private:
	GLFWwindow* window;
	int width, height;
	int nbFrames;
	double lastTime;
};