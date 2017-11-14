#pragma once
#include <GL\glew.h>
//#include <vulkan\vulkan.h>
#include <GLFW\glfw3.h>
#include <iostream>
#include <chrono>
class Display
{
public:
	Display(int width = 1280, int height = 720);
	virtual ~Display();
	void createWindow(bool noContext = false);
	void updateWindow();
	void closeWindow();
	bool shouldClose();
	GLFWwindow* getWindow();
	int getWidth() { return width; }
	int getHeight() { return height; }
    float getRatio() { return ratio; }
private:
	GLFWwindow* window;
	int width, height;
    float ratio;
	int nbFrames;
	double lastTime;
public:
	void showWindow();
};