#include "loader.h"


Loader::Loader(VulkanContext * context) :
	context{ context } {
}

Loader::~Loader()
{
	for (MeshBuffer* buf : buffers)
	{
		destroyMeshBuffer(buf);
		delete buf;
	}
}
MeshBuffer* Loader::createIndexBuffer(uint32_t* indices, VkDeviceSize indexCount)
{
	VkBuffer stagingBuffer;
	MemoryBlock stagingMemory;
	VkBuffer vertexBuffer;
	MemoryBlock vertexBufferMemory;
	VkDeviceSize byteSize = indexCount * sizeof(uint32_t);

	context->resAllocator->createBuffer(byteSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingMemory);

	void* data;
	vkMapMemory(context->device, stagingMemory.memory, stagingMemory.offset, byteSize, 0, &data);
	memcpy(data, indices, (size_t)byteSize);
	vkUnmapMemory(context->device, stagingMemory.memory);

	context->resAllocator->createBuffer(byteSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_INDEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

	util::copyBuffer(stagingBuffer, vertexBuffer, byteSize);
	context->resAllocator->destroyBuffer(stagingBuffer, stagingMemory);
	MeshBuffer* buffer = new MeshBuffer();
	buffer->buf = vertexBuffer;
	buffer->deviceMemory = vertexBufferMemory;
	buffer->size = static_cast<uint32_t>(indexCount);
	buffers.push_back(buffer);
	return buffer;
}
void Loader::destroyMeshBuffer(MeshBuffer* buffer)
{
	context->resAllocator->destroyBuffer(buffer->buf, buffer->deviceMemory);
}
MeshBuffer* Loader::createVertexBuffer(void* vertices, VkDeviceSize deviceSize, size_t vertexSize)
{
	VkBuffer stagingBuffer;
	MemoryBlock stagingMemory;
	VkBuffer vertexBuffer;
	MemoryBlock vertexBufferMemory;
	VkDeviceSize byteSize = deviceSize*vertexSize;

	context->resAllocator->createBuffer(byteSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingMemory);

	void* data;
	vkMapMemory(context->device, stagingMemory.memory, stagingMemory.offset, byteSize, 0, &data);
	memcpy(data, vertices, (size_t)byteSize);
	vkUnmapMemory(context->device, stagingMemory.memory);

	context->resAllocator->createBuffer(byteSize, VK_BUFFER_USAGE_TRANSFER_DST_BIT | VK_BUFFER_USAGE_VERTEX_BUFFER_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, vertexBuffer, vertexBufferMemory);

	util::copyBuffer(stagingBuffer, vertexBuffer, byteSize);
	context->resAllocator->destroyBuffer(stagingBuffer, stagingMemory);
	MeshBuffer* buffer = new MeshBuffer();
	buffer->buf = vertexBuffer;
	buffer->deviceMemory = vertexBufferMemory;
	buffer->size = static_cast<uint32_t>(vertexSize);
	buffers.push_back(buffer);
	return buffer;
}