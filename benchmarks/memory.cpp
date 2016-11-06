#include "memory.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <unistd.h>
#include <malloc/malloc.h>

typedef volatile uint64_t uint64_atomic_t;

static uint64_atomic_t total = 0;
static uint64_atomic_t allocations = 0;

inline void AtomicAdd(uint64_atomic_t* counter, uint64_t value)
{
    __sync_fetch_and_add(counter, (uint64_t)value);
}

inline void AtomicSub(uint64_atomic_t* counter, uint64_t value)
{
    __sync_fetch_and_sub(counter, (uint64_t)value);
}

typedef void* (*malloc_t)(size_t);
typedef void (*free_t)(void*);
typedef void* (*calloc_t)(size_t, size_t);
typedef void* (*realloc_t)(void*, size_t);
typedef void* (*memalign_t)(size_t, size_t);

static malloc_t     real_malloc = 0;
static free_t       real_free = 0;
static calloc_t     real_calloc = 0;
static realloc_t    real_realloc = 0;
static memalign_t   real_memalign = 0;

#define DLSYM( _TGT, _TYPE, _NAME ) \
    (_TGT) = (_TYPE)dlsym(RTLD_NEXT, _NAME); \
    if ((error = dlerror()) != NULL) { \
        write(2, error, strlen(error)); \
        exit(1); \
    }

void InitMemoryHooks()
{
    char* error = 0;
    DLSYM( real_malloc, malloc_t, "malloc" );
    DLSYM( real_free, free_t, "free" );
    DLSYM( real_calloc, calloc_t, "calloc" );
    DLSYM( real_realloc, realloc_t, "realloc" );
    //DLSYM( real_memalign, memalign_t, "posix_memalign" );

    ResetMemoryStats();
}

void ResetMemoryStats()
{
    total = 0;
    allocations = 0;
}

void GetMemoryStats(size_t& num_allocs, size_t& alloc_size)
{
    num_allocs = allocations;
    alloc_size = total;
}



#define CHECK_INIT()  if(!real_malloc ) { InitMemoryHooks(); }


extern "C"
void* malloc(size_t size)
{
    CHECK_INIT();

    void* ptr = real_malloc(size);

    size_t usablesize = malloc_size(ptr);
    AtomicAdd(&total, usablesize);
    AtomicAdd(&allocations, 1);

    return ptr;
}

extern "C"
void* calloc(size_t count, size_t size)
{
    CHECK_INIT();

    void* ptr = real_calloc(count, size);
    size_t usablesize = malloc_size(ptr);
 
    AtomicAdd(&total, usablesize);
    AtomicAdd(&allocations, 1);
    return ptr;
}

extern "C"
void* realloc(void* ptr, size_t size)
{
    CHECK_INIT();

    if( ptr == 0 )
    {
        return malloc(size);
    }

    size_t usablesize = malloc_size(ptr);
    AtomicSub(&total, usablesize);

    ptr = real_realloc(ptr, size);

    usablesize = malloc_size(ptr);
    AtomicAdd(&total, usablesize);
    AtomicAdd(&allocations, 1);

    return ptr;
}

extern "C"
void free(void* ptr)
{
    CHECK_INIT();

    real_free(ptr);
}

extern "C"
void* reallocf(void *ptr, size_t size)
{
    free(ptr);
    return malloc(size);
}

extern "C"
void* memalign(size_t alignment, size_t size)
{
    CHECK_INIT();

    void* ptr = real_memalign(alignment, size);

    size_t usablesize = malloc_size(ptr);
    AtomicAdd(&total, usablesize);
    AtomicAdd(&allocations, 1);

    return ptr;
}

void* operator new(size_t size)
{
    return malloc(size);
}

void operator delete(void* ptr) noexcept
{
    free(ptr);
}

void* operator new[](size_t size)
{
    return malloc(size);
}

void operator delete[](void* ptr) noexcept
{
    free(ptr);
}
