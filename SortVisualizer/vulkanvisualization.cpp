#include "vulkanvisualization.h"
#include "loader.h"
#include "datamanager.h"

VulkanVisualization::VulkanVisualization(int numElements)
	: Visualization(numElements) {
	context = DataManager::getInstance().getContext();
	
}

VulkanVisualization::~VulkanVisualization()
{
	destroy();
}
void VulkanVisualization::init(int delay)
{
	display->createWindow(true);
	initInstance();
	setupDebugCallback();
	createSurface();
	pickPhysicalDevice();
	createLogicalDevice();
	createSwapChain();
	createImageViews();
	createRenderPass();
	createPipeline();
	createCommandPools();
	createSemaphores();
	createDepthResources();
	createFramebuffers();
	createData();
	createCommandBuffers();
	glfwSetWindowUserPointer(display->getWindow(), this);
	glfwSetWindowSizeCallback(display->getWindow(), onWindowResized);
	display->showWindow();
	Visualization::init(delay);
}
void VulkanVisualization::destroy()
{

	vkDeviceWaitIdle(context->device);
	vkFreeCommandBuffers(context->device, context->commandPool, context->commandBuffers.size(), context->commandBuffers.data());
	vkFreeCommandBuffers(context->device, context->transferPool, context->transferCommands.size(), context->transferCommands.data());
	for (auto fb : context->frameBuffers) {
		vkDestroyFramebuffer(context->device, fb, nullptr);
	}
	vkDestroyImageView(context->device, context->depthImageView, nullptr);
	vkDestroyImage(context->device, context->depthImage, nullptr);
	vkDestroyFence(context->device, context->utilFence, nullptr);
	vkDestroyFence(context->device, renderFence, nullptr);
	vkDestroySemaphore(context->device, context->transferFinishedSemaphore, nullptr);
	vkDestroySemaphore(context->device, context->imageAvailableSemaphore, nullptr);
	vkDestroySemaphore(context->device, context->renderFinishedSemaphore, nullptr);
	vkDestroyCommandPool(context->device, context->commandPool, nullptr);
	vkDestroyCommandPool(context->device, context->cmdTempPool, nullptr);
	vkDestroyCommandPool(context->device, context->transferPool, nullptr);
	destroyPipeline();
	destroyRenderPass();
	delete context->resAllocator;
	for (auto iv : context->swapChainImageViews)
	{
		vkDestroyImageView(context->device, iv, nullptr);
	}
	vkDestroySwapchainKHR(context->device, context->swapChain, nullptr);
	vkDestroyDevice(context->device, nullptr);
	DestroyDebugReportCallbackEXT(context->instance, nullptr, context->callback);
	vkDestroyInstance(context->instance, nullptr);
}
#undef max
#undef min
void VulkanVisualization::loop()
{
	startSort();
	while (!display->shouldClose())
	{
		//createCommandBuffers();
		uint32_t imageIndex;
		VkResult result = vkAcquireNextImageKHR(context->device, context->swapChain, std::numeric_limits<uint64_t>::max(), context->imageAvailableSemaphore, VK_NULL_HANDLE, &imageIndex);

		VkSemaphore waitSemaphores[] = { context->imageAvailableSemaphore, context->transferFinishedSemaphore };
		if (result == VK_ERROR_OUT_OF_DATE_KHR) {
			recreateSwapChain();
			return;
		}
		else if (result != VK_SUCCESS && result != VK_SUBOPTIMAL_KHR) {
			throw std::runtime_error("failed to acquire swap chain image!");
		}
		VkSubmitInfo submitInfo =
			init::SubmitInfo();

		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &context->transferCommands[imageIndex];
		submitInfo.waitSemaphoreCount = 0;
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = &context->transferFinishedSemaphore;
		submitInfo.pWaitSemaphores = nullptr;

		vkQueueSubmit(context->transferQueue, 1, &submitInfo, VK_NULL_HANDLE);

		VkPipelineStageFlags waitStages[] = { VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT };
		submitInfo.waitSemaphoreCount = 2;
		submitInfo.pWaitSemaphores = waitSemaphores;
		submitInfo.pWaitDstStageMask = waitStages;
		submitInfo.commandBufferCount = 1;
		submitInfo.pCommandBuffers = &context->commandBuffers[imageIndex];

		VkSemaphore signalSemaphores[] = { context->renderFinishedSemaphore };
		submitInfo.signalSemaphoreCount = 1;
		submitInfo.pSignalSemaphores = signalSemaphores;


		VK_CHECK(vkQueueSubmit(context->graphicsQueue, 1, &submitInfo, renderFence));
		VkPresentInfoKHR presentInfo = {};
		presentInfo.sType = VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;

		presentInfo.waitSemaphoreCount = 1;
		presentInfo.pWaitSemaphores = signalSemaphores;

		VkSwapchainKHR swapChains[] = { context->swapChain };
		presentInfo.swapchainCount = 1;
		presentInfo.pSwapchains = swapChains;

		presentInfo.pImageIndices = &imageIndex;
		VkResult fenceRes;
		do
		{
			fenceRes = vkWaitForFences(context->device, 1, &renderFence, VK_TRUE, 100000000);
		} while (fenceRes == VK_TIMEOUT);

		result = vkQueuePresentKHR(context->presentQueue, &presentInfo);

		vkResetFences(context->device, 1, &renderFence);
		if (result == VK_ERROR_OUT_OF_DATE_KHR || result == VK_SUBOPTIMAL_KHR) {
			recreateSwapChain();
		}
		else if (result != VK_SUCCESS) {
			throw std::runtime_error("failed to present swap chain image!");
		}
		display->updateWindow();
		//std::cout << "Tick" << std::endl;
	}
	waitSort();
}




void VulkanVisualization::initInstance()
{
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "Vulkan Test";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "Worst Engine Ever";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_0;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = util::getRequiredExtensions();
	createInfo.enabledExtensionCount = (uint32_t)extensions.size();
	createInfo.ppEnabledExtensionNames = extensions.data();

	if (enableValidation)
	{
		uint32_t numProperties;
		vkEnumerateInstanceLayerProperties(&numProperties, nullptr);
		std::vector<VkLayerProperties> layers(numProperties);
		vkEnumerateInstanceLayerProperties(&numProperties, layers.data());
		createInfo.enabledLayerCount = (uint32_t)validationLayers.size();
		createInfo.ppEnabledLayerNames = validationLayers.data();
	}
	else
	{
		createInfo.enabledLayerCount = 0;
	}
	VK_CHECK(vkCreateInstance(&createInfo, nullptr, &context->instance));
}

void VulkanVisualization::setupDebugCallback()
{
	if (enableValidation) {
		VkDebugReportCallbackCreateInfoEXT createInfo =
			init::DebugReportCallbackCreateInfo(
				VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT);

		VK_CHECK(CreateDebugReportCallbackEXT(context->instance, &createInfo, nullptr, &context->callback));
	}
}

void VulkanVisualization::createSurface()
{
	glfwCreateWindowSurface(context->instance, display->getWindow(), nullptr, &context->surface);
}

void VulkanVisualization::pickPhysicalDevice()
{
	uint32_t deviceCount = 0;
	vkEnumeratePhysicalDevices(context->instance, &deviceCount, nullptr);

	if (deviceCount == 0) {
		throw std::runtime_error("failed to find GPUs with Vulkan support!");
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(context->instance, &deviceCount, devices.data());

	QueueFamilyIndices indices;
	for (const auto& device : devices) {
		indices = util::findQueueFamilies(device);
		if (util::isDeviceSuitable(device, indices)) {
			context->physicalDevice = device;
			context->indices = indices;
			break;
		}
	}

	if (context->physicalDevice == VK_NULL_HANDLE) {
		throw std::runtime_error("failed to find a suitable GPU!");
	}
}

void VulkanVisualization::createLogicalDevice()
{

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<uint32_t> uniqueQueueFamilies = { context->indices.graphicsFamily, context->indices.presentFamily, context->indices.transferFamily, context->indices.computeFamily };

	for (uint32_t queueFamily : uniqueQueueFamilies)
	{
		float priority = 0.f;
		VkDeviceQueueCreateInfo queueCreateInfo =
			init::DeviceQueueCreateInfo(
				queueFamily,
				1,
				&priority);
		queueCreateInfos.push_back(queueCreateInfo);
	}
	VkPhysicalDeviceFeatures deviceFeatures = {};

	VkDeviceCreateInfo createInfo =
		init::DeviceCreateInfo(
			queueCreateInfos.data(),
			(uint32_t)queueCreateInfos.size(),
			&deviceFeatures);

	VK_CHECK(vkCreateDevice(context->physicalDevice, &createInfo, nullptr, &context->device));

	vkGetDeviceQueue(context->device, context->indices.graphicsFamily, 0, &context->graphicsQueue);
	vkGetDeviceQueue(context->device, context->indices.presentFamily, 0, &context->presentQueue);
	vkGetDeviceQueue(context->device, context->indices.transferFamily, 0, &context->transferQueue);

	context->loader = new Loader(context);
	context->resAllocator = new ResourceAllocator(context);
}

void VulkanVisualization::createSwapChain()
{
	SwapChainSupportDetails swapChainSupport = util::querySwapChainSupport(context->physicalDevice);

	VkSurfaceFormatKHR surfaceFormat = util::chooseSwapSurfaceFormat(swapChainSupport.formats);
	VkPresentModeKHR presentMode = util::chooseSwapPresentMode(swapChainSupport.presentModes);
	VkExtent2D extent = util::chooseSwapExtent(swapChainSupport.capabilities, display);

	context->swapChainImageFormat = surfaceFormat.format;
	context->swapChainExtent = extent;

	uint32_t imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount)
	{
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}
	VkSwapchainCreateInfoKHR createInfo =
		init::SwapchainCreateInfo(
			context->surface,
			imageCount,
			surfaceFormat.format,
			surfaceFormat.colorSpace,
			extent,
			1,
			VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT,
			swapChainSupport.capabilities.currentTransform,
			VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR,
			presentMode,
			VK_TRUE);
	QueueFamilyIndices indices = context->indices;
	uint32_t queueFamilyIndices[] = { (uint32_t)indices.graphicsFamily, (uint32_t)indices.presentFamily };

	if (indices.graphicsFamily != indices.presentFamily)
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamilyIndices;
	}
	else
	{
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
		createInfo.queueFamilyIndexCount = 0; // Optional
		createInfo.pQueueFamilyIndices = nullptr; // Optional
	}
	VkSwapchainKHR oldSwapChain = context->swapChain;
	createInfo.oldSwapchain = oldSwapChain;

	VkSwapchainKHR newSwapChain;
	VK_CHECK(vkCreateSwapchainKHR(context->device, &createInfo, nullptr, &newSwapChain));
	*&context->swapChain = newSwapChain;

	vkGetSwapchainImagesKHR(context->device, context->swapChain, &imageCount, nullptr);
	context->swapChainImages.resize(imageCount);
	vkGetSwapchainImagesKHR(context->device, context->swapChain, &imageCount, context->swapChainImages.data());
}

void VulkanVisualization::createRenderPass()
{
	VkAttachmentDescription colorAttachment =
		init::AttachmentDescription(
			context->swapChainImageFormat,
			VK_SAMPLE_COUNT_1_BIT,
			VK_ATTACHMENT_LOAD_OP_CLEAR,
			VK_ATTACHMENT_STORE_OP_STORE,
			VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			VK_ATTACHMENT_STORE_OP_DONT_CARE,
			VK_IMAGE_LAYOUT_UNDEFINED,
			VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

	VkAttachmentDescription depthAttachment =
		init::AttachmentDescription(
			util::findDepthFormat(),
			VK_SAMPLE_COUNT_1_BIT,
			VK_ATTACHMENT_LOAD_OP_CLEAR,
			VK_ATTACHMENT_STORE_OP_DONT_CARE,
			VK_ATTACHMENT_LOAD_OP_DONT_CARE,
			VK_ATTACHMENT_STORE_OP_DONT_CARE,
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL,
			VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);

	VkAttachmentReference colorReference = {};
	colorReference.attachment = 0;
	colorReference.layout = VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL;

	VkAttachmentReference depthAttachmentRef = {};
	depthAttachmentRef.attachment = 1;
	depthAttachmentRef.layout = VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL;

	VkSubpassDescription subpassDescription =
		init::SubpassDescription(
			VK_PIPELINE_BIND_POINT_GRAPHICS,
			1,
			&colorReference,
			1,
			&depthAttachmentRef);

	VkSubpassDependency dependency = {};
	dependency.srcSubpass = VK_SUBPASS_EXTERNAL;
	dependency.dstSubpass = 0;

	dependency.srcStageMask = VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT;
	dependency.srcAccessMask = VK_ACCESS_MEMORY_READ_BIT;

	dependency.dstStageMask = VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
	dependency.dstAccessMask = VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT;


	std::array<VkAttachmentDescription, 2> attachments = { colorAttachment, depthAttachment };
	VkRenderPassCreateInfo createInfo =
		init::RenderPassCreateInfo(
			static_cast<uint32_t>(attachments.size()),
			attachments.data(),
			1,
			&subpassDescription,
			1,
			&dependency);

	VK_CHECK(vkCreateRenderPass(context->device, &createInfo, nullptr, &context->renderPass));
}
void VulkanVisualization::createImageViews()
{
	context->swapChainImageViews.resize(context->swapChainImages.size());
	for (uint32_t i = 0; i < context->swapChainImages.size(); i++)
	{
		context->resAllocator->createImageView(context->swapChainImages[i], context->swapChainImageFormat, VK_IMAGE_ASPECT_COLOR_BIT, context->swapChainImageViews[i]);
	}
}
void VulkanVisualization::createFramebuffers()
{

	context->frameBuffers.resize(context->swapChainImages.size());
	for (uint32_t i = 0; i < context->swapChainImages.size(); i++)
	{
		std::vector<VkImageView> attachments = {
			context->swapChainImageViews[i],
			context->depthImageView
		};
		context->resAllocator->createFramebuffer(attachments, context->frameBuffers[i]);
	}
}

void VulkanVisualization::createSemaphores()
{
	VkSemaphoreCreateInfo semaphoreInfo =
		init::SemaphoreCreateInfo();

	VK_CHECK(vkCreateSemaphore(context->device, &semaphoreInfo, nullptr, &context->imageAvailableSemaphore));
	VK_CHECK(vkCreateSemaphore(context->device, &semaphoreInfo, nullptr, &context->renderFinishedSemaphore));
	VK_CHECK(vkCreateSemaphore(context->device, &semaphoreInfo, nullptr, &context->transferFinishedSemaphore));

	VkFenceCreateInfo fenceInfo =
		init::FenceCreateInfo(0);

	VK_CHECK(vkCreateFence(context->device, &fenceInfo, nullptr, &renderFence));
	VK_CHECK(vkCreateFence(context->device, &fenceInfo, nullptr, &context->utilFence));
}

void VulkanVisualization::createCommandPools()
{
	VkCommandPoolCreateInfo poolInfo =
		init::CommandPoolCreateInfo();
	poolInfo.queueFamilyIndex = context->indices.graphicsFamily;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;
	VK_CHECK(vkCreateCommandPool(context->device, &poolInfo, nullptr, &context->commandPool));

	poolInfo = init::CommandPoolCreateInfo();
	poolInfo.queueFamilyIndex = context->indices.graphicsFamily;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;

	VK_CHECK(vkCreateCommandPool(context->device, &poolInfo, nullptr, &context->cmdTempPool));

	poolInfo.queueFamilyIndex = context->indices.transferFamily;
	poolInfo.flags = VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT;

	VK_CHECK(vkCreateCommandPool(context->device, &poolInfo, nullptr, &context->transferPool));
}

void VulkanVisualization::createDepthResources()
{
	VkFormat depthFormat = util::findDepthFormat();
	context->resAllocator->createImage(context->swapChainExtent.width, context->swapChainExtent.height,
		depthFormat, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_DEPTH_STENCIL_ATTACHMENT_BIT,
		VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT,
		context->depthImage, context->depthMemory);
	context->resAllocator->createImageView(context->depthImage, depthFormat, VK_IMAGE_ASPECT_DEPTH_BIT, context->depthImageView);
	util::transitionImageLayout(context->depthImage, depthFormat, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_DEPTH_STENCIL_ATTACHMENT_OPTIMAL);
}

void VulkanVisualization::createCommandBuffers()
{
	if (context->commandBuffers.size() > 0)
	{
		vkFreeCommandBuffers(context->device, context->commandPool, (uint32_t)context->commandBuffers.size(), context->commandBuffers.data());
		vkFreeCommandBuffers(context->device, context->transferPool, (uint32_t)context->transferCommands.size(), context->transferCommands.data());
	}
	context->commandBuffers.resize(context->frameBuffers.size());
	context->transferCommands.resize(context->frameBuffers.size());
	VkCommandBufferAllocateInfo allocInfo =
		init::CommandBufferAllocateInfo(context->commandPool, VK_COMMAND_BUFFER_LEVEL_PRIMARY, context->commandBuffers.size());

	vkAllocateCommandBuffers(context->device, &allocInfo, context->commandBuffers.data());
	
	allocInfo.commandPool = context->transferPool;

	vkAllocateCommandBuffers(context->device, &allocInfo, context->transferCommands.data());

	for (uint32_t i = 0; i < context->frameBuffers.size(); i++)
	{
		VkCommandBufferBeginInfo beginInfo = {};
		beginInfo.sType = VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
		beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;
		beginInfo.pInheritanceInfo = nullptr;

		uploadData(i);

		vkBeginCommandBuffer(context->commandBuffers[i], &beginInfo);

		VkRenderPassBeginInfo renderPassInfo = {};
		renderPassInfo.sType = VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
		renderPassInfo.renderPass = context->renderPass;
		renderPassInfo.framebuffer = context->frameBuffers[i];
		renderPassInfo.renderArea.offset = { 0, 0 };
		renderPassInfo.renderArea.extent = context->swapChainExtent;

		std::array<VkClearValue, 2> clearValues = {};
		clearValues[0].color = { 0.0f, 0.0f, 0.0f, 1.0f };
		clearValues[1].depthStencil = { 1.0f, 0 };

		renderPassInfo.clearValueCount = static_cast<uint32_t>(clearValues.size());
		renderPassInfo.pClearValues = clearValues.data();

		vkCmdBeginRenderPass(context->commandBuffers[i], &renderPassInfo, VK_SUBPASS_CONTENTS_INLINE);

		render(context->commandBuffers[i]);

		vkCmdEndRenderPass(context->commandBuffers[i]);

		VK_CHECK(vkEndCommandBuffer(context->commandBuffers[i]));
	}
}

void VulkanVisualization::destroySwapChain()
{
	vkDestroySwapchainKHR(context->device, context->swapChain, nullptr);
	context->swapChainImages.clear();
	context->swapChain = 0;
}

void VulkanVisualization::destroyImageViews()
{
	for (auto& i : context->swapChainImageViews)
	{
		context->resAllocator->destroyImageView(i);
	}
	context->swapChainImageViews.clear();
}

void VulkanVisualization::destroyRenderPass()
{
	vkDestroyRenderPass(context->device, context->renderPass, nullptr);
}

void VulkanVisualization::destroyDepthResources()
{
	context->resAllocator->destroyImageView(context->depthImageView);
	context->resAllocator->destroyImage(context->depthImage, context->depthMemory);
}

void VulkanVisualization::destroyFramebuffers()
{
	for (auto& f : context->frameBuffers)
	{
		context->resAllocator->destroyFramebuffer(f);
	}
}

void VulkanVisualization::recreateSwapChain()
{
	vkDeviceWaitIdle(context->device);

	destroySwapChain();
	destroyImageViews();
	destroyRenderPass();
	destroyDepthResources();
	destroyPipeline();
	destroyFramebuffers();
	createSwapChain();
	createImageViews();
	createRenderPass();
	createDepthResources();
	createPipeline();
	createFramebuffers();
}

void VulkanVisualization::uploadData(int bufferIndex)
{
	VkCommandBuffer& cmdBuffer = context->transferCommands[bufferIndex];

	VkCommandBufferBeginInfo beginInfo =
		init::CommandBufferBeginInfo();
	beginInfo.flags = VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT;

	vkBeginCommandBuffer(cmdBuffer, &beginInfo);

	VkBufferCopy copyRegion = {};
	copyRegion.size = sizeGPU * sizeof(float);
	vkCmdCopyBuffer(cmdBuffer, dataBlock->stagingBuffer, dataBlock->deviceBuffer, 1, &copyRegion);

	vkEndCommandBuffer(cmdBuffer);
	
}

void VulkanVisualization::onWindowResized(GLFWwindow * window, int width, int height)
{
	if (width == 0 || height == 0) return;

	VulkanVisualization* display = reinterpret_cast<VulkanVisualization*>(glfwGetWindowUserPointer(window));
	display->recreateSwapChain();
}