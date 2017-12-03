#pragma once
#include "visualization.h"
const int SIZE_HISTORY = 16;

class LineVisualization : public Visualization
{
public:
	LineVisualization(int numElements);
	virtual ~LineVisualization();
	void init(int delay);
	virtual void loop() override;
private:
	GLuint vaoID;
	GLuint vertexBuffer;
	GLuint historyBuffer;
	GLuint valueBuffer;
	GLuint programID;
	GLuint vertShader;
	GLuint fragShader;
	GLint location_history;
	GLint location_data;
	float* values;
	float* history;
};