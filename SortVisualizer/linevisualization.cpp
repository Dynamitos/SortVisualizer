#include "linevisualization.h"

LineVisualization::LineVisualization(int numElements)
	: Visualization(numElements)
{
	lines = new Line[numElements];
	data = new float[numElements];
}

LineVisualization::~LineVisualization()
{
	delete lines;
}

void LineVisualization::init(int delay)
{
	Visualization::init(delay);
	display->createWindow();
	history = new float[sizeData * SIZE_HISTORY];
	for (int i = 0; i < sizeData; ++i)
	{
		lines[i].value = data[i];
		lines[i].history = &history[i * SIZE_HISTORY];
	}
	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	glGenBuffers(1, &vertexBuffer);
	float vertices[SIZE_HISTORY * 2];
	for (int i = 0; i < SIZE_HISTORY; ++i)
	{
		vertices[i * 2 + 0] = 1.f / SIZE_HISTORY * i;
		vertices[i * 2 + 1] = -1.f;
	}
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SIZE_HISTORY * 2, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);

	glGenBuffers(1, &historyBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, historyBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SIZE_HISTORY * sizeData, history, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 1, GL_FLOAT, false, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void LineVisualization::loop()
{
	startSort();
	while (!display->shouldClose())
	{

	}
	waitSort();
}
