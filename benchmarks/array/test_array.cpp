
#include "defines.h"
#include "../report.h"
#include "../memory.h"
#include <stdlib.h>

struct SCtx
{
    int                     verbose;
    size_t                  num_elements;
    container_valuesmall_t  smallvalues;
    container_valuelarge_t  largevalues;
    uint64_t                sum;            // sum of all small values

#if defined(IMPL_C)
    SCtx() : smallvalues(0), largevalues(0)
    {

    }
    ~SCtx()
    {
        if(smallvalues)
            free(smallvalues);
        if(largevalues)
            free(largevalues);
    }
#endif
};

static void clear(SCtx& ctx)
{
    srand(0);
#if defined(IMPL_C)
    ctx.smallvalues = (container_valuesmall_t)malloc(sizeof(valuesmall_t)*ctx.num_elements);
    ctx.largevalues = (container_valuelarge_t)malloc(sizeof(valuelarge_t)*ctx.num_elements);
#else
    SET_CAPACITY(ctx.smallvalues, ctx.num_elements);
    SET_CAPACITY(ctx.largevalues, ctx.num_elements);
    SET_SIZE(ctx.smallvalues, 0);
    SET_SIZE(ctx.largevalues, 0);
#endif
}

static void setup_random(SCtx& ctx)
{
    srand(0);
#if defined(IMPL_C)
    ctx.smallvalues = (container_valuesmall_t)malloc(sizeof(valuesmall_t)*ctx.num_elements);
    ctx.largevalues = (container_valuelarge_t)malloc(sizeof(valuelarge_t)*ctx.num_elements);
#else
    SET_SIZE(ctx.smallvalues, ctx.num_elements);
    SET_SIZE(ctx.largevalues, ctx.num_elements);
#endif
    for( size_t i = 0; i < ctx.num_elements; ++i )
    {
        ctx.smallvalues[i] = rand();
        ctx.largevalues[i].i1 = ctx.smallvalues[i];
        ctx.largevalues[i].i2 = ctx.smallvalues[i]*2;
        ctx.largevalues[i].i3 = ctx.smallvalues[i]*3;
    }
}

static uint64_t get_random(SCtx& ctx)
{
    srand(0);
    uint64_t sum = 0;
    for( size_t i = 0; i < ctx.num_elements; ++i )
        sum += ctx.smallvalues[rand()%ctx.num_elements];
    return sum;
}

static uint64_t get_random_large(SCtx& ctx)
{
    srand(0);
    uint64_t sum = 0;
    for( size_t i = 0; i < ctx.num_elements; ++i )
    {
        const valuelarge_t& value = ctx.largevalues[rand()%ctx.num_elements];
        sum += value.i3;
    }
    return sum;
}

static uint64_t sum(SCtx& ctx)
{
    uint64_t sum = 0;
    for( size_t i = 0; i < ctx.num_elements; ++i )
    {
        sum += ctx.smallvalues[i];
    }
    return sum;
}

static uint64_t push_back(SCtx& ctx)
{
    uint64_t sum = 0;
    for( size_t i = 0; i < ctx.num_elements; ++i )
    {
#if defined(IMPL_C)
        ctx.smallvalues[i] = i;
#else
        PUSH(ctx.smallvalues, i);
#endif
        sum += ctx.smallvalues[i];
    }
    return sum;
}

static void do_test(const char* name, size_t num_iterations, size_t num_elements, void (*setupfn)(SCtx& ctx), uint64_t (*testfn)(SCtx& ctx), report_t& results, int verbose )
{
    CTimeIt timeit;
    SCtx ctx;
    ctx.verbose = verbose;
    ctx.num_elements = num_elements;
    uint64_t result = timeit.run<uint64_t>( num_iterations, setupfn, testfn, ctx );

    if( verbose )
    {
        printf("# %s -> %llu\n", name, result);
    }

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
}

void test(size_t reportformat, size_t num_iterations, size_t num_elements, report_t& results, int verbose)
{
    verbose = 1;

    printf("# n %zu  it %zu\n", num_elements, num_iterations);

#define TEST( NAME, SETUPFUNC, FUNC ) \
    { \
        do_test((NAME), num_iterations, num_elements, (SETUPFUNC), (FUNC), results, verbose); \
    }

    results.containername = CONTAINERNAME;

    InitMemoryHooks();

    TEST("get_random_small", setup_random, get_random);
    TEST("get_random_large", setup_random, get_random_large);
    TEST("sum", setup_random, sum);
    TEST("push_back", clear, push_back);
}
