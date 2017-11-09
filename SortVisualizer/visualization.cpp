#include "visualization.h"

Visualization::Visualization(int numElements)
{
	this->numElements = numElements;
	gpuData = new float[numElements + 2];
	gpuData[0] = 0.f;
	gpuData[numElements + 1] = 1.f;
	data = &gpuData[1];
}

void Visualization::init()
{
	display = new Display();
	display->createWindow();

	glewExperimental = true;
	if (glewInit())
		std::cout << "Error glew" << std::endl;

	glClearColor(0, 0, 0, 1);

#pragma loop(hint_parallel(8))
	for (int i = 0; i < numElements; i++)
	{
		data[i] = rand() / (float)RAND_MAX;
	}

}

void Visualization::setAlgorithm(SortAlgorithm * algorithm)
{
	this->algorithm = algorithm;
}

void Visualization::startSort()
{
	sorter = std::thread([this]
	{
		auto start = std::chrono::high_resolution_clock::now();
		algorithm->sort(data, delay);
		auto end = std::chrono::high_resolution_clock::now();
		float runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::cout << "Runtime: " << runtime << std::endl;
	});
}

void Visualization::waitSort()
{
	sorter.join();
}

GLuint Visualization::loadShader(std::string filename, GLenum shaderType)
{
	std::ifstream file(filename, std::ios::ate);
	std::vector<char> buffer;

	GLuint shaderID = glCreateShader(shaderType);
}
