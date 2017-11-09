#pragma once
#include "visualization.h"

class GradientVisualization : public Visualization
{
public:
	GradientVisualization(int numElements);
	virtual ~GradientVisualization();
	void init(int delay);
	void loop();
private:
	GLuint vaoID;
	GLuint vertexBuffer;
	GLuint valueBuffer;
	GLint programID;
	GLint vertShader;
	GLint fragShader;
	float* vertices;
};