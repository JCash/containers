#pragma once

#include <memory>
#include <cstdlib>

struct SMemoryStats
{
	size_t num_allocs;
	size_t peak_num_allocs;
	size_t alloc_size;
	size_t peak_alloc_size;
};


class allocator_base
{
public:
	static void reset()
	{
		stats.num_allocs = 0;
		stats.peak_num_allocs = 0;
		stats.alloc_size = 0;
		stats.peak_alloc_size = 0;
	}

	static void increase(size_t size)
	{
		++stats.num_allocs;
		stats.alloc_size += size;
		if( stats.alloc_size > stats.peak_alloc_size )
			stats.peak_alloc_size = stats.alloc_size;
		if( stats.num_allocs > stats.peak_num_allocs )
			stats.peak_num_allocs = stats.num_allocs;
	}
	static void decrease(size_t size)
	{
		--stats.num_allocs;
		stats.alloc_size -= size;
	}
	
	static void* malloc(size_t size)
	{
		increase(size);
		return std::malloc(size);
	}
	
	static void free(void* p)
	{
		//decrease(size);
		return std::free(p);
	}

	static SMemoryStats stats;
};

#if defined(malloc)
	#undef malloc
	#define malloc(_SIZE)	allocator_base::malloc(_SIZE)
#endif

#if defined(free)
	#undef free
	#define free(_POINTER)	allocator_base::free(_POINTER)
#endif

#if defined(IMPL_ALLOCATOR_STL)

template<typename T>
class Allocator : public allocator_base
{
public :
    //    typedefs
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

public :
    //    convert an Allocator<T> to Allocator<U>
    template<typename U>
    struct rebind
    {
        typedef Allocator<U> other;
    };

public :
    inline explicit Allocator() {}
    inline ~Allocator() {}
    inline explicit Allocator(Allocator const&) {}
    template<typename U>
    inline explicit Allocator(Allocator<U> const&) {}

    //    address
    inline pointer address(reference r) { return &r; }
    inline const_pointer address(const_reference r) { return &r; }

    //    memory allocation
    inline pointer allocate(size_type cnt, typename std::allocator<void>::const_pointer = 0)
    {
    	size_t size = cnt * sizeof (T);
    	increase(size);
    	return reinterpret_cast<pointer>(::operator new(size));
    }
    inline void deallocate(pointer p, size_type size)
    {
    	decrease(size);
        ::operator delete(p);
    }

    //    size
    inline size_type max_size() const
    {
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }

    //    construction/destruction
    inline void construct(pointer p, const T& t) { new(p) T(t); }
    inline void destroy(pointer p) { p->~T(); }

    inline bool operator==(Allocator const&) { return true; }
    inline bool operator!=(Allocator const& a) { return !operator==(a); }
};

#elif defined(IMPL_ALLOCATOR_EASTL)

#define EASTL_USER_DEFINED_ALLOCATOR 1 // Must declare this to avoid new[]/delete[] prototypes in Allocator.h
#define EASTL_ALLOCATOR_DEFAULT_NAME "CustomAlloc"
#define EASTLAllocatorType CustomAllocator::Allocator
#define EASTLAllocatorDefault CustomAllocator::GetDefaultAllocator

#include <stdio.h>
#include <stdlib.h>

namespace CustomAllocator {

// Define our Allocator class and implement it
class Allocator : allocator_base
{
public:
	// Constructors
	inline Allocator(const char* = 0) {}
	inline Allocator(const Allocator&) {}
	inline Allocator(const Allocator&, const char*) {}

	// Assignment
	inline Allocator& operator=(const Allocator&) { return *this; }

	// Allocation & Deallocation
	inline void* allocate(size_t n, int flags = 0)
	{
		increase(n);
		return ::malloc(n);
	}
	inline void* allocate(size_t n, size_t alignment, size_t offset, int flags = 0)
	{
		char* mem = NULL;
		increase(n);
		posix_memalign((void**)&mem, alignment, n);
		return mem;
	}

	inline void deallocate(void* p, size_t n)
	{
		decrease(n);
		::free(p);
	}

	// Name info
	inline const char* get_name() const
	{
		return EASTL_ALLOCATOR_DEFAULT_NAME;
	}
	inline void set_name(const char*) {}

	friend inline bool operator==(const Allocator& a, const Allocator& b) { return true; }
	friend inline bool operator!=(const Allocator& a, const Allocator& b) { return false; }
};

extern Allocator* GetDefaultAllocator();
extern Allocator* SetDefaultAllocator(Allocator* pNewAlloc);

};

#elif defined(IMPL_ALLOCATOR_BOOST)

#include <boost/container/detail/alloc_lib.h>
#include <boost/container/allocator.hpp>
#include <boost/container/detail/dlmalloc.hpp>

namespace boost {
namespace container {

struct true_type { enum { value = true }; };

template<typename T> 
class Allocator {
public:
	// types
	typedef T                      value_type;
	typedef T *                    pointer;
	typedef const T *              const_pointer;
	typedef T &                    reference;
	typedef const T &              const_reference;
	typedef std::size_t            size_type;
	typedef std::ptrdiff_t         difference_type;
	typedef true_type 			   propagate_on_container_move_assignment;  // A integral constant of type bool with value true. 
	typedef true_type 			   is_always_equal;                         // A integral constant of type bool with value true. 
	
	// member classes/structs/unions
	template<typename T2> 
	struct rebind {
	// types
		typedef Allocator< T2 > other;
	};
	
	// construct/copy/destruct
	Allocator() noexcept {}
	Allocator(const Allocator &) noexcept {}
	template<typename T2> Allocator(const Allocator< T2 > &) noexcept {}
	
	// public member functions
	pointer allocate(size_type bytes)
	{
		allocator_base::increase(bytes);
		return (pointer)( new uint8_t[bytes] );
	}
	void deallocate(pointer p, size_type bytes) noexcept
	{
		allocator_base::decrease(bytes);
		delete[] p;
	}
	size_type max_size() const noexcept	{ return std::numeric_limits<size_type>::max() / sizeof(T); }
	
	// friend functions
	friend void swap(Allocator&, Allocator&) noexcept {}
	friend bool operator==(const Allocator&, const Allocator&) noexcept { return true; }
	friend bool operator!=(const Allocator&, const Allocator&) noexcept	{ return false; }
};

} // container
} // boost


#else 

// use the new/delete functions

#endif

