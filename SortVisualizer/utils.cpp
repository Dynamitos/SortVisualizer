#include "utils.h"
#include "datamanager.h"

VkApplicationInfo init::ApplicationInfo(const char* appName, uint32_t appVersion, const char* engineName, uint32_t engineVersion, uint32_t apiVersion)
{
	VkApplicationInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	info.pApplicationName = appName;
	info.applicationVersion = appVersion;
	info.pEngineName = engineName;
	info.engineVersion = engineVersion;
	return info;
}

VkInstanceCreateInfo init::InstanceCreateInfo(VkApplicationInfo* appInfo, const std::vector<const char*> extensions, const std::vector<const char*> layers)
{
	VkInstanceCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	info.pApplicationInfo = appInfo;
	info.enabledExtensionCount = (uint32_t)extensions.size();
	info.ppEnabledExtensionNames = extensions.data();
	info.enabledLayerCount = (uint32_t)layers.size();
	info.ppEnabledLayerNames = layers.data();
	return info;
}

VkDebugReportCallbackCreateInfoEXT init::DebugReportCallbackCreateInfo(VkDebugReportFlagsEXT flags)
{
	VkDebugReportCallbackCreateInfoEXT createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CALLBACK_CREATE_INFO_EXT;
	createInfo.flags = flags;
	createInfo.pfnCallback = (PFN_vkDebugReportCallbackEXT)debugCallback;
	return createInfo;
}

VkDeviceQueueCreateInfo init::DeviceQueueCreateInfo(int queueFamilyIndex, int queueCount)
{
	float priority = 1.0f;
	return DeviceQueueCreateInfo(queueFamilyIndex, queueCount, &priority);
}

VkDeviceQueueCreateInfo init::DeviceQueueCreateInfo(int queueFamilyIndex, int queueCount, float * queuePriority)
{
	VkDeviceQueueCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	createInfo.queueFamilyIndex = queueFamilyIndex;
	createInfo.queueCount = 1;
	createInfo.pQueuePriorities = queuePriority;
	return createInfo;
}

VkDeviceCreateInfo init::DeviceCreateInfo(VkDeviceQueueCreateInfo * queueInfos, uint32_t queueCount, VkPhysicalDeviceFeatures * features)
{
	return DeviceCreateInfo(queueInfos, queueCount, features, deviceExtensions.data(), (uint32_t)deviceExtensions.size(), validationLayers.data(), (uint32_t)validationLayers.size());
}

VkSwapchainCreateInfoKHR init::SwapchainCreateInfo(VkSurfaceKHR surface, uint32_t minImageCount, VkFormat imageFormat, VkColorSpaceKHR colorSpace, VkExtent2D extent, uint32_t arrayLayers, VkImageUsageFlags usage, VkSurfaceTransformFlagBitsKHR transform, VkCompositeAlphaFlagBitsKHR alpha, VkPresentModeKHR presentMode, VkBool32 clipped)
{
	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.surface = surface;
	createInfo.minImageCount = minImageCount;
	createInfo.imageFormat = imageFormat;
	createInfo.imageColorSpace = colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = arrayLayers;
	createInfo.imageUsage = usage;
	createInfo.preTransform = transform;
	createInfo.compositeAlpha = alpha;
	createInfo.presentMode = presentMode;
	createInfo.clipped = clipped;
	return createInfo;
}

VkFramebufferCreateInfo init::FramebufferCreateInfo(VkRenderPass renderPass, uint32_t attachmentCount, VkImageView * attachments, uint32_t width, uint32_t height, uint32_t layers)
{
	VkFramebufferCreateInfo createInfo = {};
	VkFramebufferCreateInfo frameBufferCreateInfo = {};
	frameBufferCreateInfo.sType = VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
	frameBufferCreateInfo.pNext = nullptr;
	frameBufferCreateInfo.renderPass = renderPass;
	frameBufferCreateInfo.attachmentCount = attachmentCount;
	frameBufferCreateInfo.pAttachments = attachments;
	frameBufferCreateInfo.width = width;
	frameBufferCreateInfo.height = height;
	frameBufferCreateInfo.layers = layers;
	return frameBufferCreateInfo;
}

VkAttachmentDescription init::AttachmentDescription(VkFormat format, VkSampleCountFlagBits sample, VkAttachmentLoadOp loadOp, VkAttachmentStoreOp storeOp, VkAttachmentLoadOp stencilLoadOp, VkAttachmentStoreOp stencilStoreOp, VkImageLayout imageLayout, VkImageLayout finalLayout)
{
	VkAttachmentDescription desc = {};
	desc.format = format;
	desc.samples = sample;
	desc.loadOp = loadOp;
	desc.storeOp = storeOp;
	desc.stencilLoadOp = stencilLoadOp;
	desc.stencilStoreOp = stencilStoreOp;
	desc.initialLayout = imageLayout;
	desc.finalLayout = finalLayout;
	return desc;
}

VkSubpassDescription init::SubpassDescription(VkPipelineBindPoint bindPoint, uint32_t colorAttachmentCount, VkAttachmentReference * colorReference, uint32_t depthAttachmentCount, VkAttachmentReference * depthReference, uint32_t inputAttachmentCount, VkAttachmentReference * inputReference, uint32_t resolveAttachmentCount, VkAttachmentReference * resolveReference, uint32_t preserveAttachmentCount, VkAttachmentReference * preserveReference)
{
	VkSubpassDescription desc = {};
	desc.pipelineBindPoint = bindPoint;
	desc.colorAttachmentCount = colorAttachmentCount;
	desc.pColorAttachments = colorReference;
	return desc;
}

VkRenderPassCreateInfo init::RenderPassCreateInfo(uint32_t attachmentCount, VkAttachmentDescription * attachments, uint32_t subpassCount, VkSubpassDescription * subpasses, uint32_t dependencyCount, VkSubpassDependency * subpassDependencies)
{
	VkRenderPassCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	info.attachmentCount = attachmentCount;
	info.pAttachments = attachments;
	info.subpassCount = subpassCount;
	info.pSubpasses = subpasses;
	info.dependencyCount = dependencyCount;
	info.pDependencies = subpassDependencies;

	return info;
}
VkDeviceCreateInfo init::DeviceCreateInfo(VkDeviceQueueCreateInfo * queueInfos, uint32_t queueCount, VkPhysicalDeviceFeatures * features, const char * const* deviceExtensions, uint32_t deviceExtensionCount, const char * const* layers, uint32_t layerCount)
{
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.pQueueCreateInfos = queueInfos;
	createInfo.queueCreateInfoCount = queueCount;

	createInfo.pEnabledFeatures = features;

	createInfo.ppEnabledExtensionNames = deviceExtensions;
	createInfo.enabledExtensionCount = deviceExtensionCount;

	if (enableValidation)
	{
		createInfo.enabledLayerCount = layerCount;
		createInfo.ppEnabledLayerNames = layers;
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}
	return createInfo;
}

VkMemoryAllocateInfo init::MemoryAllocateInfo()
{
	VkMemoryAllocateInfo memAllocInfo = {};
	memAllocInfo.sType = VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
	memAllocInfo.pNext = NULL;
	return memAllocInfo;
}

VkCommandBufferAllocateInfo init::CommandBufferAllocateInfo(VkCommandPool commandPool, VkCommandBufferLevel level, uint32_t bufferCount)
{
	VkCommandBufferAllocateInfo commandBufferAllocateInfo = {};
	commandBufferAllocateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
	commandBufferAllocateInfo.commandPool = commandPool;
	commandBufferAllocateInfo.level = level;
	commandBufferAllocateInfo.commandBufferCount = bufferCount;
	return commandBufferAllocateInfo;
}

VkCommandPoolCreateInfo init::CommandPoolCreateInfo()
{
	VkCommandPoolCreateInfo cmdPoolCreateInfo = {};
	cmdPoolCreateInfo.sType = VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
	return cmdPoolCreateInfo;
}

VkCommandBufferBeginInfo init::CommandBufferBeginInfo()
{
	VkCommandBufferBeginInfo cmdBufferBeginInfo = {};
	cmdBufferBeginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
	cmdBufferBeginInfo.pNext = NULL;
	return cmdBufferBeginInfo;
}

VkCommandBufferInheritanceInfo init::CommandBufferInheritanceInfo()
{
	VkCommandBufferInheritanceInfo cmdBufferInheritanceInfo = {};
	cmdBufferInheritanceInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
	return cmdBufferInheritanceInfo;
}

VkRenderPassBeginInfo init::RenderPassBeginInfo()
{
	VkRenderPassBeginInfo renderPassBeginInfo = {};
	renderPassBeginInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
	renderPassBeginInfo.pNext = NULL;
	return renderPassBeginInfo;
}

VkRenderPassCreateInfo init::RenderPassCreateInfo()
{
	VkRenderPassCreateInfo renderPassCreateInfo = {};
	renderPassCreateInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
	renderPassCreateInfo.pNext = NULL;
	return renderPassCreateInfo;
}

VkImageMemoryBarrier init::ImageMemoryBarrier(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout)
{
	VkImageMemoryBarrier barrier = {};
	barrier.sType = VK_STRUCTURE_TYPE_IMAGE_MEMORY_BARRIER;
	barrier.oldLayout = oldLayout;
	barrier.newLayout = newLayout;
	barrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
	barrier.image = image;

	if (newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_DEPTH_BIT;

		if (format == VK_FORMAT_D32_SFLOAT_S8_UINT || format == VK_FORMAT_D24_UNORM_S8_UINT) {
			barrier.subresourceRange.aspectMask |= VK_IMAGE_ASPECT_STENCIL_BIT;
		}
	}
	else {
		barrier.subresourceRange.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	}

	barrier.subresourceRange.baseMipLevel = 0;
	barrier.subresourceRange.levelCount = 1;
	barrier.subresourceRange.baseArrayLayer = 0;
	barrier.subresourceRange.layerCount = 1;
	if (oldLayout == VK_IMAGE_LAYOUT_PREINITIALIZED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL) {
		barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_READ_BIT;
	}
	else if (oldLayout == VK_IMAGE_LAYOUT_PREINITIALIZED && newLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL) {
		barrier.srcAccessMask = VK_ACCESS_HOST_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
	}
	else if (oldLayout == VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL && newLayout == VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL) {
		barrier.srcAccessMask = VK_ACCESS_TRANSFER_WRITE_BIT;
		barrier.dstAccessMask = VK_ACCESS_SHADER_READ_BIT;
	}
	else if (oldLayout == VK_IMAGE_LAYOUT_UNDEFINED && newLayout == VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL) {
		barrier.srcAccessMask = 0;
		barrier.dstAccessMask = VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_READ_BIT | VK_ACCESS_DEPTH_STENCIL_ATTACHMENT_WRITE_BIT;
	}
	else {
		throw std::invalid_argument("unsupported layout transition!");
	}
	return barrier;
}

VkBufferMemoryBarrier init::BufferMemoryBarrier()
{
	VkBufferMemoryBarrier bufferMemoryBarrier = {};
	bufferMemoryBarrier.sType = VK_STRUCTURE_TYPE_BUFFER_MEMORY_BARRIER;
	bufferMemoryBarrier.pNext = NULL;
	return bufferMemoryBarrier;
}

VkMemoryBarrier init::MemoryBarrier()
{
	VkMemoryBarrier memoryBarrier = {};
	memoryBarrier.sType = VK_STRUCTURE_TYPE_MEMORY_BARRIER;
	memoryBarrier.pNext = NULL;
	return memoryBarrier;
}

VkImageCreateInfo init::ImageCreateInfo()
{
	VkImageCreateInfo imageCreateInfo = {};
	imageCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageCreateInfo.pNext = NULL;
	return imageCreateInfo;
}

VkSamplerCreateInfo init::SamplerCreateInfo()
{
	VkSamplerCreateInfo samplerCreateInfo = {};
	samplerCreateInfo.sType = VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
	samplerCreateInfo.pNext = NULL;
	return samplerCreateInfo;
}

VkImageViewCreateInfo init::ImageViewCreateInfo()
{
	VkImageViewCreateInfo imageViewCreateInfo = {};
	imageViewCreateInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	imageViewCreateInfo.pNext = NULL;
	return imageViewCreateInfo;
}

VkSemaphoreCreateInfo init::SemaphoreCreateInfo()
{
	VkSemaphoreCreateInfo semaphoreCreateInfo = {};
	semaphoreCreateInfo.sType = VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO;
	semaphoreCreateInfo.pNext = NULL;
	semaphoreCreateInfo.flags = 0;
	return semaphoreCreateInfo;
}

VkFenceCreateInfo init::FenceCreateInfo(VkFenceCreateFlags flags)
{
	VkFenceCreateInfo fenceCreateInfo = {};
	fenceCreateInfo.sType = VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
	fenceCreateInfo.flags = flags;
	return fenceCreateInfo;
}

VkEventCreateInfo init::EventCreateInfo()
{
	VkEventCreateInfo eventCreateInfo = {};
	eventCreateInfo.sType = VK_STRUCTURE_TYPE_EVENT_CREATE_INFO;
	return eventCreateInfo;
}

VkSubmitInfo init::SubmitInfo()
{
	VkSubmitInfo submitInfo = {};
	submitInfo.sType = VK_STRUCTURE_TYPE_SUBMIT_INFO;
	submitInfo.pNext = NULL;
	return submitInfo;
}

VkViewport init::Viewport(
	float width,
	float height,
	float minDepth,
	float maxDepth)
{
	VkViewport viewport = {};
	viewport.width = width;
	viewport.height = height;
	viewport.minDepth = minDepth;
	viewport.maxDepth = maxDepth;
	return viewport;
}

VkRect2D init::Rect2D(
	int32_t width,
	int32_t height,
	int32_t offsetX,
	int32_t offsetY)
{
	VkRect2D rect2D = {};
	rect2D.extent.width = width;
	rect2D.extent.height = height;
	rect2D.offset.x = offsetX;
	rect2D.offset.y = offsetY;
	return rect2D;
}

VkBufferCreateInfo init::BufferCreateInfo()
{
	VkBufferCreateInfo bufCreateInfo = {};
	bufCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	return bufCreateInfo;
}

VkBufferCreateInfo init::BufferCreateInfo(
	VkBufferUsageFlags usage,
	VkDeviceSize size)
{
	VkBufferCreateInfo bufCreateInfo = {};
	bufCreateInfo.sType = VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
	bufCreateInfo.pNext = NULL;
	bufCreateInfo.usage = usage;
	bufCreateInfo.size = size;
	bufCreateInfo.flags = 0;
	return bufCreateInfo;
}

VkDescriptorPoolCreateInfo init::DescriptorPoolCreateInfo(
	uint32_t poolSizeCount,
	VkDescriptorPoolSize* pPoolSizes,
	uint32_t maxSets)
{
	VkDescriptorPoolCreateInfo descriptorPoolInfo = {};
	descriptorPoolInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
	descriptorPoolInfo.pNext = NULL;
	descriptorPoolInfo.poolSizeCount = poolSizeCount;
	descriptorPoolInfo.pPoolSizes = pPoolSizes;
	descriptorPoolInfo.maxSets = maxSets;
	return descriptorPoolInfo;
}

VkDescriptorPoolSize init::DescriptorPoolSize(
	VkDescriptorType type,
	uint32_t descriptorCount)
{
	VkDescriptorPoolSize descriptorPoolSize = {};
	descriptorPoolSize.type = type;
	descriptorPoolSize.descriptorCount = descriptorCount;
	return descriptorPoolSize;
}

VkDescriptorSetLayoutBinding init::DescriptorSetLayoutBinding(
	VkDescriptorType type,
	VkShaderStageFlags stageFlags,
	uint32_t binding,
	uint32_t count)
{
	VkDescriptorSetLayoutBinding setLayoutBinding = {};
	setLayoutBinding.descriptorType = type;
	setLayoutBinding.stageFlags = stageFlags;
	setLayoutBinding.binding = binding;
	setLayoutBinding.descriptorCount = count;
	return setLayoutBinding;
}

VkDescriptorSetLayoutCreateInfo init::DescriptorSetLayoutCreateInfo(
	const VkDescriptorSetLayoutBinding* pBindings,
	uint32_t bindingCount)
{
	VkDescriptorSetLayoutCreateInfo descriptorSetLayoutCreateInfo = {};
	descriptorSetLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
	descriptorSetLayoutCreateInfo.pNext = NULL;
	descriptorSetLayoutCreateInfo.pBindings = pBindings;
	descriptorSetLayoutCreateInfo.bindingCount = bindingCount;
	return descriptorSetLayoutCreateInfo;
}

VkPipelineLayoutCreateInfo init::PipelineLayoutCreateInfo(
	const VkDescriptorSetLayout* pSetLayouts,
	uint32_t setLayoutCount)
{
	VkPipelineLayoutCreateInfo pipelineLayoutCreateInfo = {};
	pipelineLayoutCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
	pipelineLayoutCreateInfo.pNext = NULL;
	pipelineLayoutCreateInfo.setLayoutCount = setLayoutCount;
	pipelineLayoutCreateInfo.pSetLayouts = pSetLayouts;
	return pipelineLayoutCreateInfo;
}

VkDescriptorSetAllocateInfo init::DescriptorSetAllocateInfo(
	VkDescriptorPool descriptorPool,
	const VkDescriptorSetLayout* pSetLayouts,
	uint32_t descriptorSetCount)
{
	VkDescriptorSetAllocateInfo descriptorSetAllocateInfo = {};
	descriptorSetAllocateInfo.sType = VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
	descriptorSetAllocateInfo.pNext = NULL;
	descriptorSetAllocateInfo.descriptorPool = descriptorPool;
	descriptorSetAllocateInfo.pSetLayouts = pSetLayouts;
	descriptorSetAllocateInfo.descriptorSetCount = descriptorSetCount;
	return descriptorSetAllocateInfo;
}

VkDescriptorBufferInfo init::DescriptorBufferInfo(VkBuffer buffer, VkDeviceSize offset, VkDeviceSize range)
{
	VkDescriptorBufferInfo bufferInfo = {};
	bufferInfo.buffer = buffer;
	bufferInfo.offset = offset;
	bufferInfo.range = range;

	return bufferInfo;
}

VkDescriptorImageInfo init::DescriptorImageInfo(
	VkSampler sampler,
	VkImageView imageView,
	VkImageLayout imageLayout)
{
	VkDescriptorImageInfo descriptorImageInfo = {};
	descriptorImageInfo.sampler = sampler;
	descriptorImageInfo.imageView = imageView;
	descriptorImageInfo.imageLayout = imageLayout;
	return descriptorImageInfo;
}

VkWriteDescriptorSet init::WriteDescriptorSet(
	VkDescriptorSet dstSet,
	VkDescriptorType type,
	uint32_t binding,
	VkDescriptorBufferInfo* bufferInfo)
{
	VkWriteDescriptorSet writeDescriptorSet = {};
	writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writeDescriptorSet.pNext = NULL;
	writeDescriptorSet.dstSet = dstSet;
	writeDescriptorSet.descriptorType = type;
	writeDescriptorSet.dstBinding = binding;
	writeDescriptorSet.pBufferInfo = bufferInfo;
	// Default value in all examples
	writeDescriptorSet.descriptorCount = 1;
	return writeDescriptorSet;
}

VkWriteDescriptorSet init::WriteDescriptorSet(
	VkDescriptorSet dstSet,
	VkDescriptorType type,
	uint32_t binding,
	VkDescriptorImageInfo* bufferInfo)
{
	VkWriteDescriptorSet writeDescriptorSet = {};
	writeDescriptorSet.sType = VK_STRUCTURE_TYPE_WRITE_DESCRIPTOR_SET;
	writeDescriptorSet.pNext = NULL;
	writeDescriptorSet.dstSet = dstSet;
	writeDescriptorSet.descriptorType = type;
	writeDescriptorSet.dstBinding = binding;
	writeDescriptorSet.pImageInfo = bufferInfo;
	// Default value in all examples
	writeDescriptorSet.descriptorCount = 1;
	return writeDescriptorSet;
}

VkVertexInputBindingDescription init::VertexInputBindingDescription(
	uint32_t binding,
	uint32_t stride,
	VkVertexInputRate inputRate)
{
	VkVertexInputBindingDescription vInputBindDescription = {};
	vInputBindDescription.binding = binding;
	vInputBindDescription.stride = stride;
	vInputBindDescription.inputRate = inputRate;
	return vInputBindDescription;
}

VkVertexInputAttributeDescription init::VertexInputAttributeDescription(
	uint32_t binding,
	uint32_t location,
	VkFormat format,
	uint32_t offset)
{
	VkVertexInputAttributeDescription vInputAttribDescription = {};
	vInputAttribDescription.location = location;
	vInputAttribDescription.binding = binding;
	vInputAttribDescription.format = format;
	vInputAttribDescription.offset = offset;
	return vInputAttribDescription;
}

VkPipelineVertexInputStateCreateInfo init::PipelineVertexInputStateCreateInfo()
{
	VkPipelineVertexInputStateCreateInfo pipelineVertexInputStateCreateInfo = {};
	pipelineVertexInputStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
	pipelineVertexInputStateCreateInfo.pNext = NULL;
	return pipelineVertexInputStateCreateInfo;
}

VkPipelineInputAssemblyStateCreateInfo init::PipelineInputAssemblyStateCreateInfo(
	VkPrimitiveTopology topology,
	VkPipelineInputAssemblyStateCreateFlags flags,
	VkBool32 primitiveRestartEnable)
{
	VkPipelineInputAssemblyStateCreateInfo pipelineInputAssemblyStateCreateInfo = {};
	pipelineInputAssemblyStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
	pipelineInputAssemblyStateCreateInfo.topology = topology;
	pipelineInputAssemblyStateCreateInfo.flags = flags;
	pipelineInputAssemblyStateCreateInfo.primitiveRestartEnable = primitiveRestartEnable;
	return pipelineInputAssemblyStateCreateInfo;
}

VkPipelineRasterizationStateCreateInfo init::PipelineRasterizationStateCreateInfo(
	VkPolygonMode polygonMode,
	VkCullModeFlags cullMode,
	VkFrontFace frontFace,
	VkPipelineRasterizationStateCreateFlags flags)
{
	VkPipelineRasterizationStateCreateInfo pipelineRasterizationStateCreateInfo = {};
	pipelineRasterizationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
	pipelineRasterizationStateCreateInfo.polygonMode = polygonMode;
	pipelineRasterizationStateCreateInfo.cullMode = cullMode;
	pipelineRasterizationStateCreateInfo.frontFace = frontFace;
	pipelineRasterizationStateCreateInfo.flags = flags;
	pipelineRasterizationStateCreateInfo.depthClampEnable = VK_FALSE;
	pipelineRasterizationStateCreateInfo.lineWidth = 1.0f;
	return pipelineRasterizationStateCreateInfo;
}

VkPipelineColorBlendAttachmentState init::PipelineColorBlendAttachmentState(
	VkColorComponentFlags colorWriteMask,
	VkBool32 blendEnable)
{
	VkPipelineColorBlendAttachmentState pipelineColorBlendAttachmentState = {};
	pipelineColorBlendAttachmentState.colorWriteMask = colorWriteMask;
	pipelineColorBlendAttachmentState.blendEnable = blendEnable;
	return pipelineColorBlendAttachmentState;
}

VkPipelineColorBlendStateCreateInfo init::PipelineColorBlendStateCreateInfo(
	uint32_t attachmentCount,
	const VkPipelineColorBlendAttachmentState * pAttachments)
{
	VkPipelineColorBlendStateCreateInfo pipelineColorBlendStateCreateInfo = {};
	pipelineColorBlendStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
	pipelineColorBlendStateCreateInfo.pNext = NULL;
	pipelineColorBlendStateCreateInfo.attachmentCount = attachmentCount;
	pipelineColorBlendStateCreateInfo.pAttachments = pAttachments;
	return pipelineColorBlendStateCreateInfo;
}

VkPipelineDepthStencilStateCreateInfo init::PipelineDepthStencilStateCreateInfo(
	VkBool32 depthTestEnable,
	VkBool32 depthWriteEnable,
	VkCompareOp depthCompareOp)
{
	VkPipelineDepthStencilStateCreateInfo pipelineDepthStencilStateCreateInfo = {};
	pipelineDepthStencilStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
	pipelineDepthStencilStateCreateInfo.depthTestEnable = depthTestEnable;
	pipelineDepthStencilStateCreateInfo.depthWriteEnable = depthWriteEnable;
	pipelineDepthStencilStateCreateInfo.depthCompareOp = depthCompareOp;
	pipelineDepthStencilStateCreateInfo.front = pipelineDepthStencilStateCreateInfo.back;
	pipelineDepthStencilStateCreateInfo.back.compareOp = VK_COMPARE_OP_ALWAYS;
	return pipelineDepthStencilStateCreateInfo;
}

VkPipelineViewportStateCreateInfo init::PipelineViewportStateCreateInfo(
	uint32_t viewportCount,
	uint32_t scissorCount,
	VkPipelineViewportStateCreateFlags flags)
{
	VkPipelineViewportStateCreateInfo pipelineViewportStateCreateInfo = {};
	pipelineViewportStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
	pipelineViewportStateCreateInfo.viewportCount = viewportCount;
	pipelineViewportStateCreateInfo.scissorCount = scissorCount;
	pipelineViewportStateCreateInfo.flags = flags;
	return pipelineViewportStateCreateInfo;
}

VkPipelineMultisampleStateCreateInfo init::PipelineMultisampleStateCreateInfo(
	VkSampleCountFlagBits rasterizationSamples,
	VkPipelineMultisampleStateCreateFlags flags)
{
	VkPipelineMultisampleStateCreateInfo pipelineMultisampleStateCreateInfo = {};
	pipelineMultisampleStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
	pipelineMultisampleStateCreateInfo.rasterizationSamples = rasterizationSamples;
	return pipelineMultisampleStateCreateInfo;
}

VkPipelineDynamicStateCreateInfo init::PipelineDynamicStateCreateInfo(
	const VkDynamicState * pDynamicStates,
	uint32_t dynamicStateCount,
	VkPipelineDynamicStateCreateFlags flags)
{
	VkPipelineDynamicStateCreateInfo pipelineDynamicStateCreateInfo = {};
	pipelineDynamicStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
	pipelineDynamicStateCreateInfo.pDynamicStates = pDynamicStates;
	pipelineDynamicStateCreateInfo.dynamicStateCount = dynamicStateCount;
	return pipelineDynamicStateCreateInfo;
}

VkPipelineTessellationStateCreateInfo init::PipelineTessellationStateCreateInfo(uint32_t patchControlPoints)
{
	VkPipelineTessellationStateCreateInfo pipelineTessellationStateCreateInfo = {};
	pipelineTessellationStateCreateInfo.sType = VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
	pipelineTessellationStateCreateInfo.patchControlPoints = patchControlPoints;
	return pipelineTessellationStateCreateInfo;
}

VkGraphicsPipelineCreateInfo init::PipelineCreateInfo(
	VkPipelineLayout layout,
	VkRenderPass renderPass,
	VkPipelineCreateFlags flags)
{
	VkGraphicsPipelineCreateInfo pipelineCreateInfo = {};
	pipelineCreateInfo.sType = VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
	pipelineCreateInfo.pNext = NULL;
	pipelineCreateInfo.layout = layout;
	pipelineCreateInfo.renderPass = renderPass;
	pipelineCreateInfo.flags = flags;
	return pipelineCreateInfo;
}

VkComputePipelineCreateInfo init::ComputePipelineCreateInfo(VkPipelineLayout layout, VkPipelineCreateFlags flags)
{
	VkComputePipelineCreateInfo computePipelineCreateInfo = {};
	computePipelineCreateInfo.sType = VK_STRUCTURE_TYPE_COMPUTE_PIPELINE_CREATE_INFO;
	computePipelineCreateInfo.layout = layout;
	computePipelineCreateInfo.flags = flags;
	return computePipelineCreateInfo;
}

VkPushConstantRange init::PushConstantRange(
	VkShaderStageFlags stageFlags,
	uint32_t size,
	uint32_t offset)
{
	VkPushConstantRange pushConstantRange = {};
	pushConstantRange.stageFlags = stageFlags;
	pushConstantRange.offset = offset;
	pushConstantRange.size = size;
	return pushConstantRange;
}

VkPipelineShaderStageCreateInfo init::PipelineShaderStageCreateInfo(VkShaderStageFlagBits stage, VkShaderModule module, const char * entryName)
{
	VkPipelineShaderStageCreateInfo info = {};
	info.sType = VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO;
	info.module = module;
	info.stage = stage;
	info.pName = entryName;
	return info;
}

std::vector<const char*> util::getRequiredExtensions()
{
	std::vector<const char*> extensions;

	unsigned int glfwExtensionCount = 0;
	const char** glfwExtensions;
	glfwExtensions = glfwGetRequiredInstanceExtensions(&glfwExtensionCount);

	for (unsigned int i = 0; i < glfwExtensionCount; i++) {
		extensions.push_back(glfwExtensions[i]);
	}
	if (enableValidation)
		extensions.push_back(VK_EXT_DEBUG_REPORT_EXTENSION_NAME);


	return extensions;
}
bool util::isDeviceSuitable(VkPhysicalDevice device, QueueFamilyIndices indices)
{
	bool extensionsSupported = checkDeviceExtensionSupport(device);
	bool swapChainAdequate = false;
	if (extensionsSupported) {
		SwapChainSupportDetails swapChainSupport = querySwapChainSupport(device);
		swapChainAdequate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}
	return indices.isComplete() && extensionsSupported && swapChainAdequate;
}

bool util::checkDeviceExtensionSupport(VkPhysicalDevice physicalDevice)
{
	uint32_t extensionCount;
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(physicalDevice, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(deviceExtensions.begin(), deviceExtensions.end());

	for (const auto& extension : availableExtensions) {
		requiredExtensions.erase(extension.extensionName);
	}

	return requiredExtensions.empty();
}
QueueFamilyIndices util::findQueueFamilies(VkPhysicalDevice physicalDevice)
{
	VulkanContext* context = DataManager::getInstance().getContext();
	QueueFamilyIndices indices;

	uint32_t queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, nullptr);

	std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(physicalDevice, &queueFamilyCount, queueFamilies.data());
	int i = 0;
	for (const auto& queueFamily : queueFamilies)
	{
		if (!(queueFamily.queueCount > 0))
			continue;
		if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT)
		{
			indices.graphicsFamily = i;
		}
		if ((queueFamily.queueFlags - VK_QUEUE_TRANSFER_BIT) == 0)
		{
			indices.dedicatedTransfer = i;
		}
		if (queueFamily.queueFlags & VK_QUEUE_TRANSFER_BIT)
		{
			indices.transferFamily = i;
		}
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(physicalDevice, i, context->surface, &presentSupport);

		if (presentSupport)
		{
			indices.presentFamily = i;
		}
		if (queueFamily.queueFlags & VK_QUEUE_COMPUTE_BIT)
		{
			indices.computeFamily = i;
		}

		i++;
	}

	if (indices.dedicatedTransfer != -1)
	{
		std::cout << "using graphics for transfer" << std::endl;
		indices.transferFamily = indices.graphicsFamily;
	}
	return indices;
}

SwapChainSupportDetails util::querySwapChainSupport(VkPhysicalDevice physicalDevice)
{
	VulkanContext* context = DataManager::getInstance().getContext();
	SwapChainSupportDetails details;
	vkGetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, context->surface, &details.capabilities);

	uint32_t formatCount;
	vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, context->surface, &formatCount, nullptr);

	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, context->surface, &formatCount, details.formats.data());
	}
	uint32_t presentModeCount;
	vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, context->surface, &presentModeCount, nullptr);

	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, context->surface, &presentModeCount, details.presentModes.data());
	}

	return details;
}

VkSurfaceFormatKHR util::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED)
	{
		return{ VK_FORMAT_B8G8R8A8_UNORM, VK_COLORSPACE_SRGB_NONLINEAR_KHR };
	}
	for (const auto& availableFormat : availableFormats)
	{
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}
	return availableFormats[0];
}
VkPresentModeKHR util::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
{
	for (const auto& availablePresentMode : availablePresentModes)
	{
		if (availablePresentMode == VK_PRESENT_MODE_MAILBOX_KHR)
		{
			return availablePresentMode;
		}
	}
	return VK_PRESENT_MODE_IMMEDIATE_KHR;
}
#undef max
#undef min
VkExtent2D util::chooseSwapExtent(const VkSurfaceCapabilitiesKHR & capabilities, Display* display)
{
	if (capabilities.currentExtent.width != std::numeric_limits<uint32_t>::max()) {
		return capabilities.currentExtent;
	}
	else {
		VkExtent2D actualExtent = { display->getWidth(), display->getHeight() };

		actualExtent.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtent.width));
		actualExtent.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtent.height));

		return actualExtent;
	}
}

VkShaderModule util::loadShader(const char * filename)
{
	VulkanContext* context = DataManager::getInstance().getContext();
	std::string sfile = std::string(SHADER_PATH);
	sfile.append(filename);
	std::ifstream file(sfile, std::ios::ate | std::ios::binary);
	if (!file.is_open())
	{
		throw std::runtime_error("failed to open file!");
	}
	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);

	file.seekg(0);
	file.read(buffer.data(), fileSize);

	file.close();
	VkShaderModule module;
	VkShaderModuleCreateInfo moduleInfo = {};
	moduleInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	moduleInfo.codeSize = buffer.size();
	moduleInfo.pCode = (uint32_t*)buffer.data();
	VK_CHECK(vkCreateShaderModule(context->device, &moduleInfo, nullptr, &module));
	return module;
}
uint32_t util::findMemoryType(uint32_t typeFilter, VkMemoryPropertyFlags properties)
{
	VulkanContext* context = DataManager::getInstance().getContext();

	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(context->physicalDevice, &memProperties);


	for (uint32_t i = 0; i < memProperties.memoryTypeCount; i++) {
		if (typeFilter & (1 << i) && (memProperties.memoryTypes[i].propertyFlags & properties) == properties) {
			return i;
		}
	}

	return 0;
}
VkCommandBuffer util::beginSingleTimeCommands()
{
	VulkanContext* context = DataManager::getInstance().getContext();
	VkCommandBufferAllocateInfo allocInfo =
		init::CommandBufferAllocateInfo(
			context->cmdTempPool,
			VK_COMMAND_BUFFER_LEVEL_PRIMARY,
			1);


	VkCommandBuffer commandBuffer;
	vkAllocateCommandBuffers(context->device, &allocInfo, &commandBuffer);

	VkCommandBufferBeginInfo beginInfo =
		init::CommandBufferBeginInfo();
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
	
	vkBeginCommandBuffer(commandBuffer, &beginInfo);

	return commandBuffer;
}
void util::endSingleTimeCommands(VkCommandBuffer commandBuffer)
{
	VulkanContext* context = DataManager::getInstance().getContext();
	vkEndCommandBuffer(commandBuffer);

	VkSubmitInfo submitInfo =
		init::SubmitInfo();
	submitInfo.commandBufferCount = 1;
	submitInfo.pCommandBuffers = &commandBuffer;
	
	vkQueueSubmit(context->graphicsQueue, 1, &submitInfo, context->utilFence);
	
	VkResult res;
	do
	{
		res = vkWaitForFences(context->device, 1, &context->utilFence, VK_TRUE, 100000);
	} while (res == VK_TIMEOUT);
	vkResetFences(context->device, 1, &context->utilFence);
	
	//vkQueueWaitIdle(context->graphicsQueue);
	//vkDeviceWaitIdle(context->device);
	vkFreeCommandBuffers(context->device, context->cmdTempPool, 1, &commandBuffer);
}

void util::copyBuffer(VkBuffer srcBuffer, VkBuffer dstBuffer, VkDeviceSize size)
{
	VulkanContext* context = DataManager::getInstance().getContext();
	VkCommandBuffer commandBuffer = beginSingleTimeCommands();

	VkBufferCopy copyRegion = {};
	copyRegion.size = size;
	vkCmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, 1, &copyRegion);

	endSingleTimeCommands(commandBuffer);
}

void util::transitionImageLayout(VkImage image, VkFormat format, VkImageLayout oldLayout, VkImageLayout newLayout)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands();

	VkImageMemoryBarrier barrier = init::ImageMemoryBarrier(image, format, oldLayout, newLayout);

	vkCmdPipelineBarrier(commandBuffer, VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT, VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT, 0, 0, nullptr, 0, nullptr, 1, &barrier);

	endSingleTimeCommands(commandBuffer);
}

void util::copyImage(VkImage srcImage, VkImage dstImage, uint32_t width, uint32_t height)
{
	VkCommandBuffer commandBuffer = beginSingleTimeCommands();

	VkImageSubresourceLayers subResource = {};
	subResource.aspectMask = VK_IMAGE_ASPECT_COLOR_BIT;
	subResource.baseArrayLayer = 0;
	subResource.mipLevel = 0;
	subResource.layerCount = 1;

	VkImageCopy region = {};
	region.srcSubresource = subResource;
	region.dstSubresource = subResource;
	region.srcOffset = { 0, 0, 0 };
	region.dstOffset = { 0, 0, 0 };
	region.extent.width = width;
	region.extent.height = height;
	region.extent.depth = 1;

	vkCmdCopyImage(commandBuffer, srcImage, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL, dstImage, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, 1, &region);

	endSingleTimeCommands(commandBuffer);
}
VkFormat util::findSupportedFormat(const std::vector<VkFormat>& candidates, VkImageTiling tiling, VkFormatFeatureFlags features)
{
	VulkanContext* context = DataManager::getInstance().getContext();
	for (VkFormat format : candidates)
	{
		VkFormatProperties props;
		vkGetPhysicalDeviceFormatProperties(context->physicalDevice, format, &props);
		if (tiling == VK_IMAGE_TILING_LINEAR && (props.linearTilingFeatures & features) == features) {
			return format;
		}
		else if (tiling == VK_IMAGE_TILING_OPTIMAL && (props.optimalTilingFeatures & features) == features) {
			return format;
		}
	}
	throw std::runtime_error("failed to find supported depth format!");
}
VkFormat util::findDepthFormat()
{
	return findSupportedFormat({ VK_FORMAT_D32_SFLOAT, VK_FORMAT_D32_SFLOAT_S8_UINT, VK_FORMAT_D24_UNORM_S8_UINT },
		VK_IMAGE_TILING_OPTIMAL,
		VK_FORMAT_FEATURE_DEPTH_STENCIL_ATTACHMENT_BIT);
}
VkBool32 __stdcall debugCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t obj, size_t location, int32_t code, const char* layerPrefix, const char* msg, void* userDataManager) {
	std::cerr << layerPrefix << ": " << msg << std::endl;

	return VK_FALSE;
}
VkResult CreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT* pCreateInfo, const VkAllocationCallbacks* pAllocator, VkDebugReportCallbackEXT* pCallback) {
	auto func = (PFN_vkCreateDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkCreateDebugReportCallbackEXT");
	if (func != nullptr) {
		return func(instance, pCreateInfo, pAllocator, pCallback);
	}
	else {
		return VK_ERROR_EXTENSION_NOT_PRESENT;
	}
}

void DestroyDebugReportCallbackEXT(VkInstance instance, const VkAllocationCallbacks * pAllocator, VkDebugReportCallbackEXT pCallback)
{
	auto func = (PFN_vkDestroyDebugReportCallbackEXT)vkGetInstanceProcAddr(instance, "vkDestroyDebugReportCallbackEXT");
	if (func != nullptr) {
		func(instance, pCallback, pAllocator);
	}
}

