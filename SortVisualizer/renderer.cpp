#include "renderer.h"

Renderer::Renderer(int numValues)
	: algo(nullptr)
	, display(nullptr)
	, numValues(numValues)
{
	data.resize(numValues + 2);
}

Renderer::~Renderer()
{
}

void Renderer::setAlgorithm(SortAlgorithm * algo)
{
	this->algo = algo;
}

void Renderer::init()
{
	display = new Display();
	display->createWindow();
	glewExperimental = true;
	if (glewInit())
		std::cout << "Error glew" << std::endl;
	
	glClearColor(1, 1, 0, 1);

	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vertBuffer);
	glGenBuffers(1, &valueBuffer);
	
	data[0] = 1.f;
	for (int i = 1; i < data.size(); i++)
	{
		data[i] = i / (float)data.size();
	}
	std::random_shuffle(data.begin() + 1, data.end());
	vertices.resize(data.size() * 2 + 4);
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;

	for (int i = 0; i < numValues + 1; ++i)
	{
		float angle = 2 * 3.141592653f * i / numValues;
		vertices[i * 2 + 2] = cos(angle);
		vertices[i * 2 + 3] = sin(angle);
	}
	

	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);
	
	glBindBuffer(GL_ARRAY_BUFFER, valueBuffer);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STREAM_DRAW);
	glVertexAttribPointer(1, 1, GL_FLOAT, false, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	program = glCreateProgram();

	const char vertCode[] = "\n#version 410 \n \
		layout(location = 0) in vec2 verts_VS_in; \n \
		layout(location = 1) in float data_VS_in; \n \
		layout(location = 0) out float data_FS_out; \n \
        void main(){\n  \
			gl_Position = vec4(verts_VS_in, 0, 1); \n \
			data_FS_out = data_VS_in; \n \
		} \n \
		";

	GLint shaderLength = sizeof(vertCode);
	const GLchar* pointer = &vertCode[0];
	glShaderSource(vertShader, 1, &pointer, &shaderLength);
	glCompileShader(vertShader);

	const char fragCode[] = "#version 410\n \
		layout(location = 0) in float data_FS_in;\n \
		layout(location = 0) out vec4 color;\n \
        void main(){\n \
			color = vec4(data_FS_in, 0, 0.f, 1.f);\n \
		}\n \
		";
	
	shaderLength = sizeof(fragCode);
	pointer = &fragCode[0];
	glShaderSource(fragShader, 1, &pointer, &shaderLength);
	glCompileShader(fragShader);
	
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);
	glValidateProgram(program);
}

void Renderer::loop()
{
	std::thread sorter([this] { algo->sort(data); });
	while (!display->shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(vaoID);
		glUseProgram(program);
		glBindBuffer(GL_ARRAY_BUFFER, valueBuffer);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, 0, data.size() * sizeof(float), data.data());
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size()/2);
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);
		glUseProgram(0);
		glBindVertexArray(0);
		display->updateWindow();
	}
	display->closeWindow();
	sorter.join();
}
