
#include <stdint.h>
#define JC_ALGORITHM_IMPLEMENTATION
#include <jc/algorithm.h>
#define JC_SORT_IMPLEMENTATION
#include <jc/sort.h>
#include <algorithm>
#include <vector>

struct SRange
{
    int sortkey;
    size_t start;
    size_t count;
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

typedef struct SCtx
{
    std::vector<SRange> ranges;
    std::vector<RenderObject> renderobjects;
    std::vector<uint64_t> unsorted;
} SCtx;

static SCtx* algorithm_main_setup()
{
    SCtx* ctx = new SCtx;

    size_t count = 65536 + rand() % 100;
    size_t num_buckets = 20;
    ctx->renderobjects.reserve(count);
    for( uint32_t i = 0; i < count; ++i)
    {
        RenderObject obj;
        obj.payload = i;
        obj.sortkey = i % num_buckets;
        ctx->renderobjects.push_back(obj);
    }
    std::sort(ctx->renderobjects.begin(), ctx->renderobjects.end(), compare_render_object);

    return ctx;
}

static void algorithm_main_teardown(SCtx* ctx)
{
    delete ctx;
}

static void test_setup(SCtx* ctx)
{
    ctx->ranges.clear();

    uint32_t count = 4;
    ctx->unsorted.resize(count);
    for( uint32_t i = 0; i < count; ++i )
    {
        ctx->unsorted[i] = rand();
    }
}

static void test_teardown(SCtx* ctx)
{
    (void)ctx;
}

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

static void algorithm_upper_bound(SCtx*)
{
    int* it_stl;
    int* it_jc;

    int nbuffervalues = 3;
    int aa[] = {10000000,10000000,10000000,0,1,2,3,4,5,6,7,8,9,-10000000,-10000000,-10000000};
    int* a = aa+nbuffervalues;
    int asize = ARRAY_SIZE(aa) - 2*nbuffervalues;

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

static void algorithm_lower_bound(SCtx*)
{
    int* it_stl;
    int* it_jc;

    //int a[] = {0,1,2,3,4,5,6,7,8,9};
    int nbuffervalues = 3;
    int aa[] = {10000000,10000000,10000000,0,1,2,3,4,5,6,7,8,9,-10000000,-10000000,-10000000};
    int* a = aa+nbuffervalues;
    int asize = ARRAY_SIZE(aa) - 2*nbuffervalues;

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

static void algorithm_lower_bound_file(SCtx*)
{
    int asize = 0;
    int* a = ReadArray("/Users/mathiaswesterdahl/work/containers/test.txt", asize);
    ASSERT_NE(0, a);

    int nbuffervalues = 3;

    for( int t = -nbuffervalues; t < asize+nbuffervalues; ++t)
    {
        int* it_stl = std::lower_bound(a, a+asize, t);
        int* it_jc = jc::lower_bound(a, a+asize, t);

        ASSERT_EQ( (it_stl - a), (it_jc - a) );
    }
}


static void range_callback(void* _ctx, int key, size_t start, size_t count)
{
    SCtx* ctx = (SCtx*)_ctx;
    SRange range;
    range.sortkey = key;
    range.start = start;
    range.count = count;
    ctx->ranges.push_back(range);
}

static inline int getsortkey(RenderObject* obj)
{
    return obj->sortkey;
}

static void algorithm_find_ranges(SCtx* ctx)
{
    RenderObject a[] = {
        {100, 0}, {101, 0}, {103, 0},
        {200, 1}, {201, 1}, {203, 1}, {204, 1},
        {300, 2}, {301, 2},
        {400, 3}, {401, 3}, {403, 3},
    };

    jc::find_ranges(a, ARRAY_SIZE(a), getsortkey, range_callback, (void*)ctx);

    ASSERT_EQ( (size_t)4, ctx->ranges.size() );
#if 1
    SRange ranges[] = {
        {1, 3, 4},
        {0, 0, 3},
        {3, 9, 3},
        {2, 7, 2},
    };
#else
    SRange ranges[] = {
        {0, 0, 3},
        {1, 3, 4},
        {2, 7, 2},
        {3, 9, 3},
    };
#endif

    for( size_t i = 0; i < ctx->ranges.size(); ++i)
    {
        SRange& range1 = ranges[i];
        SRange& range2 = ctx->ranges[i];
        //printf("key %d,  start %lu,  count %lu\n", range2.sortkey, range2.start, range2.count);
        ASSERT_EQ(range1.sortkey, range2.sortkey);
        ASSERT_EQ(range1.start, range2.start);
        ASSERT_EQ(range1.count, range2.count);
    }
}


static void algorithm_find_ranges_large(SCtx* ctx)
{
    jc::find_ranges(&ctx->renderobjects[0], ctx->renderobjects.size(), getsortkey, range_callback, (void*)ctx);

    size_t sum = 0;
    for( size_t i = 0; i < ctx->ranges.size(); ++i)
    {
        SRange& range2 = ctx->ranges[i];
        //printf("key %d,  start %lu,  count %lu\n", range2.sortkey, range2.start, range2.count);
        sum += range2.count;
    }

    ASSERT_EQ( (size_t)20, ctx->ranges.size() );
    ASSERT_EQ( sum, ctx->renderobjects.size() );
}


static void sort_radix(SCtx* ctx)
{
    // printf("Before\n");
    // for(size_t i = 0; i < ctx->unsorted.size(); ++i)
    // {
    //     printf("%2lu: %u\t%08X. p: %p\n", i, ctx->unsorted[i], ctx->unsorted[i], (void*)&ctx->unsorted[i]);
    // }
    // printf("\n");

    uint64_t* begin = &ctx->unsorted[0];
    jc::radix_sort<uint64_t>(begin, begin + ctx->unsorted.size());

    // printf("\n");
    // printf("After\n");
    // for(size_t i = 0; i < ctx->unsorted.size(); ++i)
    // {
    //     printf("%2lu: %u\t%08X\n", i, ctx->unsorted[i], ctx->unsorted[i]);
    // }
    // printf("\n");

    for(size_t i = 1; i < ctx->unsorted.size(); ++i)
    {
        ASSERT_TRUE( ctx->unsorted[i-1] <= ctx->unsorted[i] );
    }

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
      hash ^= static_cast<unsigned char>(buf[2]) << 16;
    case 2:
      hash ^= static_cast<unsigned char>(buf[1]) << 8;
    case 1:
      hash ^= static_cast<unsigned char>(buf[0]);
      hash *= m;
  };

  // Do a few final mixes of the hash.
  hash ^= hash >> 13;
  hash *= m;
  hash ^= hash >> 15;
  return hash;
}

static void sort_radix_stable(SCtx* ctx)
{
    printf("Before\n");
    for(size_t i = 0; i < ctx->unsorted.size(); ++i)
    {
        printf("%2lu: %u\t%08X\n", i, ctx->unsorted[i], ctx->unsorted[i]);
    }
    printf("\n");

    bool is_sorted = true;
    uint32_t hash = 0;
    uint32_t sum = ctx->unsorted[0];
    for(size_t i = 1; i < ctx->unsorted.size(); ++i)
    {
        if (ctx->unsorted[i-1] > ctx->unsorted[i])
        {
            is_sorted = false;
        }
        hash = Hash32((uint8_t*)&ctx->unsorted[i], sizeof(ctx->unsorted[0]), hash);
        sum += ctx->unsorted[i];
    }

    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);

    ASSERT_TRUE(!is_sorted);

    std::vector<uint64_t> tmp;
    tmp.resize(ctx->unsorted.size());
    uint64_t* begin = &ctx->unsorted[0];
    jc::radix_sort_stable<uint64_t>(begin, begin + ctx->unsorted.size(), &tmp[0]);
    uint64_t* sorted = begin; // Since we sort an even number of bytes, this is true

    printf("\n");
    printf("After\n");
    for(size_t i = 0; i < ctx->unsorted.size(); ++i)
    {
        printf("%2lu: %u\t%08X\n", i, ctx->unsorted[i], ctx->unsorted[i]);
    }
    printf("\n");

    uint32_t sum_after = sorted[0];
    uint32_t hash_after = 0;
    for(size_t i = 1; i < ctx->unsorted.size(); ++i)
    {
        ASSERT_TRUE( sorted[i-1] <= sorted[i] );
        sum_after += sorted[i];
        hash_after = Hash32((uint8_t*)&sorted[i], sizeof(sorted[0]), hash_after);
    }

    ASSERT_EQ(sum, sum_after);
    ASSERT_NE(hash, hash_after);

}

TEST_BEGIN(algorithm_test, algorithm_main_setup, algorithm_main_teardown, test_setup, test_teardown)
    TEST(algorithm_upper_bound)
    TEST(algorithm_lower_bound)
    TEST(algorithm_lower_bound_file)
    TEST(algorithm_find_ranges)
    TEST(algorithm_find_ranges_large)
    TEST(sort_radix_stable)
    //TEST(sort_radix)
TEST_END(algorithm_test)
