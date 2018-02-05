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
	bool a, mt;
	int delay;
	int number;
	cxxopts::Options options;
	Visualization * visualization;
	SortAlgorithm * algorithm;
};