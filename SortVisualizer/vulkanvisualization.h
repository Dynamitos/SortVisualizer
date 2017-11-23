#pragma once
#include "visualization.h"
#include "utils.h"
#include <vulkan\vulkan.h>
class VulkanVisualization : public Visualization
{
public:
	VulkanVisualization(int numElements);
	~VulkanVisualization();
	virtual void init(int delay);
	void destroy();
	void loop();
protected:
	virtual void render(VkCommandBuffer& cmdBuffer) = 0;
	void initInstance();
	void setupDebugCallback();
	void createSurface();
	void pickPhysicalDevice();
	void createLogicalDevice();
	void createSwapChain();
	void createRenderPass();
	virtual void createPipeline() = 0;
	void createImageViews();
	void createFramebuffers();
	void createSemaphores();
	void createCommandPools();
	void createDepthResources();
	void createCommandBuffers();
	virtual void createData() = 0;
	virtual void destroyPipeline() = 0;
	void destroySwapChain();
	void destroyImageViews();
	void destroyRenderPass();
	void destroyDepthResources();
	void destroyFramebuffers();
	void recreateSwapChain();
	void uploadData(int bufferIndex);

	VkFence renderFence;
	VulkanContext* context;
	StorageBuffer* dataBlock;
	size_t sizeGPU;
	static void onWindowResized(GLFWwindow* window, int width, int height);
};