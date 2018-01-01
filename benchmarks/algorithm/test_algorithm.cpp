#include "defines.h"
#include "../timeit.h"
#include "../report.h"
#include "../memory.h"

#include <assert.h>
#include <stdlib.h>     // srand, rand
#include <chrono>

//#define ASSERT(_X_)       assert(_X_)
#define ASSERT(_X_)

struct SCtx
{
    int                 verbose;
    uint32_t            num_elements;
    std::vector<uint32_t> values32;
    std::vector<uint32_t> outvalues32;
    std::vector<uint64_t> values64;
    std::vector<uint64_t> outvalues64;
};


static void create(SCtx& ctx)
{
    ctx.values32.clear();
    size_t size = ctx.num_elements;
    ctx.values32.reserve(size);
    for( uint32_t i = 0; i < size; ++i)
        ctx.values32.push_back(i*3);
}

static void setup_sort(SCtx& ctx)
{
    ctx.values32.clear();
    ctx.values64.clear();
    ctx.outvalues32.clear();
    ctx.outvalues64.clear();

    size_t size = ctx.num_elements;
    ctx.values32.reserve(size);
    ctx.values64.reserve(size);
    for( uint32_t i = 0; i < size; ++i)
    {
        ctx.values32.push_back(rand());
        ctx.values64.push_back( uint64_t(rand()) << 32 | rand() );
    }
    ctx.outvalues32.resize(ctx.values32.size());
    ctx.outvalues64.resize(ctx.values64.size());
}

static uint64_t upper_bound(SCtx& ctx)
{
    uint64_t sum = 0;
    size_t size = ctx.values32.size();
    value_t* start = &ctx.values32[0];
    value_t* end = start + size;
    for( size_t i = 0; i < size; i += 4 )
    {
        value_t* value = UPPER_BOUND(start, end, i);
        sum += *value;
    }
    return (size_t)sum;
}

static uint64_t lower_bound(SCtx& ctx)
{
    uint64_t sum = 0;
    size_t size = ctx.values32.size();
    value_t* start = &ctx.values32[0];
    value_t* end = start + size;
    for( size_t i = 0; i < size; i += 4 )
    {
        value_t* value = LOWER_BOUND(start, end, i);
        sum += *value;
    }
    return (size_t)sum;
}

static inline bool compare_int(int a, int b)
{
    return a < b;
}

static uint64_t sort32(SCtx& ctx)
{
#if defined(IMPL_SKA)
    SORT(ctx.values32.begin(), ctx.values32.end(), ctx.outvalues32.begin());
    return ctx.outvalues32[0] + ctx.outvalues32[ctx.outvalues32.size()/2] + ctx.outvalues32[ctx.outvalues32.size()-1];
#elif defined(IMPL_JC)
    SORT(&ctx.values32[0], &ctx.values32[0] + ctx.values32.size());
    return ctx.values32[0] + ctx.values32[ctx.values32.size()/2] + ctx.values32[ctx.values32.size()-1];
#else
    SORT(ctx.values32.begin(), ctx.values32.end(), compare_int);
    return ctx.values32[0] + ctx.values32[ctx.values32.size()/2] + ctx.values32[ctx.values32.size()-1];
#endif
}

static uint64_t sort64(SCtx& ctx)
{
#if defined(IMPL_SKA)
    SORT(ctx.values64.begin(), ctx.values64.end(), ctx.outvalues64.begin());
    return ctx.outvalues64[0] + ctx.outvalues64[ctx.outvalues64.size()/2] + ctx.outvalues64[ctx.outvalues64.size()-1];
#elif defined(IMPL_JC)
    SORT(&ctx.values64[0], &ctx.values64[0] + ctx.values64.size());
    return ctx.values64[0] + ctx.values64[ctx.values64.size()/2] + ctx.values64[ctx.values64.size()-1];
#else
    SORT(ctx.values64.begin(), ctx.values64.end(), compare_int);
    return ctx.values64[0] + ctx.values64[ctx.values64.size()/2] + ctx.values64[ctx.values64.size()-1];
#endif
}

static uint64_t stable_sort32(SCtx& ctx)
{
#if defined(IMPL_JC)
    STABLE_SORT(&ctx.values32[0], &ctx.values32[0] + ctx.values32.size(), &ctx.outvalues32[0]);
    return ctx.values32[0] + ctx.values32[ctx.values32.size()/2] + ctx.values32[ctx.values32.size()-1];
#else
    STABLE_SORT(ctx.values32.begin(), ctx.values32.end(), compare_int);
    return ctx.values32[0] + ctx.values32[ctx.values32.size()/2] + ctx.values32[ctx.values32.size()-1];
#endif
}

static uint64_t stable_sort64(SCtx& ctx)
{
#if defined(IMPL_JC)
    STABLE_SORT(&ctx.values64[0], &ctx.values64[0] + ctx.values64.size(), &ctx.outvalues64[0]);
    return ctx.values64[0] + ctx.values64[ctx.values64.size()/2] + ctx.values64[ctx.values64.size()-1];
#else
    STABLE_SORT(ctx.values64.begin(), ctx.values64.end(), compare_int);
    return ctx.values64[0] + ctx.values64[ctx.values64.size()/2] + ctx.values64[ctx.values64.size()-1];
#endif
}


static void do_test(const char* name, size_t num_iterations, size_t num_elements, void (*setupfn)(SCtx& ctx), uint64_t (*testfn)(SCtx& ctx), report_t& results, int verbose )
{
    CTimeIt timeit;
    SCtx ctx;
    ctx.verbose = verbose;
    ctx.num_elements = num_elements;
    uint64_t result = timeit.run<uint64_t>( num_iterations, setupfn, testfn, ctx );

    if( verbose )
        printf("# %s -> %llu\n", name, result);

    STestReport testresult;
    testresult.testname = name;
    testresult.iterations = num_iterations;
    testresult.elements = num_elements;
    testresult.timemin = timeit.fastest();
    testresult.timemax = timeit.longest();
    testresult.timemedian = timeit.median();
    testresult.timeavg = timeit.average();

    ResetMemoryStats();

    timeit.run<uint64_t>( 1, setupfn, testfn, ctx );

    GetMemoryStats(testresult.memory_allocations, testresult.memory_size);

    results.tests.push_back( testresult );

    //printf("# ht size: %zu\n", Size(ctx.ht));
}

void test(size_t reportformat, size_t num_iterations, size_t num_elements, report_t& results, int verbose)
{
    verbose = 1;

    if(verbose)
        printf("# n %zu  it %zu\n", num_elements, num_iterations);

#define TEST( NAME, SETUPFUNC, FUNC ) \
    { \
        do_test((NAME), num_iterations, num_elements, (SETUPFUNC), (FUNC), results, verbose); \
    }

    results.containername = TESTNAME;

    InitMemoryHooks();

    // TEST( "lower_bound", create, lower_bound );
    // TEST( "upper_bound", create, upper_bound );
    TEST( "sort 32", setup_sort, sort32 );
    TEST( "sort 64", setup_sort, sort64 );
    TEST( "stable_sort 32", setup_sort, stable_sort32 );
    TEST( "stable_sort 64", setup_sort, stable_sort64 );
}
