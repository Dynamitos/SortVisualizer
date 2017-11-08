#pragma once
#include <algorithm>
#include <cmath>
#include <thread>
#include "sortalgorithm.h"
#include "display.h"
class Renderer
{
public:
	Renderer(int numValues);
	virtual ~Renderer();
	void setAlgorithm(SortAlgorithm* algo);
	void init(float delay);
	void loop();
private:

	SortAlgorithm* algo;
	Display* display;
	std::vector<float> data;
	std::vector<float> vertices;
	GLuint vaoID;
	GLuint vertBuffer;
	GLuint valueBuffer;
	GLuint program;
	float delay;
	int numValues;
};