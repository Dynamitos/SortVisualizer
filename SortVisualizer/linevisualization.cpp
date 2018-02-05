#include "linevisualization.h"

LineVisualization::LineVisualization(int numElements)
	: Visualization(numElements)
{
	values = new float[numElements];
	data = new float[numElements];
	history = new float[numElements * SIZE_HISTORY];
}

LineVisualization::~LineVisualization()
{
	delete values;
	delete history;
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &historyBuffer);
	glDeleteVertexArrays(1, &vaoID);
	glDetachShader(programID, vertShader);
	glDetachShader(programID, fragShader);
	glDeleteProgram(programID);
}

void LineVisualization::init(int delay)
{
	Visualization::init(delay);
	display->createWindow();
	glewExperimental = true;
	if (glewInit())
		std::cout << "Error glew" << std::endl;

	glClearColor(0, 0, 0, 1);
	
	memcpy(values, data, sizeData * sizeof(float));

	glGenVertexArrays(1, &vaoID);
	glBindVertexArray(vaoID);
	glGenBuffers(1, &vertexBuffer);
	float vertices[SIZE_HISTORY * 2];
	for (int i = 0; i < SIZE_HISTORY; ++i)
	{
		vertices[i * 2 + 0] = 2.f / (SIZE_HISTORY-1.f) * i - 1.f;
		vertices[i * 2 + 1] = -1.f;
	}
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SIZE_HISTORY * 2, vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);

	/*glGenBuffers(1, &historyBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, historyBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * SIZE_HISTORY * sizeData, history, GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 1, GL_FLOAT, false, 0, nullptr);
	
	glGenBuffers(1, &valueBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, valueBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeData, data, GL_STATIC_DRAW);
	glVertexAttribPointer(2, 1, GL_FLOAT, false, 0, nullptr);
	*/
	glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	//glVertexAttribDivisor(0, 0);
	//glVertexAttribDivisor(1, 1);
	//glVertexAttribDivisor(2, 0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glLineWidth(5);
	programID = glCreateProgram();
	vertShader = loadShader("line.vert", GL_VERTEX_SHADER);
	fragShader = loadShader("line.frag", GL_FRAGMENT_SHADER);

	glAttachShader(programID, vertShader);
	glAttachShader(programID, fragShader);
	glLinkProgram(programID);
	glValidateProgram(programID);

	glUseProgram(programID);

	location_history = glGetUniformLocation(programID, "transform");
	location_data = glGetUniformLocation(programID, "data");
}

void LineVisualization::loop()
{
	startSort();
	while (!display->shouldClose())
	{
		for (int i = 0; i < sizeData; ++i)
		{
			for (int j = 0; j < sizeData; ++j)
			{
				if (values[i] == data[j])
				{
//					memcpy(&history[i * SIZE_HISTORY + 1], &history[i * SIZE_HISTORY], sizeof(float) * (SIZE_HISTORY - 1));
					for (int k = SIZE_HISTORY - 1; k > 0; --k)
					{
						history[i * SIZE_HISTORY + k] = history[i * SIZE_HISTORY + k - 1];
					}
					history[i * SIZE_HISTORY] = 2.f * (float)j / sizeData;
					break;
				}
			}
		}
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(vaoID);
		glUseProgram(programID);
		//glBindBuffer(GL_ARRAY_BUFFER, historyBuffer);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sizeData * SIZE_HISTORY, nullptr, GL_DYNAMIC_DRAW);
		//glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * sizeData * SIZE_HISTORY, history);

		for (int i = 0; i < sizeData; ++i) {
			glUniform1f(location_data, values[i]);
			glUniform1fv(location_history, SIZE_HISTORY, &history[i * SIZE_HISTORY]);
			glDrawArrays(GL_LINE_STRIP, 0, SIZE_HISTORY);
		}
		glBindVertexArray(0);
		display->updateWindow();
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}
	waitSort();
}
