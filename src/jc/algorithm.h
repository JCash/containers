#pragma once
#include <stddef.h>

#include <algorithm>

namespace jc
{
    template<typename T> T* upper_bound(T* first, T* last, const T& value);
    template<typename T> T* lower_bound(T* first, T* last, const T& value);

    template<typename T, typename Value, typename Compare>
    T* upper_bound(T* first, T* last, const Value& value, Compare& comp);

    template<typename T, typename Value, typename Compare>
    T* lower_bound(T* first, T* last, const Value& value, Compare& comp);

    template<typename T> size_t lower_bound_offset(T* first, size_t size, const T& val);
    template<typename T> size_t upper_bound_offset(T* first, size_t size, const T& val);

    template<typename T, typename Value>
    void find_ranges(T* first, size_t size, Value (*getval)(T*), void (*callback)(void* ctx, Value value, size_t start, size_t count), void* ctx );
}

#if defined(JC_ALGORITHM_IMPLEMENTATION)

namespace jc
{

template<typename T>
size_t upper_bound_offset(T* first, size_t size, const T& val)
{
    size_t low = 0;
    while (size > 0) {
        size_t half = size >> 1;
        size_t middle = low + half;

        if (val < first[middle])
        {
            size = half;
        }
        else
        {
            low = middle + 1;
            size = size - half - 1;
        }
    }
    return low;
}

template<typename T>
T* upper_bound(T* first, T* last, const T& val)
{
    size_t size = (size_t)(last - first);
    while (size > 0) {
        size_t half = size >> 1;
        T* middle = first + half;

        if (val < *middle)
        {
            size = half;
        }
        else
        {
            first = middle + 1;
            size = size - half - 1;
        }
    }
    return first;
}

template<typename T, typename Value, typename Compare>
T* upper_bound(T* first, T* last, const Value& val, Compare& comp)
{
    size_t size = (size_t)(last - first);
    while (size > 0) {
        size_t half = size >> 1;
        T* middle = first + half;

        if (comp(val, *middle))
        {
            size = half;
        }
        else
        {
            first = middle + 1;
            size = size - half - 1;
        }
    }
    return first;
}

template<typename T>
size_t lower_bound_offset(T* first, size_t size, const T& val)
{
    size_t low = 0;
    while (size > 0) {
        size_t half = size >> 1;
        size_t middle = low + half;

        if (first[middle] < val)
        {
            low = middle + 1;
            size = size - half - 1;
        }
        else
        {
            size = half;
        }
    }
    return low;
}


template<typename T>
T* lower_bound(T* first, T* last, const T& val)
{
    size_t size = (size_t)(last - first);
    while (size > 0) {
        size_t half = size >> 1;
        T* middle = first + half;

        if (*middle < val)
        {
            first = middle + 1;
            size = size - half - 1;
        }
        else
        {
            size = half;
        }
    }
    return first;
}

template<typename T, typename VAL, typename Compare>
T* lower_bound(T* first, T* last, const VAL& val, Compare& comp)
{
    size_t size = (size_t)(last - first);
    while (size > 0) {
        size_t half = size >> 1;
        T* middle = first + half;

        if (comp(*middle, val))
        {
            first = middle + 1;
            size = size - half - 1;
        }
        else
        {
            size = half;
        }
    }
    return first;
}


template<typename T, typename Value>
struct FindRangeComparator
{
    Value (*getval)(T*);

    bool operator() (T& a, const Value& b) const
    {
        return getval(&a) < b;
    }
    bool operator() (const Value& a, T& b) const
    {
        return a < getval(&b);
    }

};

template<typename T, typename Value>
static void find_ranges_internal(T* first, size_t offset, size_t size, FindRangeComparator<T, Value>& comp, void (*callback)(void* ctx, Value value, size_t start, size_t count), void* ctx )
{
    if (size == 0)
        return;
    size_t half = size >> 1;
    T* low = first + offset;
    T* high = low + size;
    T* middle = low + half;
    Value val = comp.getval(middle);
    low = lower_bound(low, middle, val, comp);
    high = upper_bound(middle, high, val, comp);
    callback(ctx, val, low - first, high - low);

    T* rangefirst = first + offset;
    find_ranges_internal(first, offset, low - rangefirst, comp, callback, ctx);
    find_ranges_internal(first, high - first, size - (high - rangefirst), comp, callback, ctx);
}

template<typename T, typename Value>
void find_ranges(T* first, size_t size, Value (*getval)(T*), void (*callback)(void* ctx, Value value, size_t start, size_t count), void* ctx )
{
    FindRangeComparator<T, Value> comp;
    comp.getval = getval;
    find_ranges_internal(first, 0, size, comp, callback, ctx);
}


template<typename T, typename Value>
void find_ranges2(T* first, size_t size, Value (*getval)(T*), void (*callback)(void* ctx, Value value, size_t start, size_t count), void* ctx )
{
    FindRangeComparator<T, Value> comp;
    comp.getval = getval;

    T* end = first + size;
    size_t offset = 0;
    while(offset < size)
    {
        T* p = first + offset;
        Value val = comp.getval(p);
        T* high = std::upper_bound(p, end, val, comp);
        size_t count = high - first - offset;
        callback(ctx, val, offset, count);
        offset += count;
    }

}

} // namespace

#endif
