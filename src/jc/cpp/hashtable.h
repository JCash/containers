/*
ABOUT:
    A small and fast hash table implementing open addressing using the robin hood scheme with backward shift deletion
    Implementation uses two separate arrays in order to separate seeking and storing, for cache friendliness

    - The memory must be allocated by the user
    - It cannot grow
    - It asserts when putting an item into a full table
    - Supports keys with & and == operators
    - Supports values with = operator

VERSION:
    2.10 - (2024-12-28) - Added SetCapacity() and dynamic size support
    2.01 - (2016-11-06) - Removed requirement of allocating memory at power of 2 sizes
    2.00 - (2016-06-04) - Changed to two arrays: entries & values
                        - Removed empty key (API change)
    1.02 - (2016-06-04) - Changed to two arrays: entries & values
                        - Removed empty key
                        - Optimised the Create function
                        - Bug fixes
    1.01 - (2016-04-23) Fixed two iterator issues
    1.00 - (2016-03-08) Initial add

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
        int     i;
        float   f;
    };
    typedef jc::HashTable<uint32_t, SPod> hashtable_t;

    uint32_t numelements    = 1000; // The maximum number of entries to store
    uint32_t load_factor    = 85; // percent
    uint32_t tablesize      = uint32_t(numelements / (load_factor/100.0f));
    uint32_t sizeneeded     = hashtable_t::CalcSize(tablesize);

    void* mem = malloc(sizeneeded);

    hashtable_t ht;
    ht.Create(numelements, mem);

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

#if defined(__x86_64__) || defined(__arm64) || defined(__aarch64__) || defined(__ppc64__) || defined(_WIN64)
    #define JC_HT_64BIT
#endif

namespace jc
{

template <typename KEY, typename VALUE>
class HashTable
{
    struct Entry;
public:
    typedef KEY key_type;
    typedef VALUE mapped_type;

    static const uint32_t INVALID_INDEX = 0xFFFFFFFF;

    // Calculate the size of the memory needed
    static uint32_t CalcSize(uint32_t capacity)
    {
        return static_cast<uint32_t>( (sizeof(Entry) + sizeof(Value)) * capacity);
    }

    HashTable()
    {
        memset(this, 0, sizeof(*this));
    }

    HashTable(uint32_t capacity, void* mem)
    : m_UserAllocated(1)
    {
        Create(capacity, mem);
    }

    ~HashTable()
    {
        if (!m_UserAllocated)
        {
            free((void*)m_Entries);
        }
    }

    inline void Create(uint32_t capacity, void* mem)
    {
        assert(m_UserAllocated==1 || m_Entries==0);
        CreateFromMem(capacity, mem, 1);
    }

    inline void Clear()
    {
        m_Size = 0;
        m_FreeList = INVALID_INDEX;
        m_InitialFreeList = 0;
        memset(m_Entries, 0xFF, sizeof(Entry) * m_Capacity);
    }

    inline void SetCapacity(uint32_t capacity)
    {
        assert(capacity < 0xFFFFFFFF);
        assert(m_Size <= capacity);
        assert(!m_UserAllocated);

        if (m_Entries == 0)
        {
            uint32_t memsize = CalcSize(capacity);
            void* mem = malloc(memsize);
            CreateFromMem(capacity, mem, 0);
        }
        else
        {
            // Remap
            HashTable<KEY, VALUE> tmp;
            tmp.SetCapacity(capacity);

            for (HashTable<KEY, VALUE>::Iterator it = Begin(); it != End(); ++it)
            {
                tmp.Put(*it.GetKey(), *it.GetValue());
            }

            // swap the internals
            free((void*)m_Entries);

            m_Entries         = tmp.m_Entries;
            m_Values          = tmp.m_Values;
            m_InitialFreeList = tmp.m_InitialFreeList;
            m_FreeList        = tmp.m_FreeList;
            m_Capacity        = capacity;

            // avoid double delete
            tmp.m_Entries = 0;
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

    inline void Put(KEY key, const VALUE& value)
    {
        assert(m_Size < m_Capacity);

        // Get a free value slot to put the value in
        uint32_t valueindex;
        if(m_InitialFreeList < m_Capacity)
        {
            valueindex = m_InitialFreeList++;
        }
        else
        {
            valueindex = m_FreeList;
            m_FreeList = m_Values[valueindex].m_Next;
        }
        m_Values[valueindex].m_Value = value;

        uint32_t current_dist = 0;
        uint32_t indexinit = key % m_Capacity;
        for(uint32_t n = 0; n < m_Capacity; ++n, ++indexinit)
        {
            if( indexinit >= m_Capacity )
                indexinit = 0;
            uint32_t i = indexinit;
            if( IsFree(i) )
            {
                m_Entries[i].m_Key = key;
                m_Entries[i].m_Index = valueindex;
                ++m_Size;
                return;
            }
            else if(m_Entries[i].m_Key == key)
            {
                m_Values[m_Entries[i].m_Index].m_Value = value;
                // since we removed a new node prematurely, we put it back
                m_Values[valueindex].m_Next = m_FreeList;
                m_FreeList = valueindex;
                return;
            }
            else
            {
                uint32_t dist = Distance(i);
                if( current_dist > dist )
                {
                    KEY tmpkey = key;
                    uint32_t tmpindex = valueindex;
                    key = m_Entries[i].m_Key;
                    valueindex = m_Entries[i].m_Index;
                    m_Entries[i].m_Key = tmpkey;
                    m_Entries[i].m_Index = tmpindex;
                    current_dist = dist;
                }
            }
            ++current_dist;
        }
    }

    inline void Erase(const KEY& key)
    {
        uint32_t indexinit = key % m_Capacity;
        uint32_t index = 0;
        for(uint32_t n = 0; n < m_Capacity; ++n)
        {
            index = (indexinit + n) % m_Capacity;
            if( IsFree(index) || n > Distance(index) )
            {
                return;
            }
            else if( m_Entries[index].m_Key == key )
            {
                break;
            }
        }

        m_Values[m_Entries[index].m_Index].m_Next = m_FreeList;
        m_FreeList = m_Entries[index].m_Index;
        assert( m_FreeList != INVALID_INDEX );

        uint32_t previndex = index;
        uint32_t swapindex;
        for(uint32_t n = 1; n <= m_Capacity; ++n)
        {
            previndex = (index + n - 1) % m_Capacity;
            swapindex = (index + n) % m_Capacity;

            if( IsFree(swapindex) || Distance(swapindex) == 0 )
            {
                m_Entries[previndex].m_Index = INVALID_INDEX;
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
        #if defined(JC_HT_64BIT)
        uint32_t _pad;
        #endif

    public:
        Iterator(const HashTable<KEY, VALUE>* ht, bool begin) : m_HashTable(ht)
        {
            if( begin )
            {
                for( uint32_t i = 0; i < m_HashTable->m_Capacity; ++i)
                {
                    if( m_HashTable->m_Entries[i].m_Index != HashTable::INVALID_INDEX )
                    {
                        m_EntryIndex = i;
                        return;
                    }
                }
            }
            m_EntryIndex = INVALID_INDEX;
        }

        const KEY*      GetKey() const      { return &m_HashTable->m_Entries[m_EntryIndex].m_Key; }
        const VALUE*    GetValue() const    { return &m_HashTable->m_Values[m_HashTable->m_Entries[m_EntryIndex].m_Index].m_Value; }

        inline Iterator& operator++ ()
        {
            ++m_EntryIndex;
            for( ; m_EntryIndex < m_HashTable->m_Capacity; ++m_EntryIndex)
            {
                if( m_HashTable->m_Entries[m_EntryIndex].m_Index != INVALID_INDEX )
                {
                    return *this;
                }
            }
            m_EntryIndex = INVALID_INDEX;
            return *this;
        }

        inline bool operator==( const Iterator& rhs ) const { return m_EntryIndex == rhs.m_EntryIndex && m_HashTable == rhs.m_HashTable; }
        inline bool operator!=( const Iterator& rhs ) const { return !(*this == rhs); }
    };

    inline Iterator Begin() const   { return Iterator(this, true); }
    inline Iterator End() const     { return Iterator(this, false); }

private:
    struct Entry
    {
        KEY         m_Key;      // Key is also the hash
        uint32_t    m_Index;    // Index into the values array
        #if defined(JC_HT_64BIT)
        uint32_t    _pad;
        #endif
    };

    struct Value
    {
        VALUE       m_Value;
        uint32_t    m_Next;     // Index into the values array
        #if defined(JC_HT_64BIT)
        uint32_t    _pad;
        #endif
    };

    Entry*      m_Entries;
    Value*      m_Values;
    uint32_t    m_InitialFreeList; // while <capacity, points to the next free value node
    uint32_t    m_FreeList; // A list of free value nodes
    uint32_t    m_Capacity;
    uint32_t    m_Size:31;
    uint32_t    m_UserAllocated:1;

    inline void CreateFromMem(uint32_t capacity, void* mem, uint32_t user_allocated)
    {
        m_Capacity      = capacity;
        m_Entries       = reinterpret_cast<Entry*>(mem);
        m_Values        = reinterpret_cast<Value*>(m_Entries + m_Capacity);
        m_UserAllocated = user_allocated;
        Clear();
    }

    inline const VALUE* GetInternal(const KEY& key) const
    {
        uint32_t dist = 0;
        uint32_t indexinit = key % m_Capacity;
        uint32_t i;
        for(uint32_t n = 0; n < m_Capacity; ++n)
        {
            i = (indexinit + n) % m_Capacity;
            if( IsFree(i) || dist > Distance(i) )
            {
                return 0;
            }
            else if( m_Entries[i].m_Key == key )
            {
                return &m_Values[m_Entries[i].m_Index].m_Value;
            }
            ++dist;
        }
        return 0;
    }

    inline bool IsFree(uint32_t entryindex) const
    {
        return m_Entries[entryindex].m_Index == INVALID_INDEX;
    }

    inline uint32_t Distance(uint32_t index_stored) const
    {
        uint32_t index_init = m_Entries[index_stored].m_Key % m_Capacity;
        return index_stored - index_init + (index_init <= index_stored ? 0u : m_Capacity);
    }
};

} // namespace
