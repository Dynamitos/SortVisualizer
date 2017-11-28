#include "visualization.h"

Visualization::Visualization(int numElements)
{
	this->sizeData = numElements;
	display = new Display();
}

Visualization::~Visualization()
{
}

void Visualization::init(int delay)
{
	this->delay = delay;
	srand(time(NULL));

    
#pragma loop(hint_parallel(0))
	for (int i = 0; i < sizeData; i++)
    {
        //data[i] = i;
        data[i] = rand() / (float)RAND_MAX;
	}
    

    // TESTING
  /*  
#pragma loop(hint_parallel(0))
    for (int i = 0; i < sizeData; i++)
    {
        //data[i] = i;
        data[i] = 1 - ((float)i / sizeData);
    }
    */
}

void Visualization::setAlgorithm(SortAlgorithm * algorithm)
{
	this->algorithm = algorithm;
}

void Visualization::startSort()
{
	sorter = std::thread([=]
	{
//        std::cout << "Start sorting with " << algorithm->getName().c_str() << "..." << std::endl;
		auto start = std::chrono::high_resolution_clock::now();
		algorithm->sort(data, sizeData, delay);
		auto end = std::chrono::high_resolution_clock::now();
		float runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::cout << "Runtime of " << algorithm->getName() << ": " << runtime << "ms" << std::endl;
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


#ifdef NDEBUG
	char log[1000];
	GLint length;
	glGetShaderInfoLog(shaderID, 1000, &length, log);
	std::cout << log << std::endl;
#endif //!NDEBUG
	return shaderID;
}
