#pragma once
#include <GL\glew.h>
#include <vulkan\vulkan.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <chrono>
class Display
{
public:
	Display(int width = 1920, int height = 1080);
	virtual ~Display();
	void createWindow();
	void updateWindow();
	void closeWindow();
	bool shouldClose();
	GLFWwindow* getWindow();
	int getWidth() { return width; }
	int getHeight() { return height; }
private:
	GLFWwindow* window;
	int width, height;
	int nbFrames;
	double lastTime;
public:
	void showWindow();
};