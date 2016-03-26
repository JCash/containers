/*
ABOUT:
	A small and fast hash table implementing open addressing using the robin hood scheme with backward shift deletion

	- The memory must be allocated by the user
	- It cannot grow
	- It asserts when putting an item into a full table
	- Supports keys with % and == operators
	- Supports values with = operator

VERSION:
	1.0 - Initial add

LICENSE:

	The MIT License (MIT)

	Copyright (c) 2016 Mathias Westerdahl

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.


DISCLAIMER:

	This software is supplied "AS IS" without any warranties and support

USAGE:
	struct SPod
	{
		int 	i;
		float 	f;
	};
	typedef jc::HashTable<uint32_t, SPod> hashtable_t;
	
	uint32_t numelements 	= 1000; // The maximum number of entries to store
	uint32_t load_factor 	= 85; // percent
	uint32_t tablesize 		= uint32_t(numelements / (load_factor/100.0f)); 
	uint32_t sizeneeded 	= hashtable_t::CalcSize(tablesize);
	
	hashtable_t::key_type emptykey = 0xBAADC0D3;
	 
	void* mem = malloc(sizeneeded);
	
	hashtable_t ht;
	ht.Create(numelements, emptykey, mem);
	
	SPod value = { 1, 2.0f };
	ht.Put(17, value);
	
	Spod* pval = ht.Get(17);
	assert( pval->i == 1 );
	assert( pval->f == 2.0f );
	
	hashtable_t it = ht.Begin();
	hashtable_t itend = ht.End();
	for(; it != itend; ++it)
	{
		printf("key: %u  value: %d, %f\n", *it.GetKey(), it.GetValue()->i, it.GetValue()->f);
	}
	
	ht.Erase(17);
	
	free(mem);
*/

#pragma once
#include <stdint.h>
#include <string.h>
#include <assert.h>

namespace jc
{

#pragma pack(push, 1)

template <typename KEY, typename VALUE>
class HashTable
{
	struct Entry;
public:
	typedef KEY key_type;
	typedef VALUE mapped_type;
	
	// Calculate the size of the memory needed
	static uint32_t CalcSize(uint32_t capacity)
	{
		capacity = NextPow2(capacity);
		return static_cast<uint32_t>( sizeof(Entry) * capacity + + sizeof(uint32_t)*(capacity/(sizeof(uint32_t)*8)) );
	}
	static uint32_t NextPow2(uint32_t capacity)
	{
		--capacity;
		capacity |= capacity >> 1;
		capacity |= capacity >> 2;
		capacity |= capacity >> 4;
		capacity |= capacity >> 8;
		capacity |= capacity >> 16;
		return ++capacity;
	}

	HashTable()
	{
	}
	
	HashTable(uint32_t capacity, KEY emptykey, void* mem)
	{
		Create(capacity, emptykey, mem);
	}
	
	void Create(uint32_t capacity, KEY emptykey, void* mem)
	{
		m_Entries 		= reinterpret_cast<Entry*>(mem);
		m_Capacity 		= NextPow2(capacity);
		m_CapacityMask 	= m_Capacity - 1;
		m_EmptyKey		= emptykey;
		Clear();
	}
	
	inline void Clear()
	{
		m_Size = 0;
		for( uint32_t i = 0; i < m_Capacity; ++i )
		{
			m_Entries[i].m_Key = m_EmptyKey;
		}
	}
	
	inline VALUE* Get(const KEY& key)
	{
		return const_cast<VALUE*>(GetInternal(key));
	}
	
	inline const VALUE* Get(const KEY& key) const
	{
		return GetInternal(key);
	}
	
	inline void Put(KEY key, VALUE value)
	{
		assert(m_Size < m_Capacity);
		assert(key != m_EmptyKey);
		
		uint32_t current_dist = 0;
		uint32_t indexinit = key & m_CapacityMask;
		for(uint32_t n = 0; n < m_Capacity; ++n)
		{
			uint32_t i = (indexinit + n) & m_CapacityMask;
			if( IsFree(i) )
			{
				m_Entries[i].m_Key = key;
				m_Entries[i].m_Value = value;
				++m_Size;
				return;
			}
			else if(m_Entries[i].m_Key == key)
			{
				m_Entries[i].m_Value = value;
				return;
			}
			else
			{
				uint32_t dist = Distance(i);
				if( current_dist > dist )
				{
					KEY tmpkey = key;
					VALUE tmpvalue = value;
					key = m_Entries[i].m_Key;
					value = m_Entries[i].m_Value;
					m_Entries[i].m_Key = tmpkey;
					m_Entries[i].m_Value = tmpvalue;
					current_dist = dist;
				}
			}
			++current_dist;
		}
	}
	
	inline void Erase(const KEY& key)
	{
		assert(key != m_EmptyKey);
		uint32_t indexinit = key & m_CapacityMask;
		uint32_t index = 0;
		for(uint32_t n = 0; n < m_Capacity; ++n)
		{
			index = (indexinit + n) & m_CapacityMask;
			if( IsFree(index) || n > Distance(index) )
			{
				return;
			}
			else if( m_Entries[index].m_Key == key )
			{
				break;
			}
		}

		uint32_t previndex = index;
		uint32_t swapindex;
		for(uint32_t n = 1; n < m_Capacity; ++n)
		{
			previndex = (index + n - 1) & m_CapacityMask;
			swapindex = (index + n) & m_CapacityMask;
			
			if( IsFree(swapindex) || Distance(swapindex) == 0 )
			{
				m_Entries[previndex].m_Key = m_EmptyKey;
				break;
			}
			m_Entries[previndex] = m_Entries[swapindex];
		}
		--m_Size;
	}
	
	inline bool Empty() const
	{
		return m_Size == 0;
	}
	
	inline uint32_t Size() const
	{
		return m_Size;
	}
	
	class Iterator
	{
		const HashTable<KEY, VALUE>* m_HashTable;
		uint32_t m_EntryIndex;
	public:
		Iterator(const HashTable<KEY, VALUE>* ht, bool begin) : m_HashTable(ht)
		{
			if( begin )
			{
				for( uint32_t i = 0; i < m_HashTable->m_Capacity; ++i)
				{
					if( m_HashTable->m_Entries[i].m_Key != m_HashTable->m_EmptyKey )
					{
						m_EntryIndex = i;
						return;
					}
				}
			}
			else
			{
				m_EntryIndex = 0xffffffff;
			}
		}
		
		const KEY*      GetKey() const		{ return &m_HashTable->m_Entries[m_EntryIndex].m_Key; }
		const VALUE*    GetValue() const	{ return &m_HashTable->m_Entries[m_EntryIndex].m_Value; }
		
		inline Iterator& operator++ ()
		{
			++m_EntryIndex;
			for( ; m_EntryIndex < m_HashTable->m_Capacity; ++m_EntryIndex)
			{
				if( m_HashTable->m_Entries[m_EntryIndex].m_Key != m_HashTable->m_EmptyKey )
				{
					return *this;
				}
			}
			m_EntryIndex = 0xFFFFFFFF;
			return *this;
		}

		inline bool operator==( const Iterator& rhs ) const { return m_EntryIndex == rhs.m_EntryIndex && m_HashTable == rhs.m_HashTable; }
		inline bool operator!=( const Iterator& rhs ) const { return !(*this == rhs); }
	};

	inline Iterator Begin() const	{ return Iterator(this, true); }
	inline Iterator End() const 	{ return Iterator(this, false); }

private:
	struct Entry
	{
		KEY     m_Key;		// Key is also the hash
		VALUE   m_Value;
	};

	uint32_t    m_Capacity;
	uint32_t    m_CapacityMask;
	uint32_t    m_Size;
	KEY         m_EmptyKey;	// A key that is guaranteed by the user to not be inserted
	Entry*      m_Entries;
	
	inline const VALUE* GetInternal(const KEY& key) const
	{
		uint32_t dist = 0;
		uint32_t indexinit = key & m_CapacityMask;
		uint32_t i;
		for(uint32_t n = 0; n < m_Capacity; ++n)
		{
			i = (indexinit + n) & m_CapacityMask;
			if( IsFree(i) || dist > Distance(i) )
			{
				return 0;
			}
			else if( m_Entries[i].m_Key == key )
			{
				return &m_Entries[i].m_Value;
			}
			++dist;
		}
		return 0;
	}
	
	inline bool IsFree(uint32_t entryindex) const
	{
		return m_Entries[entryindex].m_Key == m_EmptyKey;
	}
	
	inline uint32_t Distance(uint32_t index_stored) const
	{
		uint32_t index_init = m_Entries[index_stored].m_Key & m_CapacityMask;
		return index_stored - index_init + (index_init <= index_stored ? 0u : m_Capacity);
	}	
};

} // namespace
