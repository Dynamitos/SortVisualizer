#pragma once
#include "visualization.h"
const int SIZE_HISTORY = 8;
struct Line
{
	float value;
	int currentIndex;
	float* history;
};
class LineVisualization : public Visualization
{
public:
	LineVisualization(int numElements);
	virtual ~LineVisualization();
	void init(int delay);
	virtual void loop() override;
private:
	float* history;
	GLuint vaoID;
	GLuint vertexBuffer;
	GLuint historyBuffer;
	Line* lines;
};