#pragma once
#include <vulkan/vulkan.h>
class HostAllocator
{
public:
	inline operator VkAllocationCallbacks() const
	{
		VkAllocationCallbacks result;
		result.pUserData = (void*)this;
		result.pfnAllocation = &HostAllocator::Allocation;
		result.pfnReallocation = &HostAllocator::Reallocation;
		result.pfnFree = &HostAllocator::Free;
		result.pfnInternalAllocation = nullptr;
		result.pfnInternalFree = nullptr;
		return result;
	}
private:
	//std::vector<void> m_ObjectHeap;
	//std::vector<void> m_CacheHeap;
	//std::vector<void> m_DeviceHeap;
	//std::vector<void> m_InstanceHeap;
	static void* VKAPI_CALL Allocation(
		void*									pUserData,
		size_t									size,
		size_t									alignment,
		VkSystemAllocationScope					allocationScope);

	static void* VKAPI_CALL Reallocation(
		void*									pUserData,
		void*									pOriginal,
		size_t									size,
		size_t									alignment,
		VkSystemAllocationScope					allocationScope);

	static void VKAPI_CALL Free(
		void*									pUserData,
		void*									pMemory);

	void* Allocation(
		size_t									size,
		size_t									alignment,
		VkSystemAllocationScope					allocationScope);

	void* Reallocation(
		void*									pOriginal,
		size_t									size,
		size_t									alignment,
		VkSystemAllocationScope					allocationScope);

	void Free(
		void*									pMemory);
};

