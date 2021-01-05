#include <stdint.h>
#define JC_ALGORITHM_IMPLEMENTATION
#include <jc/algorithm.h>
#define JC_SORT_IMPLEMENTATION
#include <jc/sort.h>
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
        size_t count = 65536 + rand() % 100;
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
    void SetUp()
    {
        ctx->ranges.clear();
        uint32_t count = 3000;
        ctx->unsorted.resize(count);
        for( uint32_t i = 0; i < count; ++i )
        {
            ctx->unsorted[i] = (uint64_t)rand();
        }
    }

    virtual ~AlgorithmTest();
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

static void PrintArray(uint64_t *a, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("%02d: %016x\n", (int)i, a[i]);
    }
}

TEST_F(AlgorithmTest, SortRadixStable)
{
    bool is_sorted = true;
    uint32_t hash = 0;
    uint64_t sum = 0;

    uint32_t array_size = (uint32_t)ctx->unsorted.size();
    uint32_t buffer_size = buffer_size * (uint32_t)sizeof(uint64_t);
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

static void PrintSortValues(SortValue* values, uint32_t count)
{
    for (uint32_t i = 0; i < count; ++i) {
        uint16_t* p = (uint16_t*)&values[i];
        printf("{ %u, %u }, 0x%04x\n", values[i].key, values[i].payload, (uint32_t)*p );
    }
    printf("\n");
}

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

/*
TEST_F(AlgorithmTest, SortRadixStruct2)
{
    uint32_t size = 129;
    //SortValue* values = (SortValue*)malloc((size+1) * sizeof(SortValue));
    SortValue* tmp = (SortValue*)malloc((size+1) * sizeof(SortValue));

    // for (uint32_t i = 0; i < size; ++i) {
    //     //values[i].key = rand() % 32;
    //     values[i].key = 8;
    //     values[i].payload = i;
    //     //values[i].payload = (size - i);
    // }

    SortValue values[] = { { 0x0100000802EA8B86, 0x00000000 }, { 0x0100000802EA8B86, 0x00000001 }, { 0x0100000802EA8B86, 0x00000002 }, { 0x0100000802EA8B86, 0x00000003 }, { 0x0100000802EA8B86, 0x00000004 }, { 0x0100000802EA8B86, 0x00000005 }, { 0x0100000802EA8B86, 0x00000006 }, { 0x0100000802EA8B86, 0x00000007 }, { 0x0100000802EA8B86, 0x00000008 }, { 0x0100000802EA8B86, 0x00000009 }, { 0x0100000802EA8B86, 0x0000000A }, { 0x0100000802EA8B86, 0x0000000B }, { 0x0100000802EA8B86, 0x0000000C }, { 0x0100000802EA8B86, 0x0000000D }, { 0x0100000802EA8B86, 0x0000000E }, { 0x0100000802EA8B86, 0x0000000F }, { 0x0100000802EA8B86, 0x00000010 }, { 0x0100000802EA8B86, 0x00000011 }, { 0x0100000802EA8B86, 0x00000012 }, { 0x0100000802EA8B86, 0x00000013 }, { 0x0100000802EA8B86, 0x00000014 }, { 0x0100000802EA8B86, 0x00000015 }, { 0x0100000802EA8B86, 0x00000016 }, { 0x0100000802EA8B86, 0x00000017 }, { 0x0100000802EA8B86, 0x00000018 }, { 0x0100000802EA8B86, 0x00000019 }, { 0x0100000802EA8B86, 0x0000001A }, { 0x0100000802EA8B86, 0x0000001B }, { 0x0100000802EA8B86, 0x0000001C }, { 0x0100000802EA8B86, 0x0000001D }, { 0x0100000802EA8B86, 0x0000001E }, { 0x0100000802EA8B86, 0x0000001F }, { 0x0100000802EA8B86, 0x00000020 }, { 0x0100000802EA8B86, 0x00000021 }, { 0x0100000802EA8B86, 0x00000022 }, { 0x0100000802EA8B86, 0x00000023 }, { 0x0100000802EA8B86, 0x00000024 }, { 0x0100000802EA8B86, 0x00000025 }, { 0x0100000802EA8B86, 0x00000026 }, { 0x0100000802EA8B86, 0x00000027 }, { 0x0100000802EA8B86, 0x00000028 }, { 0x0100000802EA8B86, 0x00000029 }, { 0x0100000802EA8B86, 0x0000002A }, { 0x0100000802EA8B86, 0x0000002B }, { 0x0100000802EA8B86, 0x0000002C }, { 0x0100000802EA8B86, 0x0000002D }, { 0x0100000802EA8B86, 0x0000002E }, { 0x0100000802EA8B86, 0x0000002F }, { 0x0100000802EA8B86, 0x00000030 }, { 0x0100000802EA8B86, 0x00000031 }, { 0x0100000802EA8B86, 0x00000032 }, { 0x0100000802EA8B86, 0x00000033 }, { 0x0100000802EA8B86, 0x00000034 }, { 0x0100000802EA8B86, 0x00000035 }, { 0x0100000802EA8B86, 0x00000036 }, { 0x0100000802EA8B86, 0x00000037 }, { 0x0100000802EA8B86, 0x00000038 }, { 0x0100000802EA8B86, 0x00000039 }, { 0x0100000802EA8B86, 0x0000003A }, { 0x0100000802EA8B86, 0x0000003B }, { 0x0100000802EA8B86, 0x0000003C }, { 0x0100000802EA8B86, 0x0000003D }, { 0x0100000802EA8B86, 0x0000003E }, { 0x0100000802EA8B86, 0x0000003F }, { 0x0100000802EA8B86, 0x00000040 }, { 0x0100000802EA8B86, 0x00000041 }, { 0x0100000802EA8B86, 0x00000042 }, { 0x0100000802EA8B86, 0x00000043 }, { 0x0100000802EA8B86, 0x00000044 }, { 0x0100000802EA8B86, 0x00000045 }, { 0x0100000802EA8B86, 0x00000046 }, { 0x0100000802EA8B86, 0x00000047 }, { 0x0100000802EA8B86, 0x00000048 }, { 0x0100000802EA8B86, 0x00000049 }, { 0x0100000802EA8B86, 0x0000004A }, { 0x0100000802EA8B86, 0x0000004B }, { 0x0100000802EA8B86, 0x0000004C }, { 0x0100000802EA8B86, 0x0000004D }, { 0x0100000802EA8B86, 0x0000004E }, { 0x0100000802EA8B86, 0x0000004F }, { 0x0100000802EA8B86, 0x00000050 }, { 0x0100000802EA8B86, 0x00000051 }, { 0x0100000802EA8B86, 0x00000052 }, { 0x0100000802EA8B86, 0x00000053 }, { 0x0100000802EA8B86, 0x00000054 }, { 0x0100000802EA8B86, 0x00000055 }, { 0x0100000802EA8B86, 0x00000056 }, { 0x0100000802EA8B86, 0x00000057 }, { 0x0100000802EA8B86, 0x00000058 }, { 0x0100000802EA8B86, 0x00000059 }, { 0x0100000802EA8B86, 0x0000005A }, { 0x0100000802EA8B86, 0x0000005B }, { 0x0100000802EA8B86, 0x0000005C }, { 0x0100000802EA8B86, 0x0000005D }, { 0x0100000802EA8B86, 0x0000005E }, { 0x0100000802EA8B86, 0x0000005F }, { 0x0100000802EA8B86, 0x00000060 }, { 0x0100000802EA8B86, 0x00000061 }, { 0x0100000802EA8B86, 0x00000062 }, { 0x0100000802EA8B86, 0x00000063 }, { 0x0100000802EA8B86, 0x00000064 }, { 0x0100000802EA8B86, 0x00000065 }, { 0x0100000802EA8B86, 0x00000066 }, { 0x0100000802EA8B86, 0x00000067 }, { 0x0100000802EA8B86, 0x00000068 }, { 0x0100000802EA8B86, 0x00000069 }, { 0x0100000802EA8B86, 0x0000006A }, { 0x0100000802EA8B86, 0x0000006B }, { 0x0100000802EA8B86, 0x0000006C }, { 0x0100000802EA8B86, 0x0000006D }, { 0x0100000802EA8B86, 0x0000006E }, { 0x0100000802EA8B86, 0x0000006F }, { 0x0100000802EA8B86, 0x00000070 }, { 0x0100000802EA8B86, 0x00000071 }, { 0x0100000802EA8B86, 0x00000072 }, { 0x0100000802EA8B86, 0x00000073 }, { 0x0100000802EA8B86, 0x00000074 }, { 0x0100000802EA8B86, 0x00000075 }, { 0x0100000802EA8B86, 0x00000076 }, { 0x0100000802EA8B86, 0x00000077 }, { 0x0100000802EA8B86, 0x00000078 }, { 0x0100000802EA8B86, 0x00000079 }, { 0x0100000802EA8B86, 0x0000007A }, { 0x0100000802EA8B86, 0x0000007B }, { 0x0100000802EA8B86, 0x0000007C }, { 0x0100000802EA8B86, 0x0000007D }, { 0x0100000802EA8B86, 0x0000007E }, { 0x0100000802EA8B86, 0x0000007F }, { 0x01FFFFF80726614F, 0x00000080 }, {0, 0} };

    values[size].key = 0xcdcdcdcdcdcdcdcd;
    values[size].payload = 0xcdcdcdcd;

    tmp[size].key = 0xcdcdcdcdcdcdcdcd;
    tmp[size].payload = 0xcdcdcdcd;

    // printf("\n");
    //PrintSortValues(values, size);

    jc::radix_sort(values, values + size, tmp);

    //PrintSortValues(values, size);

    ASSERT_EQ((uint64_t)0xcdcdcdcdcdcdcdcd, tmp[size].key);
    ASSERT_EQ(0xcdcdcdcd, tmp[size].payload);
    ASSERT_EQ((uint64_t)0xcdcdcdcdcdcdcdcd, values[size].key);
    ASSERT_EQ(0xcdcdcdcd, values[size].payload);
}
*/
