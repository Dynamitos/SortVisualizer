#include "hostallocator.h"
#include <string>
#include <memory>
#include <iostream>

void *VKAPI_CALL HostAllocator::Allocation(void * pUserData, size_t size, size_t alignment, VkSystemAllocationScope allocationScope)
{
	return static_cast<HostAllocator*>(pUserData)->Allocation(size,
		alignment,
		allocationScope);
}

void *VKAPI_CALL HostAllocator::Reallocation(void * pUserData, void * pOriginal, size_t size, size_t alignment, VkSystemAllocationScope allocationScope)
{
	return static_cast<HostAllocator*>(pUserData)->Reallocation(pOriginal,
		size,
		alignment,
		allocationScope);
}

void VKAPI_CALL HostAllocator::Free(void * pUserData, void * pMemory)
{
	return static_cast<HostAllocator*>(pUserData)->Free(pMemory);
}

void * HostAllocator::Allocation(size_t size, size_t alignment, VkSystemAllocationScope allocationScope)
{
	/*std::string scope;
	switch (allocationScope) {
	case VK_SYSTEM_ALLOCATION_SCOPE_CACHE:
	scope = "cache";
	break;
	case VK_SYSTEM_ALLOCATION_SCOPE_DEVICE:
	scope = "device";
	break;
	case VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE:
	scope = "instance";
	break;
	case VK_SYSTEM_ALLOCATION_SCOPE_OBJECT:
	scope = "object";
	break;
	}*/
	//std::cout << "allocating: " << size << " bytes with alignment " << alignment << std::endl;
	return _aligned_malloc(size, alignment);
}

void * HostAllocator::Reallocation(void * pOriginal, size_t size, size_t alignment, VkSystemAllocationScope allocationScope)
{
	/*std::string scope;
	switch (allocationScope) {
	case VK_SYSTEM_ALLOCATION_SCOPE_CACHE:
	scope = "cache";
	break;
	case VK_SYSTEM_ALLOCATION_SCOPE_DEVICE:
	scope = "device";
	break;
	case VK_SYSTEM_ALLOCATION_SCOPE_INSTANCE:
	scope = "instance";
	break;
	case VK_SYSTEM_ALLOCATION_SCOPE_OBJECT:
	scope = "object";
	break;
	}
	std::cout << "reallocating: " << size << " bytes with alignment" << alignment << " in scope " << scope.c_str() << std::endl;*/
	return _aligned_realloc(pOriginal, size, alignment);
}

void HostAllocator::Free(void * pMemory)
{
	_aligned_free(pMemory);
}
