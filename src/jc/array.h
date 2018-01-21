#pragma once

#include <stdlib.h>
#include <assert.h> // disable with NDEBUG

namespace jc
{

//
// Uses realloc to allocate memory. Don't use for aligned types

template <typename T>
class Array
{
public:
    Array() : m_Start(0), m_End(0), m_Back(0)   {}
    Array(size_t capacity)                      { SetCapacity(capacity); }
    ~Array()                                    { if (m_Start) free(m_Start); }

    T*          Begin()             { return m_Start; }
    const T*    Begin() const       { return m_Start; }
    T*          End()               { return m_End; }
    const T*    End() const         { return m_End; }
    size_t      Size() const        { return m_End - m_Start; }
    bool        Empty() const       { return m_End == m_Start; }
    bool        Full() const        { return m_End == m_Back; }

    T&          operator[] (int i)          { assert(i < int(m_End - m_Start)); return m_Start[i]; }
    const T&    operator[] (int i) const    { assert(i < int(m_End - m_Start)); return m_Start[i]; }

    size_t      GetCapacity() const { return m_Back - m_Start; }
    // Increases or decreases capacity. Invalidates pointers to elements
    void        SetCapacity(size_t capacity);

    void        Push(const T& item);

private:
    T* m_Start;
    T* m_End;
    T* m_Back;

    Array(const Array<T>& rhs);
    Array<T>& operator= (const Array<T>& rhs);
    bool operator== (const Array<T>& rhs);
};

template <typename T>
void Array<T>::SetCapacity(size_t capacity)
{
    size_t old_capacity = m_Back - m_Start;
    if (capacity == old_capacity)
        return;

    size_t size = m_End - m_Start;
    m_Start = (T*)realloc(m_Start, sizeof(T) * capacity);
    m_End = m_Start + size;
    m_Back = m_Start + capacity;
}


template <typename T>
void Array<T>::Push(const T& item)
{
    assert(!Full());
    *m_End++ = item;
}

} // namespace
