#ifndef LOADER_H
#define LOADER_H
#include <memory>
#include <mutex>
#include "utils.h"
struct MeshBuffer
{
	VkBuffer buf;
	MemoryBlock deviceMemory;
	uint32_t size;
};
class Loader
{
public:
	Loader(VulkanContext* context);
	virtual ~Loader();
	MeshBuffer* createIndexBuffer(uint32_t* indices, VkDeviceSize indexCount);
	void destroyMeshBuffer(MeshBuffer* buffer);
	MeshBuffer* createVertexBuffer(void* vertices, VkDeviceSize vertexCount, size_t vertexSize);
private:
	VulkanContext* context;
	std::vector<MeshBuffer*> buffers;
};
#endif
