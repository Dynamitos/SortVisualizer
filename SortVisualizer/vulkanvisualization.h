#pragma once
#include "visualization.h"
#include "utils.h"
#include <vulkan\vulkan.h>
class VulkanVisualization : public Visualization
{
public:
	VulkanVisualization(int numElements);
	virtual ~VulkanVisualization();
	virtual void init(int delay);
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
	void destroySwapChain();
	void destroyImageViews();
	void destroyRenderPass();
	virtual void destroyPipeline() = 0;
	void destroyDepthResources();
	void destroyFramebuffers();
	void recreateSwapChain();

	VkFence renderFence;
	VulkanContext* context;
	static void onWindowResized(GLFWwindow * window, int width, int height);
};