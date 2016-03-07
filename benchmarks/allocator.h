#pragma once

#include <memory>

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

	static SMemoryStats stats;
};

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

/**
template< class T
        , unsigned Version BOOST_CONTAINER_DOCONLY(=2)
        , unsigned int AllocationDisableMask BOOST_CONTAINER_DOCONLY(=0)>
class Allocator
{
   typedef unsigned int allocation_type;
   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   private:

   //Self type
   typedef Allocator<T, Version, AllocationDisableMask>   self_t;

   //Not assignable from related allocator
   template<class T2, unsigned int Version2, unsigned int AllocationDisableMask2>
   Allocator& operator=(const Allocator<T2, Version2, AllocationDisableMask2>&);

   //Not assignable from other allocator
   Allocator& operator=(const Allocator&);

   static const unsigned int ForbiddenMask =
      BOOST_CONTAINER_ALLOCATE_NEW | BOOST_CONTAINER_EXPAND_BWD | BOOST_CONTAINER_EXPAND_FWD ;

   //The mask can't disable all the allocation types
   BOOST_STATIC_ASSERT((  (AllocationDisableMask & ForbiddenMask) != ForbiddenMask  ));

   //The mask is only valid for version 2 allocators
   BOOST_STATIC_ASSERT((  Version != 1 || (AllocationDisableMask == 0)  ));

   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   public:
   typedef T                                    value_type;
   typedef T *                                  pointer;
   typedef const T *                            const_pointer;
   typedef T &                                  reference;
   typedef const T &                            const_reference;
   typedef std::size_t                          size_type;
   typedef std::ptrdiff_t                       difference_type;

   typedef boost::container::container_detail::
      version_type<self_t, Version>                version;

   #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
   typedef boost::container::container_detail::
         basic_multiallocation_chain<void*>        void_multiallocation_chain;

   typedef boost::container::container_detail::
      transform_multiallocation_chain
         <void_multiallocation_chain, T>           multiallocation_chain;
   #endif   //#ifndef BOOST_CONTAINER_DOXYGEN_INVOKED

   //!Obtains an allocator that allocates
   //!objects of type T2
   template<class T2>
   struct rebind
   {
      typedef Allocator<T2, Version, AllocationDisableMask> other;
   };

   //!Default constructor
   //!Never throws
   Allocator() BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Constructor from other allocator.
   //!Never throws
   Allocator(const Allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Constructor from related allocator.
   //!Never throws
   template<class T2>
   Allocator(const Allocator<T2
            #ifndef BOOST_CONTAINER_DOXYGEN_INVOKED
            , Version, AllocationDisableMask
            #endif
            > &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!Allocates memory for an array of count elements.
   //!Throws std::bad_alloc if there is no enough memory
   //!If Version is 2, this allocated memory can only be deallocated
   //!with deallocate() or (for Version == 2) deallocate_many()
   pointer allocate(size_type count, const void * hint= 0)
   {
      (void)hint;
      if(count > this->max_size())
         boost::container::throw_bad_alloc();
      void *ret = dlmalloc_malloc(count*sizeof(T));
      if(!ret)
         boost::container::throw_bad_alloc();
      allocator_base::increase(count*sizeof(T));
      return static_cast<pointer>(ret);
   }

   //!Deallocates previously allocated memory.
   //!Never throws
   void deallocate(pointer ptr, size_type size) BOOST_NOEXCEPT_OR_NOTHROW
   {
	   dlmalloc_free(ptr);
   	   allocator_base::decrease(size);
   }

   //!Returns the maximum number of elements that could be allocated.
   //!Never throws
   size_type max_size() const BOOST_NOEXCEPT_OR_NOTHROW
   {  return size_type(-1)/sizeof(T);   }

   //!Swaps two allocators, does nothing
   //!because this allocator is stateless
   friend void swap(self_t &, self_t &) BOOST_NOEXCEPT_OR_NOTHROW
   {}

   //!An allocator always compares to true, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator==(const Allocator &, const Allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return true;   }

   //!An allocator always compares to false, as memory allocated with one
   //!instance can be deallocated by another instance
   friend bool operator!=(const Allocator &, const Allocator &) BOOST_NOEXCEPT_OR_NOTHROW
   {  return false;   }

   //!An advanced function that offers in-place expansion shrink to fit and new allocation
   //!capabilities. Memory allocated with this function can only be deallocated with deallocate()
   //!or deallocate_many().
   //!This function is available only with Version == 2
   pointer allocation_command(allocation_type command,
                         size_type limit_size,
                         size_type &prefer_in_recvd_out_size,
                         pointer &reuse)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      const allocation_type mask(AllocationDisableMask);
      command &= ~mask;
      pointer ret = this->priv_allocation_command(command, limit_size, prefer_in_recvd_out_size, reuse);
      if(!ret && !(command & BOOST_CONTAINER_NOTHROW_ALLOCATION))
         boost::container::throw_bad_alloc();
      return ret;
   }

   //!Returns maximum the number of objects the previously allocated memory
   //!pointed by p can hold.
   //!Memory must not have been allocated with
   //!allocate_one or allocate_individual.
   //!This function is available only with Version == 2
   size_type size(pointer p) const BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      return dlmalloc_size(p);
   }

   //!Allocates just one object. Memory allocated with this function
   //!must be deallocated only with deallocate_one().
   //!Throws bad_alloc if there is no enough memory
   //!This function is available only with Version == 2
   pointer allocate_one()
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      return this->allocate(1);
   }

   //!Allocates many elements of size == 1.
   //!Elements must be individually deallocated with deallocate_one()
   //!This function is available only with Version == 2
   void allocate_individual(std::size_t num_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      this->allocate_many(1, num_elements, chain);
   }

   //!Deallocates memory previously allocated with allocate_one().
   //!You should never use deallocate_one to deallocate memory allocated
   //!with other functions different from allocate_one() or allocate_individual.
   //Never throws
   void deallocate_one(pointer p) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      return this->deallocate(p, 1);
   }

   //!Deallocates memory allocated with allocate_one() or allocate_individual().
   //!This function is available only with Version == 2
   void deallocate_individual(multiallocation_chain &chain) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      return this->deallocate_many(chain);
   }

   //!Allocates many elements of size elem_size.
   //!Elements must be individually deallocated with deallocate()
   //!This function is available only with Version == 2
   void allocate_many(size_type elem_size, std::size_t n_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      allocator_base::increase(n_elements*elem_size*sizeof(T));
      if(!dlmalloc_multialloc_nodes(n_elements, elem_size*sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, reinterpret_cast<dlmalloc_memchain *>(&chain))){
         boost::container::throw_bad_alloc();
      }
   }

   //!Allocates n_elements elements, each one of size elem_sizes[i]
   //!Elements must be individually deallocated with deallocate()
   //!This function is available only with Version == 2
   void allocate_many(const size_type *elem_sizes, size_type n_elements, multiallocation_chain &chain)
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      dlmalloc_memchain ch;
      BOOST_CONTAINER_MEMCHAIN_INIT(&ch);
      assert(false && "not implemented");
      //allocator_base::increase(n_elements*elem_size*sizeof(T));
      if(!dlmalloc_multialloc_arrays(n_elements, elem_sizes, sizeof(T), DL_MULTIALLOC_DEFAULT_CONTIGUOUS, &ch)){
         boost::container::throw_bad_alloc();
      }
      chain.incorporate_after(chain.before_begin()
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_FIRSTMEM(&ch)
                             ,(T*)BOOST_CONTAINER_MEMCHAIN_LASTMEM(&ch)
                             ,BOOST_CONTAINER_MEMCHAIN_SIZE(&ch) );
   }

   //!Deallocates several elements allocated by
   //!allocate_many(), allocate(), or allocation_command().
   //!This function is available only with Version == 2
   void deallocate_many(multiallocation_chain &chain) BOOST_NOEXCEPT_OR_NOTHROW
   {
      BOOST_STATIC_ASSERT(( Version > 1 ));
      dlmalloc_memchain ch;
      void *beg(&*chain.begin()), *last(&*chain.last());
      size_t size(chain.size());
      BOOST_CONTAINER_MEMCHAIN_INIT_FROM(&ch, beg, last, size);
      dlmalloc_multidealloc(&ch);
      //dlmalloc_multidealloc(reinterpret_cast<dlmalloc_memchain *>(&chain));
   }

   private:

   pointer priv_allocation_command
      (allocation_type command,    std::size_t limit_size
      ,size_type &prefer_in_recvd_out_size
      ,pointer &reuse_ptr)
   {
      std::size_t const preferred_size = prefer_in_recvd_out_size;
      dlmalloc_command_ret_t ret = {0 , 0};
      if((limit_size > this->max_size()) | (preferred_size > this->max_size())){
         return pointer();
      }
      std::size_t l_size = limit_size*sizeof(T);
      std::size_t p_size = preferred_size*sizeof(T);
      std::size_t r_size;
      {
         void* reuse_ptr_void = reuse_ptr;
         ret = dlmalloc_allocation_command(command, sizeof(T), l_size, p_size, &r_size, reuse_ptr_void);
         reuse_ptr = ret.second ? static_cast<T*>(reuse_ptr_void) : 0;
      }
      prefer_in_recvd_out_size = r_size/sizeof(T);
      return (pointer)ret.first;
   }
};
*/

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

