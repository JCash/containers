#pragma once

#include <stdint.h>

typedef uint64_t valuesmall_t;
typedef struct SValue
{
    int i1;
    int i2;
    int i3;
    float f1;
    float f2;
    float f3;
    char* charp;

    float rect[4];

    int* intp;
    float position[2];

    int blob[20];
    uint64_t value;

    SValue() {}
    SValue(uint64_t v) : value(v) {}
} valuelarge_t;


#if defined(IMPL_STL)
    #include <vector>
    #define CONTAINERNAME "std::vector"
    #define SET_CAPACITY(_CONTAINER, _SIZE) (_CONTAINER).reserve(_SIZE)
    #define SET_SIZE(_CONTAINER, _SIZE)     (_CONTAINER).resize(_SIZE)
    #define GET_SIZE(_CONTAINER)            (_CONTAINER).size()
    #define PUSH(_CONTAINER, _VALUE)        (_CONTAINER).push_back(_VALUE)
    typedef std::vector<valuesmall_t> container_valuesmall_t;
    typedef std::vector<valuelarge_t> container_valuelarge_t;

#elif defined(IMPL_EASTL)
    #define EASTL_EABASE_DISABLED
    #include <EASTL/vector.h>
    #define CONTAINERNAME "eastl::vector"
    #define SET_CAPACITY(_CONTAINER, _SIZE) (_CONTAINER).reserve(_SIZE)
    #define SET_SIZE(_CONTAINER, _SIZE)     (_CONTAINER).resize(_SIZE)
    #define GET_SIZE(_CONTAINER)            (_CONTAINER).size()
    #define PUSH(_CONTAINER, _VALUE)        (_CONTAINER).push_back(_VALUE)
    typedef eastl::vector<valuesmall_t>     container_valuesmall_t;
    typedef eastl::vector<valuelarge_t>     container_valuelarge_t;

#elif defined(IMPL_BOOST)
    #include <boost/container/vector.hpp>
    #define CONTAINERNAME "boost::vector"
    #define SET_CAPACITY(_CONTAINER, _SIZE) (_CONTAINER).reserve(_SIZE)
    #define SET_SIZE(_CONTAINER, _SIZE)     (_CONTAINER).resize(_SIZE)
    #define GET_SIZE(_CONTAINER)            (_CONTAINER).size()
    #define PUSH(_CONTAINER, _VALUE)        (_CONTAINER).push_back(_VALUE)
    typedef boost::container::vector<valuesmall_t> container_valuesmall_t;
    typedef boost::container::vector<valuelarge_t> container_valuelarge_t;

#elif defined(IMPL_C)
    #define CONTAINERNAME "carray"
    typedef valuesmall_t* container_valuesmall_t;
    typedef valuelarge_t* container_valuelarge_t;

#elif defined(IMPL_JC)
    #include <jc/array.h>
    #define CONTAINERNAME "jc::Array"
    #define SET_CAPACITY(_CONTAINER, _SIZE) (_CONTAINER).SetCapacity(_SIZE)
    #define SET_SIZE(_CONTAINER, _SIZE)     (_CONTAINER).SetSize(_SIZE)
    #define GET_SIZE(_CONTAINER)            (_CONTAINER).Size()
    #define PUSH(_CONTAINER, _VALUE)        (_CONTAINER).Push(_VALUE)
    typedef jc::Array<valuesmall_t> container_valuesmall_t;
    typedef jc::Array<valuelarge_t> container_valuelarge_t;

#endif
