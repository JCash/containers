#include <stdint.h>
#define JC_ALGORITHM_IMPLEMENTATION
#include <jc/cpp/algorithm.h>
#define JC_SORT_IMPLEMENTATION
#include <jc/cpp/sort.h>
#define JC_TEST_USE_DEFAULT_MAIN
#include "jc_test.h"
#include <algorithm>
#include <vector>

struct SRange
{
    size_t sortkey;
    size_t start;
    size_t count;
    size_t _pad;
};

struct RenderObject
{
    int payload;
    int sortkey;
};

static bool compare_render_object(const RenderObject& a, const RenderObject& b)
{
    return a.sortkey < b.sortkey;
}

static uint32_t Hash32(uint8_t* buf, uint32_t len, uint32_t seed)
{
  const uint32_t m = 0x5bd1e995;
  uint32_t hash = seed ^ len;

  // Mix 4 bytes at a time into the hash.
  while (len >= 4)
  {
    uint32_t k = *reinterpret_cast<uint32_t*>(buf);
    k *= m;
    k ^= k >> 24;
    k *= m;
    hash *= m;
    hash ^= k;
    buf += 4;
    len -= 4;
  }

  // Handle the last few bytes of the input array.
  switch (len)
  {
    case 3:
      hash ^= (uint32_t)(static_cast<unsigned char>(buf[2]) << 16);
    case 2:
      hash ^= (uint32_t)(static_cast<unsigned char>(buf[1]) << 8);
    case 1:
      hash ^= (uint32_t)(static_cast<unsigned char>(buf[0]) << 0);
      hash *= m;
  };

  // Do a few final mixes of the hash.
  hash ^= hash >> 13;
  hash *= m;
  hash ^= hash >> 15;
  return hash;
}

typedef struct SCtxAlgorithm
{
    std::vector<SRange> ranges;
    std::vector<RenderObject> renderobjects;
    std::vector<uint64_t> unsorted;
} SCtxAlgorithm;

class AlgorithmTest : public jc_test_base_class
{
public:
    static SCtxAlgorithm* ctx;

    static void SetUpTestCase() {
        ctx = new SCtxAlgorithm;
        size_t count = 65536 + size_t(rand() % 100);
        size_t num_buckets = 20;
        ctx->renderobjects.reserve(count);
        for( size_t i = 0; i < count; ++i)
        {
            RenderObject obj;
            obj.payload = (int)i;
            obj.sortkey = (int)(i % num_buckets);
            ctx->renderobjects.push_back(obj);
        }
        std::sort(ctx->renderobjects.begin(), ctx->renderobjects.end(), compare_render_object);
    }

    static void TearDownTestCase() {
        delete ctx;
    }

protected:
    void SetUp() override
    {
        ctx->ranges.clear();
        uint32_t count = 3000;
        ctx->unsorted.resize(count);
        for( uint32_t i = 0; i < count; ++i )
        {
            ctx->unsorted[i] = (uint64_t)rand();
        }
    }

    virtual ~AlgorithmTest() override;
};

AlgorithmTest::~AlgorithmTest() {}

SCtxAlgorithm* AlgorithmTest::ctx = 0;


#define ARRAY_SIZE(_X) (sizeof(_X)/sizeof(_X[0]))


/*
static int* CreateArray(size_t size)
{
    int* a = new int[size];
    for(size_t i = 0; i < size; ++i)
    {
        a[i] = rand();
    }
    std::sort(a, a+size);
    return a;
}

static void DestroyArray/(int* a)
{
    delete[] a;
}
*/

static bool compare(int a, int b)
{
    return a < b;
}

TEST_F(AlgorithmTest, UpperBound)
{
    int* it_stl;
    int* it_jc;

    int nbuffervalues = 3;
    int aa[] = {10000000,10000000,10000000,0,1,2,3,4,5,6,7,8,9,-10000000,-10000000,-10000000};
    int* a = aa+nbuffervalues;
    int asize = (int)ARRAY_SIZE(aa) - 2*nbuffervalues;

    for( int t = -nbuffervalues; t < asize+nbuffervalues; ++t)
    {
        it_stl = std::upper_bound(a, a+asize, t);
        it_jc = jc::upper_bound(a, a+asize, t);

        ASSERT_EQ( (it_stl - a), (it_jc - a) );
    }

    for( int t = -nbuffervalues; t < asize+nbuffervalues; ++t)
    {
        it_stl = std::upper_bound(a, a+asize, t, compare);
        it_jc = jc::upper_bound(a, a+asize, t, compare);

        ASSERT_EQ( (it_stl - a), (it_jc - a) );
    }
}

TEST_F(AlgorithmTest, LowerBound)
{
    int* it_stl;
    int* it_jc;

    //int a[] = {0,1,2,3,4,5,6,7,8,9};
    int nbuffervalues = 3;
    int aa[] = {10000000,10000000,10000000,0,1,2,3,4,5,6,7,8,9,-10000000,-10000000,-10000000};
    int* a = aa+nbuffervalues;
    int asize = (int)ARRAY_SIZE(aa) - 2*nbuffervalues;

    for( int t = -nbuffervalues; t < asize+nbuffervalues; ++t)
    {
        it_stl = std::lower_bound(a, a+asize, t);
        it_jc = jc::lower_bound(a, a+asize, t);

        ASSERT_EQ( (it_stl - a), (it_jc - a) );
    }

    for( int t = -nbuffervalues; t < asize+nbuffervalues; ++t)
    {
        it_stl = std::lower_bound(a, a+asize, t, compare);
        it_jc = jc::lower_bound(a, a+asize, t, compare);

        ASSERT_EQ( (it_stl - a), (it_jc - a) );
    }
}

static int* ReadArray(const char* path, int& asize)
{
    asize = 0;
    FILE* f = fopen(path, "rb");
    if (!f)
        return 0;

    std::vector<int> va;
    char buffer[64];
    while(fgets(buffer, sizeof(buffer), f))
    {
        va.push_back(atoi(buffer));
    }

    fclose(f);

    asize = (int)va.size();
    int* a = new int[asize];
    for( uint32_t i = 0; i < va.size(); ++i)
    {
        a[i] = va[i];
    }
    return a;
}


TEST_F(AlgorithmTest, LowerBoundFile)
{
    int asize = 0;
    int* a = ReadArray("./test/test.txt", asize);

    int nbuffervalues = 3;

    for( int t = -nbuffervalues; t < asize+nbuffervalues; ++t)
    {
        int* it_stl = std::lower_bound(a, a+asize, t);
        int* it_jc = jc::lower_bound(a, a+asize, t);

        ASSERT_EQ( (it_stl - a), (it_jc - a) );
    }

    delete[] a;
}

static bool IsSorted(uint64_t* a, size_t size)
{
    for (size_t i = 0; i < size-1; ++i)
    {
        if (a[i] > a[i+1])
            return false;
    }
    return true;
}

// static void PrintArray(uint64_t *a, size_t size)
// {
//     for (size_t i = 0; i < size; ++i)
//     {
//         printf("%02d: %016x\n", (int)i, a[i]);
//     }
// }

TEST_F(AlgorithmTest, SortRadixStable)
{
    uint32_t array_size = (uint32_t)ctx->unsorted.size();
    uint32_t buffer_size = array_size * (uint32_t)sizeof(uint64_t);
    do {
        for (uint32_t i = 0; i < array_size; ++i)
        {
            ctx->unsorted[i] = (uint64_t)rand();
        }
    } while (IsSorted(&ctx->unsorted[0], array_size));

    std::vector<uint64_t> array_copy(ctx->unsorted);
    std::sort(array_copy.begin(), array_copy.end());

    ASSERT_TRUE(IsSorted(&array_copy[0], array_size));

    uint32_t expected_hash = Hash32((uint8_t *)&array_copy[0], buffer_size, 0);

    std::vector<uint64_t> tmp;
    tmp.resize(array_size);

    uint64_t* begin = &ctx->unsorted[0];
    jc::radix_sort<uint64_t>(begin, begin + array_size, &tmp[0]);
    // Since we sort an even number of bytes,
    // the final destination is the original buffer
    uint64_t *sorted = begin;

    uint32_t sorted_hash = Hash32((uint8_t *)sorted, buffer_size, 0);
    ASSERT_TRUE(IsSorted(sorted, array_size));

    ASSERT_EQ(expected_hash, sorted_hash);
}

struct SortValue {
    uint8_t key;
    uint8_t payload;
};


// template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const SortValue* value) {
//     return buffer + JC_TEST_SNPRINTF(buffer, buffer_len, "{%llu, %llu}", value->key, value->payload);
// }

// static void PrintSortValues(SortValue* values, uint32_t count)
// {
//     for (uint32_t i = 0; i < count; ++i) {
//         uint16_t *p = (uint16_t *)(void*)&values[i];
//         printf("{ %u, %u }, 0x%04x\n", values[i].key, values[i].payload, (uint32_t)*p );
//     }
//     printf("\n");
// }

TEST_F(AlgorithmTest, SortRadixStruct)
{
    #define SENTINEL_VALUE 0xcd //cdcdcdcdcdcdcd
    #define SENTINEL {SENTINEL_VALUE,SENTINEL_VALUE}
    #define SENTINEL_SIZE 1

    SortValue values[]              = {{4, 3}, {1, 9}, {2, 3}, {1, 2}, {0, 2}, {4, 2}, {1, 5}, SENTINEL };
    SortValue expected_structkey[]  = {{0, 2}, {1, 9}, {1, 2}, {1, 5}, {2, 3}, {4, 3}, {4, 2}, SENTINEL};
    SortValue expected_stable[]     = {{0, 2}, {1, 2}, {4, 2}, {2, 3}, {4, 3}, {1, 5}, {1, 9}, SENTINEL};

    uint32_t size = (uint32_t)sizeof(values)/sizeof(values[0]) - SENTINEL_SIZE;
    SortValue* tmp = (SortValue*)malloc(sizeof(values));
    memcpy(tmp, values, sizeof(values));

    //printf("Original values\n");
    //PrintSortValues(values, size+SENTINEL_SIZE);
    //PrintSortValues(tmp, size+SENTINEL_SIZE);

    jc::radix_sort_n<sizeof(values[0].key)>(values, values + size, tmp);

    ASSERT_ARRAY_EQ(expected_structkey, values);
    ASSERT_EQ(SENTINEL_VALUE, tmp[size].key);
    ASSERT_EQ(SENTINEL_VALUE, tmp[size].payload);
    ASSERT_EQ(SENTINEL_VALUE, values[size].key);
    ASSERT_EQ(SENTINEL_VALUE, values[size].payload);

    jc::radix_sort(values, values + size, tmp);

    ASSERT_ARRAY_EQ(expected_stable, values);
    ASSERT_EQ(SENTINEL_VALUE, tmp[size].key);
    ASSERT_EQ(SENTINEL_VALUE, tmp[size].payload);
    ASSERT_EQ(SENTINEL_VALUE, values[size].key);
    ASSERT_EQ(SENTINEL_VALUE, values[size].payload);

    #undef SENTINEL
    #undef SENTINEL_SIZE
}
