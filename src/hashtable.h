#pragma once

/** A small hash table
 * 
 * - The memory must be allocated by the user
 * - It cannot grow
 * - It asserts when putting an item into a full table
 * - Supports keys with % and == operators
 * - Supports values with = operator 
 */

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
	// Calculate the size of the memory needed
	static uint32_t CalcSize(uint32_t table_size, uint32_t capacity)
	{
		return static_cast<uint32_t>( sizeof(uint32_t) * table_size + sizeof(Entry) * capacity ) + sizeof(uint32_t)*(capacity/(sizeof(uint32_t)*8));
	}

	HashTable()
	{
		memset(this, 0, sizeof(*this));
	}
	HashTable(uint32_t table_size, uint32_t capacity, void* mem)
	{
		memset(this, 0, sizeof(*this));
		Create(table_size, capacity, mem);
	}
	
	void Create(uint32_t table_size, uint32_t capacity, void* mem)
	{
		m_Buckets = reinterpret_cast<uint32_t*>(mem);
		m_Entries = reinterpret_cast<Entry*>(m_Buckets + table_size);
		m_FreeBits= reinterpret_cast<uint32_t*>(m_Entries + capacity);
		m_TableSize = table_size;
		m_Capacity = capacity;
		Clear();
	}
	
	inline VALUE* Get(KEY key)
	{
		Entry* entry = FindEntry(key);
		return entry != 0 ? &entry->m_Value : 0;
	}
	
	inline const VALUE* Get(KEY key) const
	{
		Entry* entry = FindEntry(key);
		return entry != 0 ? &entry->m_Value : 0;
	}
	
	inline void PutFirst(KEY key, const VALUE& value)
	{
		Entry* entry = FindEntry(key);
		if( entry )
		{
			entry->m_Value = value;
			return;
		}
		
		++m_Size;
		entry = AllocateEntry();
		entry->m_Key 	= key;
		entry->m_Value 	= value;
		
		uint32_t entryindex = GetEntryIndex(entry);
		uint32_t bucket = key % m_TableSize;
		entry->m_Next = m_Buckets[bucket];
		m_Buckets[bucket] = entryindex;
		SetFree(entryindex, 0);
	}

	// Put last in bucket
	inline void Put(KEY key, const VALUE& value)
	{
		Entry* entry = FindEntry(key);
		if( entry )
		{
			entry->m_Value = value;
			return;
		}
		
		++m_Size;
		entry = AllocateEntry();
		entry->m_Key 	= key;
		entry->m_Value 	= value;
		entry->m_Next	= INVALID_INDEX;

		uint32_t entryindex = GetEntryIndex(entry);
		uint32_t bucket = key % m_TableSize;
		if( m_Buckets[bucket] == INVALID_INDEX )
		{
			m_Buckets[bucket] = entryindex;
		}
		else
		{
			uint32_t index = m_Buckets[bucket];
			while( m_Entries[index].m_Next != INVALID_INDEX )
				index = m_Entries[index].m_Next;
			m_Entries[index].m_Next = entryindex;
		}
		SetFree(entryindex, 0);
	}

	
	inline void Erase(KEY key)
	{
		uint32_t bucket = key % m_TableSize;
		uint32_t index = m_Buckets[bucket];
		Entry* prev_entry = 0;
		while( index != INVALID_INDEX )
		{
			Entry* entry = &m_Entries[ index ];
			if( entry->m_Key == key )
			{
				if( prev_entry == 0 ) // first in list
					m_Buckets[bucket] = entry->m_Next;
				else
					prev_entry->m_Next = entry->m_Next;
				entry->m_Next = m_FreeEntries;
				uint32_t entryindex = GetEntryIndex(entry);
				m_FreeEntries = entryindex;
				SetFree(entryindex, 1);
				--m_Size;
				return;
			}
			prev_entry = entry;
			index = entry->m_Next;
		}
	}
	
	inline bool Exists(KEY key) const
	{
		return FindEntry(key) != 0;
	}
	
	inline bool Empty() const
	{
		return m_Size == 0;
	}
	
	inline uint32_t Size() const
	{
		return m_Size;
	}
	
	void Clear()
	{
		m_Size = 0;
		m_FreeEntries = 0;
		m_InitializedEntry = 0;		
		memset(m_Buckets, 0xff, sizeof(uint32_t)*m_TableSize + sizeof(Entry)*m_Capacity + sizeof(uint32_t)*(m_Capacity/(sizeof(uint32_t)*8)) );
	}
	
	// Iterators
	class Iterator
	{
		const HashTable<KEY, VALUE>* m_HashTable;
		uint32_t m_EntryIndex;
	public:
		Iterator(const HashTable<KEY, VALUE>* ht, bool begin) : m_HashTable(ht), m_EntryIndex(INVALID_INDEX)
		{
			if( begin )
			{
				for( uint32_t i = 0; i < m_HashTable->m_Capacity; ++i)
				{
					if( !m_HashTable->IsFree(i) )
					{
						m_EntryIndex = i;
						return;
					}
				}
			}
		}
		
		const KEY* 		GetKey() const		{ return &m_HashTable->m_Entries[m_EntryIndex].m_Key; }
		const VALUE* 	GetValue() const	{ return &m_HashTable->m_Entries[m_EntryIndex].m_Value; }
		
		inline Iterator& operator++ ()
		{
			for( uint32_t i = m_EntryIndex+1; i < m_HashTable->m_Capacity; ++i)
			{
				if( !m_HashTable->IsFree(i) )
				{
					m_EntryIndex = i;
					return *this;
				}
			}
			m_EntryIndex = INVALID_INDEX;
			return *this;
		}
		
		/*
		inline Iterator operator++ (int)
		{
			Iterator current( m_HashTable, m_State );
			m_State = reinterpret_cast<const HashTable<KEY, VALUE>*>( m_HashTable )->Next(reinterpret_cast<Entry*>(m_State));
			return current;
		}*/

		inline bool operator==( const Iterator& rhs ) const { return m_EntryIndex == rhs.m_EntryIndex && m_HashTable == rhs.m_HashTable; }
		inline bool operator!=( const Iterator& rhs ) const { return !(*this == rhs); }
	};
	
	inline Iterator Begin() const	{ return Iterator(this, true); }
	inline Iterator End() const 	{ return Iterator(this, false); }

	
	void Dump() const
	{
		for( uint32_t i = 0; i < m_TableSize; ++i)
		{
			if( m_Buckets[i] != INVALID_INDEX )
			{
				printf("ht[%5u] : ", i);
				uint32_t entryid = m_Buckets[i];
				while( entryid != INVALID_INDEX )
				{
					printf("k:%llu ", m_Entries[entryid].m_Key);
					entryid = m_Entries[entryid].m_Next;
				}
				printf("\n");
			}
		}
		printf("Size: %u\n", m_Size);
	}
private:
	static const uint32_t INVALID_INDEX = 0xFFFFFFFF;

	struct Entry
	{
		KEY			m_Key;
		VALUE		m_Value;
		uint32_t	m_Next;
	};

	uint32_t 	m_TableSize;
	uint32_t 	m_Capacity;
	uint32_t 	m_Size;
	uint32_t	m_FreeEntries; 		// linked list
	uint32_t	m_InitializedEntry;	// Pointer to where the entrys haven't been first consumed
	Entry*	 	m_Entries;
	uint32_t*	m_Buckets;
	uint32_t*	m_FreeBits;			// flags telling if an entry is free or not
	
	inline uint32_t GetEntryIndex(const Entry* entry) const
	{
		return static_cast<uint32_t>(entry - m_Entries);
	}
	
	inline bool IsFree(uint32_t entryindex) const
	{
		uint32_t freeindex = entryindex / (sizeof(uint32_t)*8);
		uint32_t freebitindex = entryindex - (freeindex * sizeof(uint32_t)*8);
		return m_FreeBits[freeindex] & (1 << freebitindex);
	}
	
	inline void SetFree(uint32_t entryindex, uint32_t flag)
	{
		uint32_t freeindex = entryindex / (sizeof(uint32_t)*8);
		uint32_t freebitindex = entryindex - (freeindex * sizeof(uint32_t)*8);
		m_FreeBits[freeindex] = (m_FreeBits[freeindex] & ~(1 << freebitindex)) | (flag << freebitindex);
	}

	inline Entry* FindEntry(KEY key) const
	{
		uint32_t bucket = key % m_TableSize;
		uint32_t index = m_Buckets[bucket];
		while( index != INVALID_INDEX )
		{
			if( m_Entries[ index ].m_Key == key )
				return &m_Entries[ index ];
			index = m_Entries[ index ].m_Next;
		}
		return 0;
	}
	
	inline Entry* AllocateEntry()
	{
		if( m_InitializedEntry < m_Capacity )
			return &m_Entries[m_InitializedEntry++];
		
		assert( m_FreeEntries != INVALID_INDEX );
		Entry* entry = &m_Entries[m_FreeEntries];
		m_FreeEntries = entry->m_Next;
		return entry;
	}
};

#pragma pack(pop)

}
