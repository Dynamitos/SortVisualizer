#include "columnvisualization.h"

ColumnVisualization::ColumnVisualization(int numElements)
	: Visualization{ numElements }
{
	data = new float[numElements];
	sizeData = numElements;
}

ColumnVisualization::~ColumnVisualization()
{
	delete data;
	delete vertices;
}

void ColumnVisualization::init(int delay)
{
	Visualization::init(delay);
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &positionBuffer);
	glGenBuffers(1, &valueBuffer);

	float width = 2.f / sizeData;
	vertices = new float[8]
	{
		-width/2.f, 1.f,
		width/2.f, 1.f,
		-width/2.f, -1.f,
		width/2.f, -1.f
	};

	positions = new float[sizeData];
#pragma loop(hint_parallel(0))
	for (int i = 0; i < sizeData; ++i)
	{
		positions[i] = -1.f + i*width;
	}

	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeData * sizeof(float), positions, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 1, GL_FLOAT, false, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, valueBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeData * sizeof(float), data, GL_STREAM_DRAW);
	glVertexAttribPointer(2, 1, GL_FLOAT, false, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glVertexAttribDivisor(0, 0);
	glVertexAttribDivisor(1, 1);
	glVertexAttribDivisor(2, 1);
	glBindVertexArray(0);

	programID = glCreateProgram();
	vertShader = loadShader("column.vert", GL_VERTEX_SHADER);
	fragShader = loadShader("column.frag", GL_FRAGMENT_SHADER);

	glAttachShader(programID, vertShader);
	glAttachShader(programID, fragShader);
	glLinkProgram(programID);
	glValidateProgram(programID);
}

void ColumnVisualization::loop()
{
	startSort();
	while (!display->shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(vaoID);
		glUseProgram(programID);
		glBindBuffer(GL_ARRAY_BUFFER, valueBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeData * sizeof(float), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeData * sizeof(float), data);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
		glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 4, sizeData);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glDisableVertexAttribArray(2);
		glUseProgram(0);
		glBindVertexArray(0);
		display->updateWindow();
	}
	waitSort();
}
