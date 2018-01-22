#pragma once

#include "timeit.h"
#include "../helpers.h"

typedef uint32_t    value_t;


#if defined(IMPL_STL)
    #include <algorithm>
    #define TESTNAME "std::algorithm"
    #define UPPER_BOUND std::upper_bound
    #define LOWER_BOUND std::lower_bound
    #define SORT std::sort
    #define STABLE_SORT std::stable_sort

#elif defined(IMPL_EASTL)

#elif defined(IMPL_BOOST)

#elif defined(IMPL_WIKISORT)

    #include <algorithm>
    #include "WikiSort.h"
    #define TESTNAME "wikisort::stable_sort"
    #define UPPER_BOUND std::upper_bound
    #define LOWER_BOUND std::lower_bound

    #define SORT std::sort
    #define STABLE_SORT Wiki::Sort

#elif defined(IMPL_SKA)

    #include <algorithm>
    #include "ska_sort.hpp"
    #define TESTNAME "ska::sort"
    #define UPPER_BOUND std::upper_bound
    #define LOWER_BOUND std::lower_bound

    // template<typename It, typename OutIt, typename ExtractKey>
    // bool radix_sort(It begin, It end, OutIt buffer_begin, ExtractKey && extract_key)
    // {
    //     return detail::RadixSorter<typename std::result_of<ExtractKey(decltype(*begin))>::type>::sort(begin, end, buffer_begin);
    // }
    template<typename It, typename OutIt>
    bool radix_sort(It begin, It end, OutIt buffer_begin)
    {
        return detail::RadixSorter<decltype(*begin)>::sort(begin, end, buffer_begin, detail::IdentityFunctor());
    }

    // #define SORT(_A, _B, _C) radix_sort(_A, _B, _C, [](auto i){ return i; } )
    // #define STABLE_SORT(_A, _B, _C) radix_sort(_A, _B, _C, [](auto i){ return i; } )
    #define SORT        radix_sort
    #define STABLE_SORT std::stable_sort


#elif defined(IMPL_JC)
    #define JC_ALGORITHM_IMPLEMENTATION
    #include "../../src/jc/algorithm.h"
    #define JC_SORT_IMPLEMENTATION
    #include "../../src/jc/sort.h"

    #define TESTNAME "jc::algorithm"
    #define UPPER_BOUND jc::upper_bound<value_t>
    #define LOWER_BOUND jc::lower_bound<value_t>


#include <algorithm>
#include <iostream>
#include <iterator>

    #include "kxsort.h"

    // // Radix sort comparator for 32-bit two's complement integers
    // class radix_test
    // {
    //     const int bit; // bit position [0..31] to examine
    // public:
    //     radix_test(int offset) : bit(offset) {} // constructor

    //     bool operator()(int value) const // function call operator
    //     {
    //         if (bit == 31) // sign bit
    //             return value < 0; // negative int to left partition
    //         else
    //             return !(value & (1 << bit)); // 0 bit to left partition
    //     }
    // };

    // // Least significant digit radix sort
    // inline void lsd_radix_sort(int* first, int* last)
    // {
    //     for (int lsb = 0; lsb < 32; ++lsb) // least-significant-bit
    //     {
    //         std::stable_partition(first, last, radix_test(lsb));
    //     }
    // }

    #define SORT std::sort
    //#define SORT jc::radix_sort
    //#define STABLE_SORT(_A, _B) lsd_radix_sort((int*)_A, (int*)_B)
    #define STABLE_SORT jc::radix_sort_stable

#endif

