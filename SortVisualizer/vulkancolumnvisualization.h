#pragma once
#include "vulkanvisualization.h"
#include "loader.h"
class VulkanColumnVisualization : public VulkanVisualization
{
public:
	VulkanColumnVisualization(int numElements);
	~VulkanColumnVisualization();
	void init(int delay);
protected:
	void render(VkCommandBuffer& cmdBuffer);
	void createPipeline();
	void destroyPipeline(void);
	void createData();
	void createLayoutDescriptions();
private:
	VkShaderModule vertModule;
	VkShaderModule fragModule;
	VkPipelineLayout pipelineLayout;
	VkPipeline pipeline;
	std::vector<VkVertexInputBindingDescription> binding;
	std::vector<VkVertexInputAttributeDescription> attribDesc;
	MeshBuffer* vertexBlock;
	MeshBuffer* positionBlock;
	float* gpuData;
	float* vertices;
	float* positions;
};