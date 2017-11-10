#include "gradientvisualization.h"

GradientVisualization::GradientVisualization(int numElements)
	: Visualization(numElements)
{
}

GradientVisualization::~GradientVisualization()
{
	delete vertices;
}

void GradientVisualization::init(int delay)
{
	Visualization::init(delay);

	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vertexBuffer);
	glGenBuffers(1, &valueBuffer);

	vertices = new float[sizeGPU * 2];
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;

#pragma loop(hint_parallel(0))
	for (int i = 0; i < sizeGPU - 1; ++i)
	{
		float angle = 2 * 3.141592653f * i / sizeData;
		vertices[i * 2 + 2] = cos(angle);
		vertices[i * 2 + 3] = sin(angle);
	}
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeGPU * 2 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, valueBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeGPU * sizeof(float), gpuData, GL_STREAM_DRAW);
	glVertexAttribPointer(1, 1, GL_FLOAT, false, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	programID = glCreateProgram();
	vertShader = loadShader("gradient.vert", GL_VERTEX_SHADER);
	fragShader = loadShader("gradient.frag", GL_FRAGMENT_SHADER);

	glAttachShader(programID, vertShader);
	glAttachShader(programID, fragShader);
	glLinkProgram(programID);
	glValidateProgram(programID);
}

void GradientVisualization::loop()
{
	startSort();
	while (!display->shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(vaoID);
		glUseProgram(programID);
		glBindBuffer(GL_ARRAY_BUFFER, valueBuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeGPU * sizeof(float), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, sizeGPU * sizeof(float), gpuData);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_TRIANGLE_FAN, 0, sizeGPU);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glUseProgram(0);
		glBindVertexArray(0);
		display->updateWindow();
	}
	display->closeWindow();
	waitSort();
}
