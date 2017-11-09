#include "visualization.h"

Visualization::Visualization(int numElements)
{
	this->sizeData = numElements;
	sizeGPU = numElements + 2;
	gpuData = new float[sizeGPU];
	gpuData[0] = 0.f;
	gpuData[sizeGPU - 1] = 1.f;
	data = &gpuData[1];
}

Visualization::~Visualization()
{
	delete gpuData;
}

void Visualization::init(int delay)
{
	this->delay = delay;
	display = new Display();
	display->createWindow();

	glewExperimental = true;
	if (glewInit())
		std::cout << "Error glew" << std::endl;

	glClearColor(0, 0, 0, 1);

#pragma loop(hint_parallel(0))
	for (int i = 0; i < sizeData; i++)
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
	sorter = std::thread([=]
	{
		auto start = std::chrono::high_resolution_clock::now();
		algorithm->sort(data, sizeData, delay);
		auto end = std::chrono::high_resolution_clock::now();
		float runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::cout << "Runtime: " << runtime << "ms" << std::endl;
	});
}

void Visualization::waitSort()
{
	sorter.join();
}

GLuint Visualization::loadShader(std::string filename, GLenum shaderType)
{
	std::ifstream file(filename, std::ios::in | std::ios::ate);
	if (!file.is_open())
	{
		throw std::runtime_error("failed to open file!");
	}
    std::streampos fileSize = file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();

	GLuint shaderID = glCreateShader(shaderType);
	const GLchar* pointer = buffer.data();
	GLint shaderLength = fileSize;
	glShaderSource(shaderID, 1, &pointer, &shaderLength);
	glCompileShader(shaderID);
	return shaderID;
}
