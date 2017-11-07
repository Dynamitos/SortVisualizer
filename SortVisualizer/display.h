#pragma once
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>
class Display
{
public:
	Display(int width = 1280, int height = 720);
	virtual ~Display();
	void createWindow();
	void updateWindow();
	void closeWindow();
private:
	GLFWwindow* window;
	int width, height;
public:
	bool shouldClose();
};