#pragma once
#include <mutex>
#include <vector>
#include <vulkan\vulkan.h>
class Texture;
class ArrayTexture;
struct VulkanContext;
struct UniformBuffer;
struct StorageBuffer;


struct MemoryBlock
{
	VkDeviceMemory memory;
	VkDeviceSize offset;
	VkDeviceSize size;
	bool free;
	void *ptr = nullptr;

	bool operator==(MemoryBlock const &chunk);
};
class MemoryChunk {
public:
	MemoryChunk(VkDeviceSize size, int memoryTypeIndex);

	bool allocate(VkDeviceSize size, VkDeviceSize alignment, MemoryBlock &block);
	bool isIn(MemoryBlock const &block);
	void deallocate(MemoryBlock const &block);
	int memoryTypeIndex() const;
	void destroy();

	~MemoryChunk();
protected:
	VulkanContext* m_context;
	VkDeviceMemory m_Memory = VK_NULL_HANDLE;
	VkDeviceSize m_Size;
	int m_MemoryTypeIndex;
	std::vector<MemoryBlock> m_Blocks;
	void *m_Ptr = nullptr;
};
class ChunkAllocator
{
public:
	ChunkAllocator(VkDeviceSize size);
	~ChunkAllocator();
	std::unique_ptr<MemoryChunk> allocate(VkDeviceSize size, int memoryTypeIndex);

private:
	VkDeviceSize m_Size;
};
class AbstractAllocator
{
public:
	virtual MemoryBlock allocate(VkDeviceSize size, VkDeviceSize alignmemt, int memoryTypeIndex) = 0;
	virtual void deallocate(MemoryBlock &block) = 0;

	virtual ~AbstractAllocator() = 0;
};
VkDeviceSize nextPowerOfTwo(VkDeviceSize size);

bool isPowerOfTwo(VkDeviceSize size);

class ResourceAllocator : public AbstractAllocator
{
public:
	ResourceAllocator(VulkanContext* context);
	ResourceAllocator(const ResourceAllocator& src);
	virtual ~ResourceAllocator();
	//void allocateTexture(std::string fileName, VkDescriptorSetLayout layout, uint32_t imageBinding, Texture* tex);
	//void freeTexture(Texture* texture);
	void createBuffer(VkDeviceSize size, VkBufferUsageFlags usages, VkMemoryPropertyFlags properties, VkBuffer& buffer, MemoryBlock& memory);
	void destroyBuffer(VkBuffer& buffer, MemoryBlock& block);
	void createImage(uint32_t width, uint32_t height, VkFormat format, VkImageTiling tiling, VkImageUsageFlags usage, VkMemoryPropertyFlags properties, VkImage & image, MemoryBlock & imageMemory);
	void destroyImage(VkImage & image, MemoryBlock & imageMemory);
	void createImageView(VkImage image, VkFormat format, VkImageAspectFlags aspectFlags, VkImageView& imageView);
	void destroyImageView(VkImageView& imageView);
	void createFramebuffer(std::vector<VkImageView> attachments, VkFramebuffer& framebuffer);
	void destroyFramebuffer(VkFramebuffer& framebuffer);
	StorageBuffer* allocateStorageBuffer(VkDeviceSize size);
	void deallocateStorageBuffer(StorageBuffer* buffer);
	UniformBuffer* allocateUniformBuffer(VkDeviceSize size);
	void deallocateUniformBuffer(UniformBuffer* buffer);
	MemoryBlock allocate(VkDeviceSize size, VkDeviceSize alignment, int memoryTypeIndex);
	void deallocate(MemoryBlock &block);

	void destroy();
private:
	VulkanContext* context;
	VkDescriptorPool descriptorPool;
	ChunkAllocator m_ChunkAllocator;
	std::vector<std::shared_ptr<MemoryChunk>> m_Chunks;
};