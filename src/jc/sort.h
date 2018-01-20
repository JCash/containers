#pragma once

// Notes on radix sort
// Pierre Terdiman, http://codercorner.com/RadixSortRevisited.htm
// Michael Herf, http://stereopsis.com/radix.html
// https://github.com/gorset/radix/blob/master/radix.cc
// http://www.drdobbs.com/parallel/parallel-in-place-radix-sort-simplified/229000734?pgno=2
// https://github.com/coderodde/radixsort.cpp/blob/master/radixsort.cpp/radixsort.h
// https://github.com/maybeshewill/openmp_msd_radix/blob/master/radix.cpp

namespace jc
{
    template<typename KeyType, typename T, typename GetKey>
    void radix_sort_stable(T* begin, T* end, T* out);
}

#ifdef JC_SORT_IMPLEMENTATION

namespace jc
{

template<int N, typename T>
void radix_sort_stable_internal(T* begin, T* end, T* out){
    #define KEY_TO_INDEX(_X) ((*(_X) >> shift) & 0xFF)
#if defined(__GNUC__)
    #define PREFETCH(_A) __builtin_prefetch(_A, 0, 2)
#else
    #define PREFETCH
#endif

    size_t size = end - begin;

    uint32_t counts[N][256] = {{0}};
    for( size_t i = 0; i < size; ++i )
    {
        PREFETCH(begin + i + 2);
        uint64_t key = begin[i];
        for (uint32_t c = 0; c < N; ++c)
        {
            uint32_t index = (key >> (c*8)) & 0xFF;
            counts[c][index]++;
        }
    }

    uint32_t offsets[N][256];
    for (uint32_t c = 0; c < N; ++c)
    {
        offsets[c][0] = 0;
        for( size_t i = 1; i < 256; ++i )
        {
            PREFETCH(&counts[c][0] + i + 3);
            offsets[c][i] = offsets[c][i-1] + counts[c][i-1];
        }
    }

    for( uint32_t c = 0; c < N; ++c)
    {
        uint32_t shift = c*8;
        uint32_t* curoffsets = &offsets[c][0];
        // copy elements from source buffer to final buffer (from back to front to keep stable order)
        for( uint32_t i = 0; i < size; ++i )
        {
            PREFETCH(begin + i + 2); // v good
            uint32_t index = KEY_TO_INDEX(begin + i);
            out[curoffsets[index]++] = begin[i]; // Also decrement the bucket, so the next item ends up in the correct place
        }

        T* tmp = begin;
        begin = out;
        out = tmp;
    }
#undef KEY_TO_INDEX
#undef PREFETCH

    if (N & 1)
        memcpy(out, begin, size*sizeof(T));
}

template<typename T>
void radix_sort_stable(T* begin, T* end, T* out){
    radix_sort_stable_internal<sizeof(T), T>(begin, end, out);
}


} // namespace

#endif
