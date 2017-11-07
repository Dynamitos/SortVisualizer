#include "renderer.h"

Renderer::Renderer(int numValues)
	: algo(nullptr)
	, display(nullptr)
	, numValues(numValues)
{
	data.resize(numValues);
}

Renderer::~Renderer()
{
}

void Renderer::setAlgorithm(SortAlgorithm * algo)
{
}

void Renderer::start()
{
	display = new Display();
	display->createWindow();
	glewExperimental = true;
	if (glewInit())
		std::cout << "Error glew" << std::endl;
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vertBuffer);
	glGenBuffers(1, &valueBuffer);
	

	for (int i = 0; i < data.size(); i++)
	{
		data[i] = i;
	}
	std::random_shuffle(data.begin(), data.end());
	vertices.resize(data.size() * 2 + 2);
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;
	for (int i = 0; i < numValues; ++i)
	{
		vertices[i * 2 + 2] = sin((float)i/numValues*360.f);
		vertices[i * 2 + 3] = cos((float)i/numValues*360.f);
	}

	glBindVertexArray(vaoID);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, nullptr);
	
	glBindBuffer(GL_ARRAY_BUFFER, valueBuffer);
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_DYNAMIC_DRAW);
	glVertexAttribPointer(1, 1, GL_FLOAT, false, 0, nullptr);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	GLuint vertShader = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	program = glCreateProgram();
	glUseProgram(program);

	const char* vertCode = "#version 450\n \
		layout(location = 0) in vec2 verts_VS_in;\n \
		layout(location = 1) in float data_VS_in;\n \
		layout(location = 0) out float data_FS_out;\n \
        void main(){\n \
			gl_Position = vec4(verts_VS_in, 0, 1);\n \
			data_FS_out = data_VS_in;\n \
		}\n \
		";

	GLint shaderLength = sizeof(vertCode);
	glShaderSource(vertShader, 1, &vertCode, &shaderLength);
	glCompileShader(vertShader);

	const char* fragCode = "#version 450\n \
		layout(location = 0) in float data_FS_out;\n \
		layout(location = 0) out vec4 color;\n \
        void main(){\n \
			color = vec4(data_FS_in, 0, 0, 1);\n \
		}\n \
		";
	
	shaderLength = sizeof(fragCode);
	glShaderSource(fragShader, 1, &fragCode, &shaderLength);
	glCompileShader(fragShader);
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);
	glValidateProgram(program);

	
}
