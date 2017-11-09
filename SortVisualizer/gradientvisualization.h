#pragma once
#include "visualization.h"

class GradientVisualization : public Visualization
{
public:
	GradientVisualization(int numElements);
	void init();
private:
	int vaoID;
	int vertexBuffer;
	int valueBuffer;
};