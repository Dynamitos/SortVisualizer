#pragma once
#include <fstream>
#include "sortalgorithm.h"
#include "display.h"
class Visualization
{
public:
	Visualization(int numElements);
	virtual void init();
	void setAlgorithm(SortAlgorithm* algorithm);
	virtual void loop() = 0;
	void startSort();
	void waitSort();
protected:
	int numElements;
	float* data;
	float* gpuData;
	Display* display;
	SortAlgorithm* algorithm;
	GLuint loadShader(std::string filename, GLenum shaderType);
private:
	std::thread sorter;
};