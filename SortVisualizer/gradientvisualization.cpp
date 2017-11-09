#include "gradientvisualization.h"

GradientVisualization::GradientVisualization(int numElements)
	: Visualization(numElements)
{
}

void GradientVisualization::init()
{
	float* vertices = new float[numElements * 2 + 4];
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;

#pragma loop(hint_parallel(8))
	for (int i = 0; i < numElements + 1; ++i)
	{
		float angle = 2 * 3.141592653f * i / numElements;
		vertices[i * 2 + 2] = cos(angle);
		vertices[i * 2 + 3] = sin(angle);
	}
	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, (numElements * 2 + 4) * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);

	glBindBuffer(GL_ARRAY_BUFFER, valueBuffer);
	glBufferData(GL_ARRAY_BUFFER, (numElements + 2) * sizeof(float), gpuData, GL_STREAM_DRAW);
	glVertexAttribPointer(1, 1, GL_FLOAT, false, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}
