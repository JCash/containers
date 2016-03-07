
#if defined(IMPL_EASTL)
#include <stdlib.h>


// EASTL expects us to define these, see allocator.h line 194
void* operator new[](size_t size, const char* /* pName */,
                     int /* flags */, unsigned /* debugFlags */,
                     const char* /* file */, int /* line */) {
    return malloc(size);
}

void* operator new[](size_t size, size_t alignment,
                     size_t /* alignmentOffset */, const char* /* pName */,
                     int /* flags */, unsigned /* debugFlags */,
                     const char* /* file */, int /* line */) {
    return malloc(size);
}
#endif
