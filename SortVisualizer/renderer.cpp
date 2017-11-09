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

void Renderer::init(float delay)
{
	auto start = std::chrono::high_resolution_clock::now();
	display = new Display();
	display->createWindow();
	this->delay = delay;
	glewExperimental = true;
	if (glewInit())
		std::cout << "Error glew" << std::endl;
	
	glClearColor(1, 1, 0, 1);

	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vertBuffer);
	glGenBuffers(1, &valueBuffer);
	
	data[0] = 0.f;
	srand(NULL);
#pragma loop(hint_parallel(8))
	for (int i = 1; i < data.size(); i++)
	{
		data[i] = rand()/(float)RAND_MAX;
	}
	//std::random_shuffle(data.begin() + 1, data.end());
	vertices.resize(data.size() * 2 + 4);
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;

#pragma loop(hint_parallel(8))
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

	const char vertCode[] = "#version 410 \n \
		layout(location = 0) in vec2 position_VS_in; \n \
		layout(location = 1) in float data_VS_in; \n \
		layout(location = 0) out vec2 position_FS_out; \n \
		layout(location = 1) out float data_FS_out; \n \
        void main(){\n  \
			gl_Position = vec4(position_VS_in, 0, 1); \n \
			position_FS_out = position_VS_in; \n \
			data_FS_out = data_VS_in; \n \
		} \n \
		";

	GLint shaderLength = sizeof(vertCode);
	const GLchar* pointer = &vertCode[0];

//	char log[1000];
//	int length;

	glShaderSource(vertShader, 1, &pointer, &shaderLength);
	glCompileShader(vertShader);

//	glGetShaderInfoLog(vertShader, 1000, &length, log);
//	std::cout << log << std::endl;
	const char fragCode[] = "#version 410\n \
		layout(location = 0) in vec2 position_FS_in; \n \
		layout(location = 1) in float data_FS_in;\n \
		layout(location = 0) out vec4 color;\n \
		vec3 hsv2rgb(vec3 c) \n \
		{ \n \
			vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0); \n \
			vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www); \n \
			return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y); \n \
		} \n \
        void main(){\n \
			vec3 hsv = vec3(data_FS_in/length(position_FS_in), length(position_FS_in), 1.f);\n \
			color = vec4(hsv2rgb(hsv), 1.f); \n \
		}\n \
		";
	
	shaderLength = sizeof(fragCode);
	pointer = &fragCode[0];
	glShaderSource(fragShader, 1, &pointer, &shaderLength);
	glCompileShader(fragShader);

//	glGetShaderInfoLog(fragShader, 1000, &length, log);
//	std::cout << log << std::endl;
	glAttachShader(program, vertShader);
	glAttachShader(program, fragShader);
	glLinkProgram(program);
	glValidateProgram(program);
//	glGetProgramInfoLog(program, 1000, &length, log);
//	std::cout << log << std::endl;
	auto end = std::chrono::high_resolution_clock::now();
	float runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
	std::cout << "Init took: " << runtime << "ms" << std::endl;

}

void Renderer::loop()
{
	std::thread sorter([this] 
	{
		auto start = std::chrono::high_resolution_clock::now();
		algo->sort(data, delay); 
		auto end = std::chrono::high_resolution_clock::now();
		float runtime = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
		std::cout << "Runtime: " << runtime << std::endl; 
	});
	while (!display->shouldClose())
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindVertexArray(vaoID);
		glUseProgram(program);
		glBindBuffer(GL_ARRAY_BUFFER, valueBuffer);
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), NULL, GL_STREAM_DRAW);
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float), (data.size()-1) * sizeof(float), data.data()+1);
	
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
