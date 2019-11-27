#include <GL\glew.h>
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <cmath>

#include "vulkancolumnvisualization.h"
#include "vulkangradientvisualization.h"
#include "linevisualization.h"
#include "gradientvisualization.h"
#include "columnvisualization.h"
#include "renderer.h"
#include "selectionsort.h"
#include "bogosort.h"
#include "bubblesort.h"
#include "radixsort.h"
#include "rapidquicksort.h"
#include "stdsort.h"
#include "quicksort.h"
#include "cyclesort.h"
#include "mergesort.h"
#include "insertionsort.h"
#include "commandparser.h"

int main(int argc, char* argv[])
{
	/*glfwInit();
	glfwSetErrorCallback([](int index, const char* error) {std::cout << error << std::endl; });

	VkApplicationInfo appInfo = {};
	appInfo.apiVersion = VK_API_VERSION_1_1;
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pApplicationName = "Vulkan Test";
	appInfo.pEngineName = "Vulkan Engine";
	VkInstanceCreateInfo instanceInfo = {};
	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pNext = nullptr;
	instanceInfo.flags = 0;
	std::vector<const char*> standardvalidation = { "VK_LAYER_LUNARG_standard_validation", "VK_LAYER_LUNARG_api_dump" };
	instanceInfo.enabledLayerCount = standardvalidation.size();
	instanceInfo.ppEnabledLayerNames = standardvalidation.data();
	uint32_t glfwExtensionCount;
	const char** glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);
	instanceInfo.enabledExtensionCount = glfwExtensionCount;
	instanceInfo.ppEnabledExtensionNames = glfwExtensions;
	instanceInfo.pApplicationInfo = &appInfo;

	VkInstance instance;
	VK_CHECK(vkCreateInstance(&instanceInfo, nullptr, &instance));*/
	CommandParser* parser = new CommandParser();
	parser->parseCommandLine(argc, argv);
	SortAlgorithm* algo = parser->getAlgorithm();
	Visualization* renderer = parser->getVisualization();
	renderer->init(parser->getDelay());
	renderer->setAlgorithm(algo);
	renderer->loop();
	delete renderer;
	return 0;
}