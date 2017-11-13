#pragma once
#include "vulkanvisualization.h"
struct MeshBuffer;
class VulkanGradientVisualization : public VulkanVisualization
{
public:
	VulkanGradientVisualization(int numElements);
	virtual ~VulkanGradientVisualization();
	void init(int delay);
protected:
	void render(VkCommandBuffer& cmdBuffer);
	void createPipeline();
	void destroyPipeline();
	void createLayoutDescriptions();
private:
	VkShaderModule vertModule;
	VkShaderModule fragModule;
	VkPipelineLayout pipelineLayout;
	VkPipeline pipeline;
	std::vector<VkVertexInputBindingDescription> binding;
	std::vector<VkVertexInputAttributeDescription> attribDesc;
	StorageBuffer* dataBlock;
	MeshBuffer* vertexBlock;
	size_t sizeGPU;
	float* gpuData;
};