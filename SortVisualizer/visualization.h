#pragma once
#include <fstream>
#include "datamanager.h"
#include "sortalgorithm.h"
#include "display.h"
class Visualization
{
public:
	Visualization(int numElements);
	virtual ~Visualization();
	virtual void init(int delay);
	void setAlgorithm(SortAlgorithm* algorithm);
	virtual void loop() = 0;
	void startSort();
	void waitSort();
protected:
	float* data;
	size_t sizeData;
	Display* display;
	SortAlgorithm* algorithm;
	int delay;
	GLuint loadShader(std::string filename, GLenum shaderType);
private:
	std::thread sorter;
};