#include "defines.h"
#include "../timeit.h"
#include "../report.h"
#include "../memory.h"

#include <assert.h>
#include <stdlib.h>     // srand, rand
#include <chrono>

//#define ASSERT(_X_)		assert(_X_)
#define ASSERT(_X_)

struct SCtx
{
	int 				verbose;
	size_t 				num_elements;
	std::vector<keey_t> keys;			// for using when accessing elements in the test container
	std::vector<keey_t> randomkeys;		// for using when accessing elements in the test container
	std::vector<bool> 	exists;			// for using when accessing elements in the test container
	uint64_t			sum; 			// sum of all products key*value
	hashtable_t			ht;
};

void nop(SCtx& ctx)
{

}

uint64_t nostuff(SCtx& ctx)
{
    return 0;
}


void setup_random(SCtx& ctx)
{
    srand(0);
    ctx.sum = 0;
    ctx.keys.clear();
    ctx.keys.resize(ctx.num_elements);
    ctx.randomkeys.clear();
    ctx.randomkeys.resize(ctx.num_elements);
    ctx.exists.clear();
    ctx.exists.resize(ctx.num_elements);

    for( size_t i = 0; i < ctx.num_elements; ++i )
    {
        keey_t key = rand();
        while( Exists(ctx.ht, key ) )
        {
            key = rand();
        }
        Put(ctx.ht, key, value_t(i+1) );
        ctx.keys[i] = key;
        ctx.randomkeys[i] = key;
        ctx.exists[i] = true;
        ctx.sum += key * (i+1);
    }
}

void create_sequential_table(SCtx& ctx)
{
	Init( ctx.ht, ctx.num_elements );

	ctx.sum = 0;
	ctx.keys.clear();
	ctx.keys.resize(ctx.num_elements);
	ctx.randomkeys.clear();
	ctx.randomkeys.resize(ctx.num_elements);
	ctx.exists.clear();
	ctx.exists.resize(ctx.num_elements);

	for( size_t i = 0; i < ctx.num_elements; ++i )
	{
		keey_t key = i;
		Put(ctx.ht, key, value_t( i+1 ) );
		ctx.keys[i] = key;
		ctx.randomkeys[i] = key;
		ctx.exists[i] = true;
		ctx.sum += key * (i+1);
	}

	ASSERT( Size(ctx.ht) == ctx.num_elements );
}


void create_random_table(SCtx& ctx)
{
	Init( ctx.ht, ctx.num_elements );

	setup_random(ctx);

	ASSERT( Size(ctx.ht) == ctx.num_elements );

	std::random_shuffle( ctx.randomkeys.begin(), ctx.randomkeys.end() );
}


void clear(SCtx& ctx)
{
	Init( ctx.ht, ctx.num_elements );

	setup_random(ctx);
	Clear( ctx.ht );
}



#if defined(IMPL_DM_HASHTABLE)
static inline void sum_callback(uint64_t* context, const keey_t* key, value_t* value )
{
	(void)key;
	#ifdef BIG_VALUE
		*context += value->value;
	#else
		*context += *value;
	#endif
}
#endif


uint64_t create_insert_and_sum(SCtx& ctx)
{
	hashtable_t ht;
	Init(ht, ctx.num_elements);
	for( size_t i = 0; i < ctx.num_elements; ++i )
		Put(ht, keey_t( i ), value_t( i ) );

	uint64_t sum = 0;
#if defined(IMPL_DM_HASHTABLE)
	ht.Iterate(sum_callback, &sum);
#else
	auto it = IteratorBegin(ht);
	auto itend = IteratorEnd(ht);
	for( ; it != itend; IteratorNext(ht, it) )
		sum += IteratorGetValue(ht, it);
#endif
	return sum;
}

void create_insert(SCtx& ctx)
{
	Init(ctx.ht, ctx.num_elements);

	for( size_t i = 0; i < ctx.num_elements; ++i )
		Put(ctx.ht, keey_t( i ), value_t( i ) );
}

uint64_t sum(SCtx& ctx)
{
	uint64_t sum = 0;
#if defined(IMPL_DM_HASHTABLE)
	ctx.ht.Iterate(sum_callback, &sum);
#else
	auto it = IteratorBegin(ctx.ht);
	auto itend = IteratorEnd(ctx.ht);
	for( ; it != itend; IteratorNext(ctx.ht, it) )
		sum += IteratorGetValue(ctx.ht, it);
#endif
	return sum;
}


uint64_t create_table(SCtx& ctx)
{
	hashtable_t ht;
	Init(ht, ctx.num_elements);
	return Size(ht);
}

uint64_t insert_sequential(SCtx& ctx)
{
	for( size_t i = 0; i < ctx.num_elements; ++i )
		Put(ctx.ht, keey_t( i ), value_t( i ) );

	ASSERT( Size(ctx.ht) == ctx.num_elements );
	return 0;
}

uint64_t insert_random(SCtx& ctx)
{
	srand(0);
	for( size_t i = 0; i < ctx.num_elements; ++i )
		Put(ctx.ht, ctx.randomkeys[i], value_t( i ) );

	ASSERT( Size(ctx.ht) == ctx.num_elements );
	return 0;
}

uint64_t iterator_prefix(SCtx& ctx)
{
	ASSERT( Size(ctx.ht) == ctx.num_elements );
	uint64_t sum = 0;
#if defined(IMPL_DM_HASHTABLE)
	ctx.ht.Iterate(sum_callback, &sum);
#else
	iterator_t it = IteratorBegin(ctx.ht);
	iterator_t itend = IteratorEnd(ctx.ht);
	for( ; it != itend; IteratorNext(ctx.ht, it) )
		sum += IteratorGetValue(ctx.ht, it);
#endif
	return sum;
}

uint64_t get_sequential(SCtx& ctx)
{
	uint64_t sum = 0;
	for( size_t i = 0; i < ctx.num_elements; ++i )
	{
		keey_t key = keey_t( ctx.keys[i] );
		sum += key * Get( ctx.ht, key );
	}

	ASSERT( Size(ctx.ht) == ctx.num_elements );
	ASSERT( sum == ctx.sum );
	return (size_t)sum;
}


uint64_t get_random(SCtx& ctx)
{
	uint64_t sum = 0;
	for( size_t i = 0; i < ctx.num_elements; ++i )
	{
		keey_t key = ctx.randomkeys[i];
		sum += key * Get( ctx.ht, key );
	}

	ASSERT( Size(ctx.ht) == ctx.num_elements );
	ASSERT( sum == ctx.sum );
	return sum;
}

uint64_t erase_sequential(SCtx& ctx)
{
	ASSERT( Size(ctx.ht) == ctx.num_elements );
	for( size_t i = 0; i < ctx.num_elements; ++i )
	{
		Erase(ctx.ht, ctx.keys[i] );
	}
	ASSERT( Empty(ctx.ht) );
	return 0;
}

uint64_t erase_random(SCtx& ctx)
{
	ASSERT( Size(ctx.ht) == ctx.num_elements );
	for( size_t i = 0; i < ctx.num_elements; ++i )
		Erase(ctx.ht, ctx.randomkeys[i] );
	ASSERT( Empty(ctx.ht) );
	return 0;
}

uint64_t adds_and_removes(SCtx& ctx)
{
	uint32_t percent = 30;
	uint32_t percent_lower = 50;
	uint32_t num_to_keep = (ctx.num_elements * percent_lower) / 100;
	uint32_t num_to_addremove = (ctx.num_elements * percent) / 100;
	if( num_to_addremove == 0 )
		num_to_addremove = 1;
	if( num_to_keep + num_to_addremove > ctx.num_elements )
		num_to_keep = ctx.num_elements - num_to_addremove;
	for(uint32_t i = 0; i < 100; ++i )
	{
		if( i & 1 )
		{
			// add
			uint32_t num_to_add = rand() % num_to_addremove;
			if( Size(ctx.ht) + num_to_add > ctx.num_elements )
				num_to_add = ctx.num_elements - Size(ctx.ht);

			for( size_t i = 0; i < num_to_add; ++i )
			{
				keey_t index = rand() % ctx.num_elements;
				Put(ctx.ht, ctx.randomkeys[ index ], value_t(i) );
				ctx.exists[index] = true;
			}
		}
		else
		{
			// remove
			uint32_t num_to_remove = rand() % num_to_addremove;
			if( Size(ctx.ht) - num_to_remove < num_to_keep )
				num_to_remove = Size(ctx.ht) - num_to_keep;

			for( size_t i = 0; i < num_to_remove; ++i )
			{
				keey_t index = rand() % ctx.num_elements;
				if( ctx.exists[index] )
				{
					Erase(ctx.ht, ctx.randomkeys[ index ] );
					ctx.exists[index] = false;
				}
			}
		}
	}
	return 0;
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

	printf("# ht size: %zu\n", Size(ctx.ht));
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

	TEST( "insert_sequential", clear, insert_sequential );
	TEST( "insert_random", clear, insert_random );
	TEST( "get_sequential", create_sequential_table, get_sequential );
	TEST( "get_random", create_random_table, get_random );
	TEST( "erase_sequential", create_sequential_table, erase_sequential );
	TEST( "erase_random", create_random_table, erase_random );
	TEST( "iterator", create_random_table, iterator_prefix );
	TEST( "create_insert_sum", nop, create_insert_and_sum );
	TEST( "adds_and_removes", create_random_table, adds_and_removes );
}
