#include "vulkangradientvisualization.h"
#include "loader.h"

VulkanGradientVisualization::VulkanGradientVisualization(int numElements)
	:VulkanVisualization(numElements)
{
	sizeGPU = numElements + 2;
}

VulkanGradientVisualization::~VulkanGradientVisualization()
{

}

void VulkanGradientVisualization::init(int delay)
{
	VulkanVisualization::init(delay);
	vkUnmapMemory(context->device, dataBlock->stagingMemory.memory);
}

void VulkanGradientVisualization::render(VkCommandBuffer & cmdBuffer)
{
	//buffer memory barrier on both queues
	vkCmdBindPipeline(cmdBuffer, VK_PIPELINE_BIND_POINT_GRAPHICS, pipeline);
	VkBuffer buffers[] = { vertexBlock->buf, dataBlock->deviceBuffer };
	VkDeviceSize offsets[] = { 0, 0 };
	vkCmdBindVertexBuffers(cmdBuffer, 0, 2, buffers, offsets);
	vkCmdDraw(cmdBuffer, sizeGPU, 1, 0, 0);
}

void VulkanGradientVisualization::createPipeline()
{
	vertModule = util::loadShader("gradientVert.spv");
	fragModule = util::loadShader("gradientFrag.spv");

	VkPipelineShaderStageCreateInfo vertShaderStageInfo =
		init::PipelineShaderStageCreateInfo(
			VK_SHADER_STAGE_VERTEX_BIT,
			vertModule,
			"main");

	VkPipelineShaderStageCreateInfo fragShaderStageInfo =
		init::PipelineShaderStageCreateInfo(
			VK_SHADER_STAGE_FRAGMENT_BIT,
			fragModule,
			"main");

	VkPipelineShaderStageCreateInfo shaderStages[] = { vertShaderStageInfo, fragShaderStageInfo };

	createLayoutDescriptions();


	VkPipelineVertexInputStateCreateInfo vertexInputInfo =
		init::PipelineVertexInputStateCreateInfo();
	vertexInputInfo.vertexBindingDescriptionCount = (uint32_t)binding.size();
	vertexInputInfo.pVertexBindingDescriptions = binding.data();
	vertexInputInfo.vertexAttributeDescriptionCount = (uint32_t)attribDesc.size();
	vertexInputInfo.pVertexAttributeDescriptions = attribDesc.data();

	VkPipelineInputAssemblyStateCreateInfo inputAssemby =
		init::PipelineInputAssemblyStateCreateInfo(
			VK_PRIMITIVE_TOPOLOGY_TRIANGLE_FAN,
			0,
			VK_FALSE);

	VkViewport viewPort =
		init::Viewport(
		(float)context->swapChainExtent.width,
			(float)context->swapChainExtent.height,
			0.0f,
			1.0f);

	VkRect2D scissor = {};
	scissor.offset = { 0, 0 };
	scissor.extent = context->swapChainExtent;

	VkPipelineDepthStencilStateCreateInfo depthStencil =
		init::PipelineDepthStencilStateCreateInfo(
			VK_TRUE,
			VK_TRUE,
			VK_COMPARE_OP_LESS);

	VkPipelineViewportStateCreateInfo viewportState =
		init::PipelineViewportStateCreateInfo(
			1,
			1,
			0);
	viewportState.pViewports = &viewPort;
	viewportState.pScissors = &scissor;

	VkPipelineRasterizationStateCreateInfo rasterizer =
		init::PipelineRasterizationStateCreateInfo(
			VK_POLYGON_MODE_FILL,
			VK_CULL_MODE_NONE,
			VK_FRONT_FACE_COUNTER_CLOCKWISE,
			0);
	rasterizer.depthClampEnable = VK_FALSE;
	rasterizer.rasterizerDiscardEnable = VK_FALSE;
	rasterizer.lineWidth = 1.0f;
	rasterizer.depthBiasEnable = VK_FALSE;

	VkPipelineMultisampleStateCreateInfo multisampling =
		init::PipelineMultisampleStateCreateInfo(
			VK_SAMPLE_COUNT_1_BIT,
			0);

	VkPipelineColorBlendAttachmentState colorBlendAttachment =
		init::PipelineColorBlendAttachmentState(
			VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT,
			VK_FALSE);

	VkPipelineColorBlendStateCreateInfo colorBlending =
		init::PipelineColorBlendStateCreateInfo(
			1,
			&colorBlendAttachment);
	colorBlending.logicOp = VK_LOGIC_OP_COPY;
	colorBlending.logicOpEnable = VK_FALSE;
	colorBlending.blendConstants[0] = 0.0f;
	colorBlending.blendConstants[1] = 0.0f;
	colorBlending.blendConstants[2] = 0.0f;
	colorBlending.blendConstants[3] = 0.0f;


	VkPipelineLayoutCreateInfo pipelineLayoutInfo =
		init::PipelineLayoutCreateInfo(
			nullptr,
			0);
	
	VK_CHECK(vkCreatePipelineLayout(context->device, &pipelineLayoutInfo, nullptr, &pipelineLayout));

	VkGraphicsPipelineCreateInfo pipelineInfo = {};
	pipelineInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineInfo.stageCount = 2;
	pipelineInfo.pStages = shaderStages;
	pipelineInfo.pVertexInputState = &vertexInputInfo;
	pipelineInfo.pInputAssemblyState = &inputAssemby;
	pipelineInfo.pViewportState = &viewportState;
	pipelineInfo.pRasterizationState = &rasterizer;
	pipelineInfo.pMultisampleState = &multisampling;
	pipelineInfo.pColorBlendState = &colorBlending;
	pipelineInfo.pDepthStencilState = &depthStencil;
	pipelineInfo.layout = pipelineLayout;
	pipelineInfo.renderPass = context->renderPass;
	pipelineInfo.subpass = 0;
	pipelineInfo.basePipelineHandle = VK_NULL_HANDLE;


	VK_CHECK(vkCreateGraphicsPipelines(context->device, VK_NULL_HANDLE, 1, &pipelineInfo, nullptr, &pipeline));
}


void VulkanGradientVisualization::createLayoutDescriptions()
{
	binding.resize(2);
	binding[0] =
		init::VertexInputBindingDescription(
			0,
			sizeof(float)*2,
			VK_VERTEX_INPUT_RATE_VERTEX);
	binding[1] =
		init::VertexInputBindingDescription(
			1,
			sizeof(float),
			VK_VERTEX_INPUT_RATE_VERTEX);

	attribDesc.resize(2);
	attribDesc[0].binding = 0;
	attribDesc[0].location = 0;
	attribDesc[0].format = VK_FORMAT_R32G32_SFLOAT;
	attribDesc[0].offset = 0;

	attribDesc[1].binding = 1;
	attribDesc[1].location = 1;
	attribDesc[1].format = VK_FORMAT_R32_SFLOAT;
	attribDesc[1].offset = 0;

}

void VulkanGradientVisualization::destroyPipeline()
{
	vkUnmapMemory(context->device, dataBlock->stagingMemory.memory);
	vkDestroyBuffer(context->device, dataBlock->deviceBuffer, nullptr);
	vkDestroyBuffer(context->device, dataBlock->stagingBuffer, nullptr);
	vkDestroyBuffer(context->device, vertexBlock->buf, nullptr);
	vkDestroyShaderModule(context->device, vertModule, nullptr);
	vkDestroyShaderModule(context->device, fragModule, nullptr);
	vkDestroyPipelineLayout(context->device, pipelineLayout, nullptr);
	vkDestroyPipeline(context->device, pipeline, nullptr);
}

void VulkanGradientVisualization::createData()
{
	float* vertices = new float[sizeGPU * 2];
	vertices[0] = 0.0f;
	vertices[1] = 0.0f;

#pragma loop(hint_parallel(0))
	for (int i = 0; i < sizeGPU - 1; ++i)
	{
		float angle = 2 * 3.141592653f * i / sizeData;
		vertices[i * 2 + 2] = cos(angle);
		vertices[i * 2 + 3] = sin(angle);
	}
	vertexBlock = context->loader->createVertexBuffer(vertices, sizeGPU, sizeof(float) * 2);


	dataBlock = new StorageBuffer();
	context->resAllocator->createBuffer(sizeGPU * sizeof(float), VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_COHERENT_BIT | VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, dataBlock->stagingBuffer, dataBlock->stagingMemory);
	context->resAllocator->createBuffer(sizeGPU * sizeof(float), VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, dataBlock->deviceBuffer, dataBlock->deviceMemory);
	vkMapMemory(context->device, dataBlock->stagingMemory.memory, dataBlock->stagingMemory.offset, sizeGPU * sizeof(float), 0, (void**)&gpuData);
	gpuData[0] = 0.f;
	gpuData[sizeGPU - 1] = 1.f;
	data = &gpuData[1];

}

