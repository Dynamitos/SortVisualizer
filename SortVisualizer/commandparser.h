#pragma once
#include <cxxopts.h>
#include "visualization.h"
#include "sortalgorithm.h"
class CommandParser
{
public:
	CommandParser();
	~CommandParser();
	void parseCommandLine(int argc, char* argv[]);
	Visualization* getVisualization() { return visualization; }
	SortAlgorithm* getAlgorithm() { return algorithm; }
	int getDelay() { return delay; }
private:
	bool vulkan{ false };
	bool a{ false };
	bool mt{ false };
	bool g{ false };
	bool c{ false };
	bool l{ false };
	int delay;
	int number;
	cxxopts::Options options;
	Visualization * visualization;
	SortAlgorithm * algorithm;
};