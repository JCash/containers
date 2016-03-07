#include "Allocator.h"

SMemoryStats allocator_base::stats;

#if defined(IMPL_ALLOCATOR_NEW)
#include <stdlib.h>


void* operator new(size_t size) {
	size_t* mem = (size_t*)malloc(size+sizeof(size_t));
    *mem = size;
    allocator_base::increase(size);
    return (void*)(mem+1);
}

void* operator new[](size_t size) {
	size_t* mem = (size_t*)malloc(size+sizeof(size_t));
    *mem = size;
    allocator_base::increase(size);
    return (void*)(mem+1);
}

void operator delete(void* p) noexcept {
	size_t* mem = ((size_t*)p) - 1;
	size_t size = *mem;
	allocator_base::decrease(size);
    free((void*)mem);
}

void operator delete[](void* p) noexcept {
	size_t* mem = ((size_t*)p) - 1;
	size_t size = *mem;
	allocator_base::decrease(size);
    free((void*)mem);
}


#elif defined(IMPL_ALLOCATOR_EASTL)

namespace CustomAllocator
{

// Defines the EASTL API glue, so we can set our Allocator as the global default Allocator
Allocator  gDefaultAllocator;
Allocator* gpDefaultAllocator = &gDefaultAllocator;


Allocator* GetDefaultAllocator()
{
	return gpDefaultAllocator;
}

Allocator* SetDefaultAllocator(Allocator* pNewAlloc)
{
	Allocator* pOldAlloc = gpDefaultAllocator;
	gpDefaultAllocator = pNewAlloc;
	return pOldAlloc;
}

} // namespace

#endif
