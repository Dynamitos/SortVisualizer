#include "resourceallocator.h"
#include "datamanager.h"
#include "utils.h"


ResourceAllocator::ResourceAllocator(VulkanContext* context) 
	: m_ChunkAllocator{ 1024 * 1024 * 1024 }
	, context(context)
{

	std::array<VkDescriptorPoolSize, 4> poolSizes;
	poolSizes[0].type = VK_DESCRIPTOR_TYPE_SAMPLED_IMAGE;
	poolSizes[0].descriptorCount = 256;
	poolSizes[1].type = VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER;
	poolSizes[1].descriptorCount = 256;
	poolSizes[2].type = VK_DESCRIPTOR_TYPE_INPUT_ATTACHMENT;
	poolSizes[2].descriptorCount = 256;
	poolSizes[3].type = VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER;
	poolSizes[3].descriptorCount = 256;

	VkDescriptorPoolCreateInfo poolInfo =
		init::DescriptorPoolCreateInfo(
			static_cast<uint32_t>(poolSizes.size()),
				poolSizes.data(),
				512);

	VK_CHECK(vkCreateDescriptorPool(context->device, &poolInfo, nullptr, &descriptorPool));
}

ResourceAllocator::ResourceAllocator(const ResourceAllocator & src) :
	m_ChunkAllocator{ 1024 * 1024 * 1024 }
{
	context = src.context;
	descriptorPool = src.descriptorPool;
}


ResourceAllocator::~ResourceAllocator()
{
	destroy();
}
/*
void ResourceAllocator::allocateTexture(std::string fileName, VkDescriptorSetLayout layout, uint32_t imageBinding, Texture* tex)
{
	int texWidth, texHeight, texChannels;
	std::string path = TEXTURE_PATH;
	path.append(fileName);
	stbi_uc* pixels = stbi_load(path.c_str(), &texWidth, &texHeight, &texChannels, 4);
	VkDeviceSize imageSize = texWidth * texHeight * 4;

	MemoryBlock stagingMemory;
	VkImage stagingImage;

	createImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_LINEAR, VK_IMAGE_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingImage, stagingMemory);
	createImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_SAMPLED_BIT | VK_IMAGE_USAGE_TRANSFER_DST_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, tex->image, tex->deviceMemory);
	
	vkMapMemory(context->device, stagingMemory.memory, stagingMemory.offset, VK_WHOLE_SIZE, 0, &stagingMemory.ptr);
	memcpy(stagingMemory.ptr, pixels, (size_t)imageSize);
	vkUnmapMemory(context->device, stagingMemory.memory);

	util::transitionImageLayout(stagingImage, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_TRANSFER_SRC_OPTIMAL);
	util::transferImageQueue(tex->image, VK_IMAGE_LAYOUT_PREINITIALIZED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	
	util::copyImage(stagingImage, tex->image, texWidth, texHeight);

	util::transitionImageLayout(tex->image, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL, context->indices.transferFamily, context->indices.graphicsFamily);
	
	stbi_image_free(pixels);

	createImageView(tex->image, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_ASPECT_COLOR_BIT, tex->imageView);

	VkSamplerCreateInfo samplerInfo =
		init::SamplerCreateInfo();
	samplerInfo.magFilter = VK_FILTER_LINEAR;
	samplerInfo.minFilter = VK_FILTER_LINEAR;
	samplerInfo.addressModeU = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeV = VK_SAMPLER_ADDRESS_MODE_REPEAT;
	samplerInfo.addressModeW = VK_SAMPLER_ADDRESS_MODE_REPEAT;

	samplerInfo.anisotropyEnable = VK_TRUE;
	samplerInfo.maxAnisotropy = 1.0f;
	samplerInfo.borderColor = VK_BORDER_COLOR_INT_OPAQUE_BLACK;
	samplerInfo.unnormalizedCoordinates = VK_FALSE;
	samplerInfo.compareEnable = VK_FALSE;
	samplerInfo.compareOp = VK_COMPARE_OP_ALWAYS;

	samplerInfo.mipmapMode = VK_SAMPLER_MIPMAP_MODE_LINEAR;
	samplerInfo.mipLodBias = 0.0f;
	samplerInfo.minLod = 0.0f;
	samplerInfo.maxLod = 0.0f;

	VK_CHECK(vkCreateSampler(context->device, &samplerInfo, nullptr, &tex->sampler));
	
	VkDescriptorSetAllocateInfo allocateInfo =
		init::DescriptorSetAllocateInfo(
			descriptorPool,
			&layout,
			1);
	VK_CHECK(vkAllocateDescriptorSets(context->device, &allocateInfo, &tex->descriptorSet));

	VkDescriptorImageInfo descImageInfo =
		init::DescriptorImageInfo(
			tex->sampler,
			tex->imageView,
			VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	VkWriteDescriptorSet imageWrite =
		init::WriteDescriptorSet(
			tex->descriptorSet,
			VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER,
			imageBinding,
			&descImageInfo);

	vkUpdateDescriptorSets(context->device, 1, &imageWrite, 0, nullptr);

	destroyImage(stagingImage, stagingMemory);
}

void ResourceAllocator::freeTexture(Texture * texture)
{
	vkDestroySampler(context->device, texture->sampler, nullptr);
	vkDestroyImageView(context->device, texture->imageView, nullptr);
	vkDestroyImage(context->device, texture->image, nullptr);
	deallocate(texture->deviceMemory);
}
*/
void ResourceAllocator::createFramebuffer(std::vector<VkImageView> attachments, VkFramebuffer & framebuffer)
{
	VkFramebufferCreateInfo createInfo =
		init::FramebufferCreateInfo(
			context->renderPass,
			static_cast<uint32_t>(attachments.size()),
			attachments.data(),
			context->swapChainExtent.width,
			context->swapChainExtent.height,
			1);
	VK_CHECK(vkCreateFramebuffer(context->device, &createInfo, nullptr, &framebuffer));
}

void ResourceAllocator::destroyFramebuffer(VkFramebuffer & framebuffer)
{
	vkDestroyFramebuffer(context->device, framebuffer, nullptr);
}


void ResourceAllocator::createBuffer(VkDeviceSize size, VkBufferUsageFlags usages, VkMemoryPropertyFlags properties, VkBuffer& buffer, MemoryBlock& memory)
{
	VkBufferCreateInfo createInfo =
		init::BufferCreateInfo(
			usages,
			size);
	VK_CHECK(vkCreateBuffer(context->device, &createInfo, nullptr, &buffer));

	VkMemoryRequirements requirements;
	vkGetBufferMemoryRequirements(context->device, buffer, &requirements);

	memory = allocate(requirements.size, requirements.alignment, util::findMemoryType(requirements.memoryTypeBits, properties));

	vkBindBufferMemory(context->device, buffer, memory.memory, memory.offset);
}

void ResourceAllocator::destroyBuffer(VkBuffer & buffer, MemoryBlock & block)
{
	vkDestroyBuffer(context->device, buffer, nullptr);

	deallocate(block);
}

void ResourceAllocator::createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage & image, MemoryBlock & imageMemory)
{
	VkImageCreateInfo imageInfo = {};
	imageInfo.sType = VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
	imageInfo.imageType = VK_IMAGE_TYPE_2D;
	imageInfo.extent.width = width;
	imageInfo.extent.height = height;
	imageInfo.extent.depth = 1;
	imageInfo.mipLevels = 1;
	imageInfo.arrayLayers = 1;
	imageInfo.format = format;
	imageInfo.tiling = tiling;
	imageInfo.initialLayout = VK_IMAGE_LAYOUT_PREINITIALIZED;
	imageInfo.usage = usage;
	imageInfo.samples = VK_SAMPLE_COUNT_1_BIT;
	imageInfo.sharingMode = VK_SHARING_MODE_EXCLUSIVE;
	//std::array<uint32_t, 2> queues = { context->indices.graphicsFamily, context->indices.transferFamily };
	//imageInfo.pQueueFamilyIndices = queues.data();
	//imageInfo.queueFamilyIndexCount = static_cast<uint32_t>(queues.size());

	VK_CHECK(vkCreateImage(context->device, &imageInfo, nullptr, &image));

	VkMemoryRequirements memRequirements;
	vkGetImageMemoryRequirements(context->device, image, &memRequirements);

	imageMemory = allocate(memRequirements.size, memRequirements.alignment, util::findMemoryType(memRequirements.memoryTypeBits, properties));
	
	vkBindImageMemory(context->device, image, imageMemory.memory, imageMemory.offset);

}

void ResourceAllocator::destroyImage(VkImage & image, MemoryBlock & imageMemory)
{
	vkDestroyImage(context->device, image, nullptr);

	deallocate(imageMemory);
}

void ResourceAllocator::createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VkImageView & imageView)
{
	VkImageViewCreateInfo viewInfo = {};
	viewInfo.sType = VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
	viewInfo.image = image;
	viewInfo.viewType = VK_IMAGE_VIEW_TYPE_2D;
	viewInfo.format = format;
	viewInfo.subresourceRange.aspectMask = aspectFlags;
	viewInfo.subresourceRange.baseMipLevel = 0;
	viewInfo.subresourceRange.levelCount = 1;
	viewInfo.subresourceRange.baseArrayLayer = 0;
	viewInfo.subresourceRange.layerCount = 1;

	VK_CHECK(vkCreateImageView(context->device, &viewInfo, nullptr, &imageView));
}

void ResourceAllocator::destroyImageView(VkImageView & imageView)
{
	vkDestroyImageView(context->device, imageView, nullptr);
}



UniformBuffer * ResourceAllocator::allocateUniformBuffer(VkDeviceSize size)
{
	UniformBuffer* buf = new UniformBuffer();

	createBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buf->stagingBuffer, buf->stagingMemory);

	createBuffer(size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buf->deviceBuffer, buf->deviceMemory);

		
	return buf;
}

void ResourceAllocator::deallocateUniformBuffer(UniformBuffer * buffer)
{
	vkDestroyBuffer(context->device, buffer->stagingBuffer, nullptr);
	vkDestroyBuffer(context->device, buffer->deviceBuffer, nullptr);

	deallocate(buffer->stagingMemory);
	deallocate(buffer->deviceMemory);
}

StorageBuffer* ResourceAllocator::allocateStorageBuffer(VkDeviceSize size)
{
	StorageBuffer* buf = new StorageBuffer();
	
	createBuffer(size, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, buf->stagingBuffer, buf->stagingMemory);

	createBuffer(size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT | VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_STORAGE_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, buf->deviceBuffer, buf->deviceMemory);

	return buf;
}
void ResourceAllocator::deallocateStorageBuffer(StorageBuffer * buffer)
{
	vkDestroyBuffer(context->device, buffer->stagingBuffer, nullptr);
	vkDestroyBuffer(context->device, buffer->deviceBuffer, nullptr);

	deallocate(buffer->deviceMemory);
	deallocate(buffer->stagingMemory);
}
MemoryBlock ResourceAllocator::allocate(VkDeviceSize size, VkDeviceSize alignment, int memoryTypeIndex)
{
	MemoryBlock block;
	for (auto &chunk : m_Chunks)
		if (chunk->memoryTypeIndex() == memoryTypeIndex)
			if (chunk->allocate(size, alignment, block))
				return block;

	m_Chunks.emplace_back(m_ChunkAllocator.allocate(size, memoryTypeIndex));
	m_Chunks.back()->allocate(size, alignment, block);
	return block;
}

void ResourceAllocator::deallocate(MemoryBlock & block)
{
	for (auto &chunk : m_Chunks)
	{
		if (chunk->isIn(block))
		{
			chunk->deallocate(block);
			return;
		}
	}
}

void ResourceAllocator::destroy()
{
	vkDestroyDescriptorPool(context->device, descriptorPool, nullptr);
	for (auto& m : m_Chunks)
	{
		m->destroy();
	}
}

bool MemoryBlock::operator==(MemoryBlock const & chunk)
{
	if (memory == chunk.memory &&
		offset == chunk.offset &&
		size == chunk.size &&
		free == chunk.free &&
		ptr == chunk.ptr)
		return true;
	return false;

}

MemoryChunk::MemoryChunk(VkDeviceSize size, int memoryTypeIndex):
	m_Size{ size },
	m_MemoryTypeIndex{ memoryTypeIndex } {
	m_context = DataManager::getInstance().getContext();

	VkMemoryAllocateInfo allocateInfo =
		init::MemoryAllocateInfo();
	allocateInfo.allocationSize = size;
	allocateInfo.memoryTypeIndex = memoryTypeIndex;

	MemoryBlock block;
	block.free = true;
	block.offset = 0;
	block.size = size;
	
	VK_CHECK(vkAllocateMemory(m_context->device, &allocateInfo, nullptr, &m_Memory));
	block.memory = m_Memory;
	
	VkPhysicalDeviceMemoryProperties memProperties;
	vkGetPhysicalDeviceMemoryProperties(m_context->physicalDevice, &memProperties);
	
	m_Blocks.emplace_back(block);
}

bool MemoryChunk::allocate(VkDeviceSize size, VkDeviceSize alignment, MemoryBlock & block)
{
	if (size > m_Size)
		return false;

	for (uint32_t i = 0; i < m_Blocks.size(); ++i)
	{
		if (m_Blocks[i].free)
		{
			VkDeviceSize newSize = m_Blocks[i].size;
			if (m_Blocks[i].offset % alignment != 0)
			{
				newSize -= alignment - m_Blocks[i].offset % alignment;
			}
			if (newSize >= size)
			{
				m_Blocks[i].size = newSize;
				if (m_Blocks[i].offset % alignment != 0)
				{
					m_Blocks[i].offset += alignment - m_Blocks[i].offset % alignment;
				}
				if (m_Ptr != nullptr)
					m_Blocks[i].ptr = (char*)m_Ptr + m_Blocks[i].offset;
				if (m_Blocks[i].size == size)
				{
					m_Blocks[i].free = false;
					block = m_Blocks[i];
					return true;
				}
				MemoryBlock nextBlock;
				nextBlock.free = true;
				nextBlock.offset = m_Blocks[i].offset + size;
				nextBlock.memory = m_Memory;
				nextBlock.size = m_Blocks[i].size - size;
				m_Blocks.emplace_back(nextBlock);

				m_Blocks[i].size = size;
				m_Blocks[i].free = false;

				block = m_Blocks[i];
				return true;
			}
		}
	}
	return false;
}

bool MemoryChunk::isIn(MemoryBlock const & block)
{
	for (auto b : m_Blocks)
	{
		if (b==block)
			return true;
	}
	return false;
}

void MemoryChunk::deallocate(MemoryBlock const & block)
{
	auto blockIt(std::find(m_Blocks.begin(), m_Blocks.end(), block));
	assert(blockIt != m_Blocks.end());

	blockIt->free = true;
}

int MemoryChunk::memoryTypeIndex() const
{
	return m_MemoryTypeIndex;
}

MemoryChunk::~MemoryChunk()
{
}
void MemoryChunk::destroy()
{
	vkFreeMemory(m_context->device, m_Memory, nullptr);
}
ChunkAllocator::ChunkAllocator(VkDeviceSize size):
	m_Size{ size }
{
}

ChunkAllocator::~ChunkAllocator()
{
}

inline AbstractAllocator::~AbstractAllocator()
{

}

std::unique_ptr<MemoryChunk> ChunkAllocator::allocate(VkDeviceSize size, int memoryTypeIndex)
{
	size = (size > m_Size) ? nextPowerOfTwo(size) : m_Size;

	return std::make_unique<MemoryChunk>(size, memoryTypeIndex);
}


VkDeviceSize nextPowerOfTwo(VkDeviceSize size) {
	VkDeviceSize power = static_cast<VkDeviceSize>(std::log2l(size) + 1);
	return (VkDeviceSize)1 << power;
}

bool isPowerOfTwo(VkDeviceSize size) {
	VkDeviceSize mask = 0;
	VkDeviceSize power = static_cast<VkDeviceSize>(std::log2l(size));

	for (VkDeviceSize i = 0; i < power; ++i)
		mask += (VkDeviceSize)1 << i;

	return !(size & mask);
}