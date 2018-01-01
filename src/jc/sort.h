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
    template<typename T>
    class SortKeyIdentity {
    public:
        const T& get_key(const T* value) const { return *value; }
    };

    template<typename KeyType, typename T, typename GetKey>
    void radix_sort(T* begin, T* end);

    template<typename KeyType, typename T, typename GetKey>
    void radix_sort_stable(T* begin, T* end, T* out);
}

#ifdef JC_SORT_IMPLEMENTATION

namespace jc
{


/*
template<typename KeyType, typename T, typename GetKey, int N>
void radix_sort_stable_internal(T* begin, T* end, T* out, GetKey* getter){
    size_t size = end - begin;
    #define KEY_TO_INDEX(_X) ((getter->get_key(_X) >> shift) & 0xFF)
    // if (size <= 64)
    // {
    //     std::sort(begin, end, [&](auto && l, auto && r){ return KEY_TO_INDEX(l) < KEY_TO_INDEX(r); });
    // }
    // else
    {
        // printf("Size: %u\n", size);
        // printf("Count: %u\n", count);
        for( uint32_t c = 0; c < N; ++c)
        {
//printf("C: %u\n", c);
            uint32_t shift = c*8;
            uint32_t buckets[256] = { 0 }; // memset
            for( uint32_t i = 0; i < size; ++i ) // count each bytes occurrances
                buckets[KEY_TO_INDEX(begin + i)]++;

// printf("\tCounts:\n");
// for( uint32_t i = 0; i < 256; ++i ) // count each bytes occurrances
// {
//     if(buckets[i])
//         printf("\t%3u:\t%u\n", i, buckets[i]);
// }

            for( uint32_t i = 1; i < 256; ++i ) // convert from count to offsets into final list
                buckets[i] += buckets[i-1];

// printf("\tOffsets:\n");
// for( uint32_t i = 0; i < 256; ++i ) // count each bytes occurrances
// {
//     if( i == 0 || i == 255 || buckets[i-1] != buckets[i])
//         printf("\t%3u:\t%u\n", i, buckets[i]);
// }

            // copy elements from source buffer to final buffer (from back to front to keep stable order)
            for( int i = (int)size-1; i >= 0; --i )
            {
                out[--buckets[KEY_TO_INDEX(begin + i)]] = begin[i]; // Also increment the bucket, so the next item ends up in the correct place
            }

// printf("\tOut:\n");
// for( uint32_t i = 0; i < size; ++i ) // count each bytes occurrances
// {
//     printf("\t%3u:\t%u\t%08X\n", i, out[i], out[i]);
// }
// printf("\n");


            T* tmp = begin;
            begin = out;
            out = tmp;
        }
    }
    #undef KEY_TO_INDEX

    if (N & 1)
        memcpy(out, begin, size*sizeof(T));
}
*/


// template<int N, typename T, typename GetKey>
// void radix_sort_stable_internal(T* begin, T* end, T* out, GetKey* getter){
//     size_t size = end - begin;
//     #define KEY_TO_INDEX(_X) ((getter->get_key(_X) >> shift) & 0xFF)

//     size_t count = sizeof(T);
//     for( uint32_t c = 0; c < count; ++c)
//     {
//         uint32_t shift = c*8;
//         uint32_t buckets[256] = { 0 }; // memset
//         for( uint32_t i = 0; i < size; ++i ) // count each bytes occurrances
//             buckets[KEY_TO_INDEX(begin + i)]++;

//         for( uint32_t i = 1; i < 256; ++i ) // convert from count to offsets into final list
//             buckets[i] += buckets[i-1];

//         // copy elements from source buffer to final buffer (from back to front to keep stable order)
//         for( int i = (int)size-1; i >= 0; --i )
//         {
//             out[--buckets[KEY_TO_INDEX(begin + i)]] = begin[i]; // Also increment the bucket, so the next item ends up in the correct place
//         }

//         T* tmp = begin;
//         begin = out;
//         out = tmp;
//     }
//     #undef KEY_TO_INDEX

//     if (count & 1)
//         memcpy(out, begin, size*sizeof(T));
// }


// // Good version 1
// template<int N, typename T>
// void radix_sort_stable_internal(T* begin, T* end, T* out){
//     #define KEY_TO_INDEX(_X) ((*(_X) >> shift) & 0xFF)
//     #define PF(_A) __builtin_prefetch(_A, 0, 1)
//     #define PFW(_A) __builtin_prefetch(_A, 1, 1)

//     PF(begin);

//     size_t size = end - begin;
//     uint32_t buckets[N][256] = {{0}};
//     for( uint32_t i = 0; i < size; ++i )
//     {
//         uint64_t key = begin[i];
//         for (uint32_t c = 0; c < N; ++c)
//         {
//             uint32_t index = (key >> (i*8)) & 0xFF;
//             PFW(&buckets[c][index] + 3);
//             buckets[c][index]++;
//         }
//         PF(begin + i + 3);
//     }

//     for( uint32_t i = 1; i < 256; ++i )
//     {
//         for (uint32_t c = 0; c < N; ++c)
//         {
//             buckets[c][i] += buckets[c][i-1];
//             PFW(&buckets[c][i] + 3);
//         }
//     }

//     for( uint32_t c = 0; c < N; ++c)
//     {
//         uint32_t shift = c*8;

//         // copy elements from source buffer to final buffer (from back to front to keep stable order)
//         for( int i = (int)size-1; i >= 0; --i )
//         {
//             PF(begin + i + 3);
//             uint32_t index = KEY_TO_INDEX(begin + i);
//             PFW(&buckets[c][index]);
//             out[--buckets[c][index]] = begin[i]; // Also deccrement the bucket, so the next item ends up in the correct place
//         }

//         T* tmp = begin;
//         begin = out;
//         out = tmp;
//     }
//     #undef KEY_TO_INDEX

//     if (N & 1)
//         memcpy(out, begin, size*sizeof(T));
// }

// Ok, not good
// stable_sort 32  iterations: 20  avg: 0.556560 ms    median: 0.554354 ms min: 0.552125 ms    max: 0.576250 ms
// stable_sort 64  iterations: 20  avg: 2.336902 ms    median: 2.329709 ms min: 2.311167 ms    max: 2.490291 ms
template<int N, typename T>
void radix_sort_stable_internal_ok(T* begin, T* end, T* out){
    #define KEY_TO_INDEX(_X) ((*(_X) >> shift) & 0xFF)
    size_t size = end - begin;

    for( uint32_t c = 0; c < N; ++c)
    {
        uint32_t shift = c*8;

        uint32_t offsets[256] = { 0 }; // memset
        for( uint32_t i = 0; i < size; ++i ) // count each bytes occurrances
            offsets[KEY_TO_INDEX(begin + i)]++;

        for( uint32_t i = 1; i < 256; ++i ) // count each bytes occurrances
            offsets[i] += offsets[i-1];

        // copy elements from source buffer to final buffer (from back to front to keep stable order)
        for( int i = (int)size-1; i >= 0; --i )
        {
            uint32_t index = KEY_TO_INDEX(begin + i);
            out[--offsets[index]] = begin[i]; // Also decrement the bucket, so the next item ends up in the correct place
        }

        T* tmp = begin;
        begin = out;
        out = tmp;
    }
    #undef KEY_TO_INDEX

    if (N & 1)
        memcpy(out, begin, size*sizeof(T));
}

// Ok, not good (better 64 bit support)
// stable_sort 32  iterations: 20  avg: 0.544917 ms    median: 0.541791 ms min: 0.540250 ms    max: 0.580542 ms
// stable_sort 64  iterations: 20  avg: 1.464696 ms    median: 1.380938 ms min: 1.354209 ms    max: 2.219292 ms
template<int N, typename T>
void radix_sort_stable_internal_ok1(T* begin, T* end, T* out){
    #define KEY_TO_INDEX(_X) ((*(_X) >> shift) & 0xFF)
    size_t size = end - begin;
    uint32_t offsets[N][256] = {{0}};
    for( size_t i = 0; i < size; ++i )
    {
        uint64_t key = begin[i];
        for (uint32_t c = 0; c < N; ++c)
        {
            uint32_t index = (key >> (c*8)) & 0xFF;
            offsets[c][index]++;
        }
    }

    for (uint32_t c = 0; c < N; ++c)
    {
        for( size_t i = 1; i < 256; ++i )
            offsets[c][i] += offsets[c][i-1];
    }

    for( uint32_t c = 0; c < N; ++c)
    {
        uint32_t shift = c*8;

        // copy elements from source buffer to final buffer (from back to front to keep stable order)
        for( int i = (int)size-1; i >= 0; --i )
        {
            uint32_t index = KEY_TO_INDEX(begin + i);
            out[--offsets[c][index]] = begin[i]; // Also decrement the bucket, so the next item ends up in the correct place
        }

        T* tmp = begin;
        begin = out;
        out = tmp;
    }
    #undef KEY_TO_INDEX

    if (N & 1)
        memcpy(out, begin, size*sizeof(T));
}

// Use actual offsets
// stable_sort 32  iterations: 20  avg: 0.529219 ms    median: 0.524772 ms min: 0.512750 ms    max: 0.580208 ms
// stable_sort 64  iterations: 20  avg: 1.412467 ms    median: 1.379125 ms min: 1.368500 ms    max: 1.687208 ms
template<int N, typename T>
void radix_sort_stable_internal_ok2(T* begin, T* end, T* out){
    #define KEY_TO_INDEX(_X) ((*(_X) >> shift) & 0xFF)

    size_t size = end - begin;

    uint32_t counts[N][256] = {{0}};
    for( size_t i = 0; i < size; ++i )
    {
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
            offsets[c][i] = offsets[c][i-1] + counts[c][i-1];
    }

    for( uint32_t c = 0; c < N; ++c)
    {
        uint32_t shift = c*8;

        // copy elements from source buffer to final buffer (from back to front to keep stable order)
        for( uint32_t i = 0; i < size; ++i )
        {
            uint32_t index = KEY_TO_INDEX(begin + i);
            out[offsets[c][index]++] = begin[i]; // Also decrement the bucket, so the next item ends up in the correct place
        }

        T* tmp = begin;
        begin = out;
        out = tmp;
    }
    #undef KEY_TO_INDEX

    if (N & 1)
        memcpy(out, begin, size*sizeof(T));
}

// Prefetch tests
// stable_sort 32  iterations: 20  avg: 0.527279 ms    median: 0.523292 ms min: 0.494000 ms    max: 0.680958 ms
// stable_sort 32  iterations: 20  avg: 0.531602 ms    median: 0.525584 ms min: 0.510458 ms    max: 0.665917 ms
// stable_sort 32  iterations: 20  avg: 0.525952 ms    median: 0.527813 ms min: 0.512125 ms    max: 0.534125 ms
// stable_sort 32  iterations: 20  avg: 0.508402 ms    median: 0.500292 ms min: 0.487000 ms    max: 0.641709 ms
// stable_sort 32  iterations: 20  avg: 0.505027 ms    median: 0.500938 ms min: 0.487833 ms    max: 0.518917 ms
// stable_sort 32  iterations: 20  avg: 0.504771 ms    median: 0.504958 ms min: 0.489500 ms    max: 0.511000 ms

// stable_sort 64  iterations: 20  avg: 1.207700 ms    median: 1.195417 ms min: 1.186416 ms    max: 1.311666 ms
// stable_sort 64  iterations: 20  avg: 1.173946 ms    median: 1.143042 ms min: 1.132500 ms    max: 1.445292 ms
// stable_sort 64  iterations: 20  avg: 1.162848 ms    median: 1.162333 ms min: 1.149375 ms    max: 1.194625 ms
// stable_sort 64  iterations: 20  avg: 1.145525 ms    median: 1.131021 ms min: 1.120541 ms    max: 1.403250 ms
// stable_sort 64  iterations: 20  avg: 1.130585 ms    median: 1.126021 ms min: 1.120334 ms    max: 1.156792 ms
// stable_sort 64  iterations: 20  avg: 1.108983 ms    median: 1.107188 ms min: 1.093792 ms    max: 1.127000 ms

// STL
// sort 32 iterations: 20  avg: 1.534485 ms    median: 1.532167 ms min: 1.500250 ms    max: 1.583542 ms
// sort 64 iterations: 20  avg: 1.826802 ms    median: 1.824375 ms min: 1.784833 ms    max: 1.927375 ms
// stable_sort 32  iterations: 20  avg: 2.566500 ms    median: 2.509417 ms min: 2.472667 ms    max: 3.199208 ms
// stable_sort 64  iterations: 20  avg: 3.550561 ms    median: 3.535459 ms min: 3.466000 ms    max: 3.750041 ms

// SKA (has no stable sort)
// sort 32 iterations: 20  avg: 0.555629 ms    median: 0.549708 ms min: 0.544292 ms    max: 0.589625 ms
// sort 64 iterations: 20  avg: 1.331408 ms    median: 1.272625 ms min: 1.242625 ms    max: 1.493458 ms

template<int N, typename T>
void radix_sort_stable_internal(T* begin, T* end, T* out){
    #define KEY_TO_INDEX(_X) ((*(_X) >> shift) & 0xFF)
    #define PREFETCH(_A) __builtin_prefetch(_A, 0, 2)

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

    if (N & 1)
        memcpy(out, begin, size*sizeof(T));
}



/*

template<>
void radix_sort_stable_internal_<8, uint64_t>(uint64_t* begin, uint64_t* end, uint64_t* out, SortKeyIdentity<uint64_t>* ){

    size_t size = end - begin;
    #define KEY_TO_INDEX(_X) ((getter->get_key(_X) >> shift) & 0xFF)

// todo: prefetch

    uint32_t buckets[8][256] = {{0}};


#define PF(_A) //__builtin_prefetch(_A, 0, 1)
#define PFW(_A) //__builtin_prefetch(_A, 1, 1)

    for( uint32_t i = 0; i < size; ++i )
    {
        //PF(begin + i + 1);
        uint64_t key = begin[i];
        //__builtin_prefetch(buckets[1] + sizeof(buckets[1])*256);
        buckets[0][(key >>  0) & 0xFF]++;
        //__builtin_prefetch(buckets[2] + sizeof(buckets[2])*256);
        buckets[1][(key >>  8) & 0xFF]++;
        //__builtin_prefetch(buckets[3] + sizeof(buckets[3])*256);
        buckets[2][(key >> 16) & 0xFF]++;
        //__builtin_prefetch(buckets[4] + sizeof(buckets[4])*256);
        buckets[3][(key >> 24) & 0xFF]++;
        //__builtin_prefetch(buckets[5] + sizeof(buckets[5])*256);
        buckets[4][(key >> 32) & 0xFF]++;
        //__builtin_prefetch(buckets[6] + sizeof(buckets[6])*256);
        buckets[5][(key >> 40) & 0xFF]++;
        //__builtin_prefetch(buckets[7] + sizeof(buckets[7])*256);
        buckets[6][(key >> 48) & 0xFF]++;
        buckets[7][(key >> 54) & 0xFF]++;

        PF(begin + i + 1);
    }

    for( uint32_t i = 1; i < 256; ++i )
    {
        PFW(&buckets[0][i]);
        PF(&buckets[1][i-1]);
        buckets[0][i] += buckets[0][i-1];
        PFW(&buckets[1][i]);
        PF(&buckets[2][i-1]);
        buckets[1][i] += buckets[1][i-1];
        PFW(&buckets[2][i]);
        PF(&buckets[3][i-1]);
        buckets[2][i] += buckets[2][i-1];
        PFW(&buckets[3][i]);
        PF(&buckets[4][i-1]);
        buckets[3][i] += buckets[3][i-1];
        PFW(&buckets[4][i]);
        PF(&buckets[5][i-1]);
        buckets[4][i] += buckets[4][i-1];
        PFW(&buckets[5][i]);
        PF(&buckets[6][i-1]);
        buckets[5][i] += buckets[5][i-1];
        PFW(&buckets[6][i]);
        PF(&buckets[7][i-1]);
        buckets[6][i] += buckets[6][i-1];
        PFW(&buckets[7][i]);
        buckets[7][i] += buckets[7][i-1];
    }

    for( uint32_t c = 0; c < 8; ++c)
    {
        uint32_t shift = c*8;
        uint32_t* curbuckets = buckets[c];
        // copy elements from source buffer to final buffer (from back to front to keep stable order)
        for( int i = (int)size-1; i >= 0; --i )
        {
            //prefetch_range(begin - 4, 32);
            uint64_t key = (begin[i] >> shift) & 0xFF;
            uint32_t index = --curbuckets[key];
            PFW(out + index);
            PF(begin + i - 1);
            out[index] = begin[i]; // Also increment the bucket, so the next item ends up in the correct place
        }

        uint64_t* tmp = begin;
        begin = out;
        out = tmp;
    }
#undef KEY_TO_INDEX
#undef PF
}

*/


template<typename KeyType, typename T, typename GetKey>
void radix_sort_internal(int32_t index, T* begin, T* end, GetKey* getter){
    size_t size = end - begin;
    uint32_t shift = index*8;
    #define KEY_TO_INDEX(_X) ((int)((getter->get_key(_X) >> shift) & 0xFF))

//printf("Index: %d\n", index);
    uint32_t buckets[256] = { 0 }; // memset
    for( uint32_t i = 0; i < size; ++i ) // count each bytes occurrances
        ++buckets[KEY_TO_INDEX(begin + i)];

    T* pointers_[256+1];
    T** pointers = pointers_ + 1; // +1 is a trick to avoid an extra if statement below (negative index)
    pointers_[0] = pointers_[1] = begin;

// printf("begin/end: %p, %p\n", (void*)begin, (void*)end);

// printf("\tCounts:\n");
// for( uint32_t i = 0; i < 256; ++i ) // count each bytes occurrances
// {
//     if(buckets[i])
//         printf("\t%3u:\t%u\n", i, buckets[i]);
// }

    for( uint32_t i = 1; i < 256; ++i ) // convert from count to pointers into final list
        pointers[i] = pointers[i - 1] + buckets[i-1];

printf("\tOffsets:\n");
for( uint32_t i = 0; i < 256; ++i ) // count each bytes occurrances
{
    if( i == 0 || i == 255 || buckets[i-1] != buckets[i])
        printf("\t%3u:\t%u\tp: %p\n", i, buckets[i], (void*)pointers[i]);
}

    // In place copy
    for( int32_t i = 0; i < 256; ++i )
    {
        T* rangeend = pointers[i-1] + buckets[i];
        if (rangeend == end)
        {
            pointers[i] = end;
            break;
        }
        while( pointers[i] != rangeend )
        {
            T value = *pointers[i];
            int32_t idx = KEY_TO_INDEX(&value);

        //printf("%d: pointers[%d] == %p.  idx: %d\n", i, i, (void*)pointers[i], idx);
            if(i != idx)
            {
                do {
                    T tmp = *pointers[idx];
                    *pointers[idx]++ = value;
                    value = tmp;
                } while( (idx = KEY_TO_INDEX(&value)) != i );
                *pointers[i] = value;
                //printf("%d: pointers[%d] == %p\n", i, i, (void*)pointers[i]);
            }
            ++pointers[i];
            //printf("%d: pointers[%d] == %p\n", i, i, (void*)pointers[i]);
        }
    }

//printf("index: %d\n", index);
    if (index)
    {
        for(uint32_t i = 0; i < 256; ++i)
        {
            if(buckets[i] > 64 && index >= 0)
            {
                radix_sort_internal<KeyType, T>(index-1, pointers[i-1], pointers[i], getter);
            }
            else if(buckets[i] > 1)
            {
                //printf("Sort(%p, %p)\n", pointers[i-1], pointers[i]);
                std::sort(pointers[i-1], pointers[i], [&](auto && l, auto && r){ return getter->get_key(&l) < getter->get_key(&r); });
            }
        }

    }

    #undef KEY_TO_INDEX
}


// template<typename KeyType, typename T>
// void radix_sort_stable(T* begin, T* end, T* out){
//     SortKeyIdentity<KeyType, T> getter;
//     radix_sort_stable_internal<KeyType, T, SortKeyIdentity<KeyType, T> > (begin, end, out, &getter);
// }

template<typename T>
void radix_sort_stable(T* begin, T* end, T* out){
    //SortKeyIdentity<T> getter;
    //if (T(-1) > T(0))
        radix_sort_stable_internal<sizeof(T), T>(begin, end, out);
}

template<typename KeyType>
void radix_sort(KeyType* begin, KeyType* end){
    SortKeyIdentity<KeyType> getter;
    radix_sort_internal<KeyType, KeyType, SortKeyIdentity<KeyType> > (sizeof(KeyType), begin, end, &getter);
}


} // namespace

#endif
