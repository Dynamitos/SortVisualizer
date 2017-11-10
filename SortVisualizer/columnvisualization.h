#pragma once
#include "visualization.h"

class ColumnVisualization : public Visualization
{
public:
	ColumnVisualization(int numElements);
	virtual ~ColumnVisualization();
	void init(int delay);
	void loop();
private:
	GLuint vaoID;
	GLuint vertexBuffer;
	GLuint positionBuffer;
	GLuint valueBuffer;
	float* vertices;
	float* positions;
	GLint programID;
	GLint vertShader;
	GLint fragShader;
};