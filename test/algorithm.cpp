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

TEST_F(AlgorithmTest, SortRadixFullWidthUint64)
{
    const size_t bit_count = 64;
    uint64_t values[bit_count + 3];
    values[0] = UINT64_MAX;
    values[1] = UINT64_MAX - 1;
    for (size_t i = 0; i < bit_count; ++i)
        values[i + 2] = UINT64_C(1) << (bit_count - 1 - i);
    values[bit_count + 2] = 0;

    const size_t count = ARRAY_SIZE(values);
    uint64_t expected[count];
    uint64_t tmp[count];
    std::copy_n(values, count, expected);
    std::sort(expected, expected + count);

    jc::radix_sort(values, values + count, tmp);

    ASSERT_ARRAY_EQ(expected, values);
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
    const SortValue input_guard = {0, 0};
    const SortValue scratch_guard = {0xcd, 0xcd};
    SortValue by_key[] = {{4, 3}, {1, 9}, {2, 3}, {1, 2}, {0, 2}, {4, 2}, {1, 5}, input_guard};
    SortValue by_record[ARRAY_SIZE(by_key)];
    std::copy_n(by_key, ARRAY_SIZE(by_key), by_record);
    const size_t count = ARRAY_SIZE(by_key) - 1;

    SortValue key_tmp[ARRAY_SIZE(by_key)] = {};
    key_tmp[count] = scratch_guard;
    jc::radix_sort_n<sizeof(by_key[0].key)>(by_key, by_key + count, key_tmp);

    SortValue expected_by_key[] = {{0, 2}, {1, 9}, {1, 2}, {1, 5}, {2, 3}, {4, 3}, {4, 2}, input_guard};
    ASSERT_ARRAY_EQ(expected_by_key, by_key);
    ASSERT_ARRAY_EQ_LEN(&scratch_guard, key_tmp + count, 1);

    SortValue record_tmp[ARRAY_SIZE(by_record)] = {};
    record_tmp[count] = scratch_guard;
    jc::radix_sort(by_record, by_record + count, record_tmp);

    SortValue expected_by_record[] = {{0, 2}, {1, 2}, {4, 2}, {2, 3}, {4, 3}, {1, 5}, {1, 9}, input_guard};
    ASSERT_ARRAY_EQ(expected_by_record, by_record);
    ASSERT_ARRAY_EQ_LEN(&scratch_guard, record_tmp + count, 1);
}

template <int KeyBytes, size_t Count>
static void CheckRadixSortPrefixStability()
{
    struct Record
    {
        uint8_t key[3];
        uint8_t payload;
    };
    // Some two-byte ties differ in the third byte. Complete keys also repeat.
    const uint8_t keys[][3] = {
        {0xff, 0, 1},
        {0,    1, 0},
        {1,    0, 1},
        {0xff, 0, 0},
        {0,    1, 0},
        {0xff, 0, 1},
        {0,    0, 1}
    };
    Record values[Count];
    for (size_t i = 0; i < Count; ++i)
    {
        std::copy_n(keys[i % ARRAY_SIZE(keys)], ARRAY_SIZE(values[i].key), values[i].key);
        // Alternate low and high payloads to make the input order of ties visible.
        values[i].payload = static_cast<uint8_t>(i % 2 == 0 ? i / 2 : Count - 1 - i / 2);
    }
    Record expected[Count];
    Record tmp[Count];
    std::copy_n(values, Count, expected);
    std::stable_sort(expected, expected + Count, [](const Record& a, const Record& b) {
        for (int byte = KeyBytes - 1; byte >= 0; --byte)
        {
            if (a.key[byte] != b.key[byte])
                return a.key[byte] < b.key[byte];
        }
        return false;
    });

    jc::radix_sort_n<KeyBytes>(values, values + Count, tmp);

    EXPECT_ARRAY_EQ(expected, values);
}

TEST_F(AlgorithmTest, SortRadixStableTwoByteKeys)
{
    CheckRadixSortPrefixStability<2, 7>();
    CheckRadixSortPrefixStability<2, 64>();
}

TEST_F(AlgorithmTest, SortRadixStableThreeByteKeys)
{
    CheckRadixSortPrefixStability<3, 7>();
    CheckRadixSortPrefixStability<3, 64>();
}
