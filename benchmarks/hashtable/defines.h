#pragma once

#include "../allocator.h"

typedef uint64_t 	keey_t;	// because iostream defines a key_t
typedef uint64_t 	value_t;

const uint32_t		MAX_LOAD_FACTOR = 95;  // percent 

#if defined(IMPL_STL_MAP) || defined(IMPL_STL_UNORDERED_MAP)
	#ifdef IMPL_STL_UNORDERED_MAP
		#include <unordered_map>
		#define CONTAINERNAME "std::unordered_map"
		typedef std::unordered_map<keey_t, value_t, std::hash<keey_t>, std::equal_to<keey_t>, Allocator<std::pair<const keey_t, value_t>>> hashtable_t;
	#else
		#include <map>
		#define CONTAINERNAME "std::map"
		typedef std::map<keey_t, value_t, std::less<keey_t>, Allocator<std::pair<const keey_t, value_t>>> hashtable_t;
	#endif
	typedef hashtable_t::const_iterator iterator_t;
	#define STL_LIKE_CONTAINER 1

#elif defined(IMPL_EASTL_HASH_MAP)
	#define CONTAINERNAME "eastl::hash_map"
	#include <EASTL/hash_map.h>
	//typedef eastl::hash_map<keey_t, value_t, eastl::hash<keey_t>, eastl::equal_to<keey_t>, CustomAllocator::Allocator> hashtable_t;
	typedef eastl::hash_map<keey_t, value_t> hashtable_t;
	typedef hashtable_t::const_iterator iterator_t;	
	#define STL_LIKE_CONTAINER 1

#elif defined(IMPL_BOOST_UNORDERED_MAP)
	#define CONTAINERNAME "boost::unordered_map"
	#include <boost/unordered_map.hpp>
	//typedef boost::unordered_map<keey_t, value_t, boost::hash<keey_t>, std::equal_to<keey_t>, boost::container::Allocator<std::pair<const keey_t, value_t>>> hashtable_t;
	typedef boost::unordered_map<keey_t, value_t> hashtable_t;
	typedef hashtable_t::const_iterator iterator_t;
	#define STL_LIKE_CONTAINER 1

#elif defined(IMPL_BOOST_FLAT_MAP)
	#define CONTAINERNAME "boost::flat_map"
	#include <boost/container/flat_map.hpp>
	//typedef boost::container::flat_map<keey_t, value_t, std::less<keey_t>, boost::container::Allocator< std::pair<keey_t, value_t> >> hashtable_t;
	typedef boost::container::flat_map<keey_t, value_t> hashtable_t;
	typedef hashtable_t::const_iterator iterator_t;
	#define STL_LIKE_CONTAINER 1
	
#elif defined(IMPL_GOOGLE_SPARSEHASHMAP)
	#define CONTAINERNAME "google::sparse_hash_map"
	#include <sparsehash/sparse_hash_map>
	typedef google::sparse_hash_map<keey_t, value_t> hashtable_t;
	typedef hashtable_t::const_iterator iterator_t;
	#define GOOGLE_LIKE_CONTAINER 1
	
#elif defined(IMPL_GOOGLE_DENSEHASHMAP)
	#define CONTAINERNAME "google::dense_hash_map"
	#include <sparsehash/dense_hash_map>
	typedef google::dense_hash_map<keey_t, value_t> hashtable_t;
	//typedef google::dense_hash_map<keey_t, value_t, SPARSEHASH_HASH<keey_t>, std::equal_to<keey_t>, Allocator<std::pair<const keey_t, value_t>>> hashtable_t;
	typedef hashtable_t::const_iterator iterator_t;
	#define GOOGLE_LIKE_CONTAINER 1
	
#elif defined(IMPL_JC_HASHTABLE_CH) || defined(IMPL_JC_HASHTABLE_OA) || defined(IMPL_JC_HASHTABLE_RH)
	#if defined(IMPL_JC_HASHTABLE_CH)
		#include "../../src/hashtable_ch.h"
		#define CONTAINERNAME "jc::hashtable_ch"
	#elif defined(IMPL_JC_HASHTABLE_OA)
		#include "../../src/hashtable_oa.h"
		#define CONTAINERNAME "jc::hashtable_oa"
	#else
		#include "../../src/hashtable.h"
		#define CONTAINERNAME "jc::hashtable"
	#endif
	typedef jc::HashTable<keey_t, value_t> hashtable_t;
	typedef hashtable_t::Iterator iterator_t;

	inline void Init( hashtable_t& ht, uint32_t numelements )
	{
		(void)numelements;
		uint32_t tablesize = uint32_t(numelements / (MAX_LOAD_FACTOR/100.0f));

#if defined(IMPL_JC_HASHTABLE_CH)
		void* mem = new uint8_t[ hashtable_t::CalcSize( tablesize, numelements ) ];
		ht.Create(tablesize, numelements, mem);
#else
		void* mem = new uint8_t[ hashtable_t::CalcSize( tablesize ) ];
		ht.Create(tablesize, 0xBAADC0DEF00DF17E, mem);
#endif
	}
	inline void Clear( hashtable_t& ht )
	{
		ht.Clear();
	}
	inline size_t Size( hashtable_t& ht )
	{
		return ht.Size();
	}
	inline bool Empty( hashtable_t& ht )
	{
		return ht.Empty();
	}
	inline void Put( hashtable_t& ht, keey_t key, value_t value)
	{
		ht.Put( key, value );
	}
	inline value_t Get( hashtable_t& ht, keey_t key)
	{
		return *ht.Get( key );
	}
	inline void Erase( hashtable_t& ht, keey_t key)
	{
		ht.Erase( key );
	}
	inline iterator_t IteratorBegin(hashtable_t& ht)
	{
		return ht.Begin();
	}
	inline iterator_t IteratorEnd(hashtable_t& ht)
	{
		return ht.End();
	}
	inline keey_t IteratorGetKey(hashtable_t&, iterator_t& it)
	{
		return *it.GetKey();
	}
	inline value_t IteratorGetValue(hashtable_t&, iterator_t& it)
	{
		return *it.GetValue();
	}
	inline void IteratorNext(hashtable_t&, iterator_t& it)
	{
		++it;
	}
	
#elif defined(IMPL_DM_HASHTABLE)
	#include "../memory.h"
	#include "../../src/dmhashtable.h"
	#define CONTAINERNAME "dmHashTable"
	typedef dmHashTable<keey_t, value_t> hashtable_t;

	inline void Init( hashtable_t& ht, uint32_t numelements )
	{
		uint32_t tablesize = uint32_t(numelements / (MAX_LOAD_FACTOR/100.0f));
		ht.SetCapacity(tablesize, numelements);
		ht.Clear();
	}
	inline void Clear( hashtable_t& ht )
	{
		ht.Clear();
	}
	inline size_t Size( hashtable_t& ht )
	{
		return ht.Size();
	}
	inline bool Empty( hashtable_t& ht )
	{
		return ht.Empty();
	}
	inline void Put( hashtable_t& ht, keey_t key, value_t value)
	{
		ht.Put( key, value );
	}
	inline value_t Get( hashtable_t& ht, keey_t key)
	{
		return *ht.Get( key );
	}
	inline void Erase( hashtable_t& ht, keey_t key)
	{
		ht.Erase( key );
	}
	
#endif
	
#ifdef GOOGLE_LIKE_CONTAINER
	inline void Init( hashtable_t& ht, uint32_t numelements )
	{
		(void)numelements;
		hashtable_t httemp;
		ht.clear();
		std::swap(httemp, ht);
		ht.set_deleted_key(0xbaadc0deF00DF17E);
	#ifdef IMPL_GOOGLE_DENSEHASHMAP
		ht.set_empty_key(0xbaadcafeF00DF17E);
		ht.resize(numelements);
	#endif
	}
	inline void Clear( hashtable_t& ht )
	{
		ht.clear();
	}
	inline size_t Size( hashtable_t& ht )
	{
		return ht.size();
	}
	inline bool Empty( hashtable_t& ht )
	{
		return ht.empty();
	}
	inline void Put( hashtable_t& ht, keey_t key, value_t value)
	{
		ht[key] = value;
	}
	inline value_t Get( hashtable_t& ht, keey_t key)
	{
		return ht[key];
	}
	inline void Erase( hashtable_t& ht, keey_t key)
	{
		ht.erase( key );
	}
	inline iterator_t IteratorBegin(hashtable_t& ht)
	{
		return ht.begin();
	}
	inline iterator_t IteratorEnd(hashtable_t& ht)
	{
		return ht.end();
	}
	inline keey_t IteratorGetKey(hashtable_t&, iterator_t& it)
	{
		return it->first;
	}
	inline value_t IteratorGetValue(hashtable_t&, iterator_t& it)
	{
		return it->second;
	}
	inline void IteratorNext(hashtable_t&, iterator_t& it)
	{
		++it;
	}
#endif

#ifdef STL_LIKE_CONTAINER
	inline void Init( hashtable_t& ht, uint32_t numelements )
	{
		(void)numelements;
		hashtable_t httemp;
		ht.clear();
		std::swap(httemp, ht);
#if defined(IMPL_BOOST_FLAT_MAP) || defined(IMPL_SHERWOODMAP)
		ht.reserve(numelements);
#endif
	}
	inline void Clear( hashtable_t& ht )
	{
		ht.clear();
	}
	inline size_t Size( hashtable_t& ht )
	{
		return ht.size();
	}
	inline bool Empty( hashtable_t& ht )
	{
		return ht.empty();
	}
	inline void Put( hashtable_t& ht, keey_t key, value_t value)
	{
		ht[key] = value;
	}
	inline value_t Get( hashtable_t& ht, keey_t key)
	{
		return ht[key];
	}
	inline void Erase( hashtable_t& ht, keey_t key)
	{
		ht.erase( key );
	}
	inline iterator_t IteratorBegin(hashtable_t& ht)
	{
		return ht.cbegin();
	}
	inline iterator_t IteratorEnd(hashtable_t& ht)
	{
		return ht.cend();
	}
	inline keey_t IteratorGetKey(hashtable_t&, iterator_t& it)
	{
		return it->first;
	}
	inline value_t IteratorGetValue(hashtable_t&, iterator_t& it)
	{
		return it->second;
	}
	inline void IteratorNext(hashtable_t&, iterator_t& it)
	{
		++it;
	}
#endif

void test();
