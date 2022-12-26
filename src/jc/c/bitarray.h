/*
ABOUT:      A bit array structure in C / C++
VERSION:
    1.00 - (2021-11-13) Initial commit

LICENSE:    MIT, Copyright (c) 2021 Mathias Westerdahl (See full licensea the bottom)
DISCLAIMER: This software is supplied "AS IS" without any warranties and support
SOURCE:     https://github.com/jcash/containers
*/

/* Examples:
// C

    jcba_bitarray* ba = jcba_create(17);
    jcba_clear(ba, 0); // Set all zeroes
    uint32_t v = jcba_getbit(ba, 15); // value is 0 or 1
    jcba_setbit(ba, 15, 1);
    jcba_destroy(ba);

// C++

    jc::BitArray* ba = new jc::BitArray(17);
    ba->Clear(0); // Set all zeroes
    uint32_t v = ba->GetBit(15);  // value is 0 or 1
    ba->SetBit(15, 1); // value is 0 or not
    delete ba;

*/

#ifndef JC_BITARRAY_H
#define JC_BITARRAY_H

#include <stdlib.h>
#include <string.h> // memset
#include <assert.h> // disable with NDEBUG

// Each bit represents a tile. 1 means it's filled
typedef struct _jcba_bitarray
{
    uint32_t bitcount;
    uint32_t capacity;   // Capacity in bytes
    uint8_t* bits;
} jcba_bitarray;

// C Api
// The bitarray asserts on out of bounds

jcba_bitarray*  jcba_create(uint32_t num_bits); // Creates an array using JCBA_REALLOC() (single allocation), containing num bits
void            jcba_destroy(jcba_bitarray* ba);  // Calls JCBA_FREE(ba)

void            jcba_clear(jcba_bitarray* ba, uint32_t bit);    // Sets all bits

uint32_t        jcba_getbit(const jcba_bitarray* ba, uint32_t index);         // Gets the bit at the n'th position.
void            jcba_setbit(jcba_bitarray* ba, uint32_t index, uint32_t bit); // Sets the bit at the n'th position. 0 if bit==0, 1 otherwise.

void            jcba_erase(jcba_bitarray* ba, uint32_t index, uint32_t count); // Deletes n bits from the array

uint32_t        jcba_is_all_ones(const jcba_bitarray* ba);    // return 1 if all bits are 1
uint32_t        jcba_is_all_zeroes(const jcba_bitarray* ba);  // return 1 if all bits are 0

// C++ api
#if defined(__cplusplus)
namespace jc {
    class BitArray
    {
    public:
        jcba_bitarray* ba;

        BitArray(uint32_t bit_count);
        ~BitArray();
        uint32_t Capacity();
        uint32_t Bitcount();
        uint32_t GetBit(uint32_t bit_index);
        void     SetBit(uint32_t bit_index, uint32_t bit);
        void     Clear(uint32_t bit);    // Sets all bits
        void     Erase(uint32_t index, uint32_t count); // Deletes n bits from the array
        bool     IsAllOnes();
        bool     IsAllZeroes();
    };
} // namespaces
#endif

#endif // JC_BITARRAY_H

/* ******************************************************************************************************** */

#ifdef JC_BITARRAY_IMPLEMENTATION
#undef JC_BITARRAY_IMPLEMENTATION

#ifndef JCBA_REALLOC
    #define JCBA_REALLOC realloc
#endif

#ifndef JCBA_FREE
    #define JCBA_FREE free
#endif

#ifndef JCBA_ASSERT
    #define JCBA_ASSERT assert
#endif

static inline uint32_t jcba_roundup(uint32_t x, uint32_t multiple)
{
    return ((x + multiple - 1) / multiple) * multiple;
}

static inline uint32_t jcba_bitcountinbytes(const jcba_bitarray* ba)
{
    return jcba_roundup(ba->bitcount, 8) / 8;
}


jcba_bitarray* jcba_create(uint32_t num_bits)
{
    uint32_t capacity = jcba_roundup(num_bits, 8) / 8;
    jcba_bitarray* ba = (jcba_bitarray*)JCBA_REALLOC(0, sizeof(jcba_bitarray)+capacity);
    ba->bits = ((uint8_t*)ba) + sizeof(jcba_bitarray);
    ba->capacity = capacity;
    ba->bitcount = num_bits;
    return ba;
}

void jcba_destroy(jcba_bitarray* ba)
{
    JCBA_FREE(ba);
}

void jcba_clear(jcba_bitarray* ba, uint32_t bit)
{
    JCBA_ASSERT(ba);
    if (bit)
        memset(ba->bits, 0xFF, ba->capacity);
    else 
        memset(ba->bits, 0x00, ba->capacity);
}

uint32_t jcba_getbit(const jcba_bitarray* ba, uint32_t bit_index)
{
    JCBA_ASSERT(ba);
    JCBA_ASSERT(bit_index < ba->bitcount);
    uint32_t byte = bit_index / 8;
    uint32_t bit = bit_index - byte*8;
    int value = ba->bits[byte] & (1 << bit);
    return value != 0 ? 1 : 0;
}

void jcba_setbit(jcba_bitarray* ba, uint32_t bit_index, uint32_t value)
{
    JCBA_ASSERT(ba);
    JCBA_ASSERT(bit_index < ba->bitcount);
    uint32_t byte = bit_index / 8;
    uint32_t bit = bit_index - byte*8;
    if (value)
        ba->bits[byte] |= 1 << bit;
    else
        ba->bits[byte] &= ~(1 << bit);
}

uint32_t jcba_is_all_ones(const jcba_bitarray* ba)
{
    if (!ba->bitcount)
        return 0U;
    uint32_t num_bytes = jcba_bitcountinbytes(ba);
    uint32_t remaining_bits = ba->bitcount - ((ba->bitcount / 8)*8);
    if (remaining_bits)
        num_bytes--;
    for (uint32_t i = 0; i < num_bytes; ++i)
    {
        if (ba->bits[i] != 0xFF)
            return 0U;
    }
    if (remaining_bits)
    {
        uint32_t bit_mask = (1<<(remaining_bits+1)) - 1;
        return (ba->bits[num_bytes] & bit_mask) == bit_mask;
    }

    return 1U;
}

uint32_t jcba_is_all_zeroes(const jcba_bitarray* ba)
{
    if (!ba->bitcount)
        return 0U;
    uint32_t num_bytes = jcba_bitcountinbytes(ba);
    uint32_t remaining_bits = ba->bitcount - ((ba->bitcount / 8)*8);
    if (remaining_bits)
        num_bytes--;
    for (uint32_t i = 0; i < num_bytes; ++i)
    {
        if (ba->bits[i] != 0x00)
            return 0U;
    }
    if (remaining_bits)
    {
        uint32_t bit_mask = (1<<(remaining_bits+1)) - 1;
        return (ba->bits[num_bytes] & bit_mask) == 0;
    }

    return 1U;
}

void jcba_erase(jcba_bitarray* ba, uint32_t index, uint32_t count)
{
    JCBA_ASSERT(ba);
    JCBA_ASSERT(index < ba->bitcount);

    if (count == 0)
        return;

    // A naive version to shift elements
    uint32_t num_to_copy = ba->bitcount - (index + count);
    for (uint32_t i = 0, dst = index, src=index+count; i < num_to_copy; ++i, ++dst, ++src)
    {
        uint32_t v = jcba_getbit(ba, src);
        jcba_setbit(ba, dst, v);
    }
    ba->bitcount -= count;
}

// C++ api
#if defined(__cplusplus)
namespace jc {
            BitArray::BitArray(uint32_t bit_count)          { ba = jcba_create(bit_count); }
            BitArray::~BitArray()                           { jcba_destroy(ba); }
uint32_t    BitArray::Capacity()                            { return ba->capacity; }
uint32_t    BitArray::Bitcount()                            { return ba->bitcount; }
uint32_t    BitArray::GetBit(uint32_t index)                { return jcba_getbit(ba, index); }
void        BitArray::SetBit(uint32_t index, uint32_t bit)  { jcba_setbit(ba, index, bit); }
void        BitArray::Clear(uint32_t bit)                   { jcba_clear(ba, bit); }
void        BitArray::Erase(uint32_t index, uint32_t count) { jcba_erase(ba, index, count); }
bool        BitArray::IsAllOnes()                           { return jcba_is_all_ones(ba); }
bool        BitArray::IsAllZeroes()                         { return jcba_is_all_zeroes(ba); }
} // namespaces
#endif



#endif // JC_BITARRAY_IMPLEMENTATION

/*
LICENSE:
    The MIT License (MIT)

    Copyright (c) 2021 Mathias Westerdahl

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
*/
