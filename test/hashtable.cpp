#include "jc_test.h"
#include "hashtable.h"
//#include "dmhashtable.h"

#include <stdlib.h>

//https://attractivechaos.wordpress.com/2008/10/07/another-look-at-my-old-benchmark/

// tables to test
// EASTL: hash_map.h, fixed_hash_map.h
// STL: map, unordered_map
// Foundation: hashmap.h, hashtable.h   https://github.com/rampantpixels/foundation_lib
// ..//ProDBG/src/external/bgfx/3rdparty/glsl-optimizer/src/util/hash_table.h
// ..//ProDBG/src/external/foundation_lib/foundation/hashtable.h
// Bullet: bullet-2.82-r2704/src/LinearMath/btHashMap.h
// boost: hash_map, flat_map
// khash

const uint32_t STRESS_COUNT = 2000000;
const uint32_t PERCENT = 99;


#include <map>
#include <unordered_map>

struct SPod
{
	int a;
	int b;
	
	bool operator== (const SPod& rhs) const
	{
		return memcmp(this, &rhs, sizeof(SPod)) == 0;
	}
};

typedef jc::HashTable<uint64_t, SPod> TestHT64;

typedef struct SCtx
{
	uint32_t 	count;
	uint32_t 	memorysize;
	void* 		memory;
	TestHT64	ht;
} SCtx;

static SCtx* hashtable_main_setup()
{
	return reinterpret_cast<SCtx*>( malloc( sizeof(SCtx) ) );
}

static void hashtable_main_teardown(SCtx* ctx)
{
	free(ctx);
}

static void test_setup(SCtx* ctx)
{
	ctx->count = 10;
	ctx->memorysize = TestHT64::CalcSize(1023, ctx->count);
	ctx->memory = malloc( ctx->memorysize );
	ctx->ht.Create(1023, ctx->count, ctx->memory);
}

static void test_teardown(SCtx* ctx)
{
	free(ctx->memory);
}

static void hashtable_create(SCtx* ctx)
{
	TestHT64 ht(ctx->count, ctx->memorysize, ctx->memory);
	
	ASSERT_TRUE( ht.Empty() );
	
	ctx->ht.Create(1023, ctx->count, ctx->memory);

	ASSERT_TRUE( ctx->ht.Empty() );
}

static void hashtable_insert_remove(SCtx* ctx)
{
	TestHT64& ht = ctx->ht;

	ASSERT_TRUE( ht.Empty() );
	ASSERT_EQ( 0, ht.Size() );
	
	for( uint32_t i = 0; i < ctx->count; ++i )
	{
		SPod v = { 1, 2 };
		ht.Put( 1234, v );
		
		ASSERT_EQ( 1, ht.Size() );
		
		ASSERT_TRUE( ht.Exists(1234) );
		
		const SPod* value = ht.Get(1234);
		ASSERT_TRUE( value != 0 );
		ASSERT_EQ( v, *value );

		ht.Erase(666);
		ASSERT_EQ( 1, ht.Size() );

		ht.Erase(1234);
		
		ASSERT_TRUE( ht.Empty() );
		ASSERT_EQ( 0, ht.Size() );
	}
	
	// Reinsert it
	SPod v2 = { 2, 3 };
	ht.Put( 1234, v2 );
	ASSERT_EQ( 1, ht.Size() );
	ASSERT_TRUE( ht.Exists(1234) );
	const SPod* value = ht.Get(1234);
	ASSERT_TRUE( value != 0 );
	ASSERT_EQ( v2, *value );
	
	// Change it
	SPod v3 = { 3, 4 };
	ASSERT_EQ( 1, ht.Size() );
	ht.Put( 1234, v3 );
	ASSERT_EQ( 1, ht.Size() );
	value = ht.Get(1234);
	ASSERT_TRUE( value != 0 );
	ASSERT_EQ( v3, *value );

}

static void hashtable_iterate(SCtx* ctx)
{
	(void)ctx;
	/*
	TestHT64& ht = ctx->ht;

	ASSERT_TRUE( ht.Empty() );
	ASSERT_EQ( 0, ht.Size() );
	
	SPod v = { 1, 2 };
	ht.Put( 1234, v );

	TestHT64iterator it = ht.begin();
	
	const std::pair<uint64_t, SPod>& p = *it;
	ASSERT_EQ( 1234, p.first );
	ASSERT_EQ( v, p.second );
	
	TestHT64iterator itend = ht.end();
	const std::pair<uint64_t, SPod>& pend = *itend;
	ASSERT_EQ( 0u, pend.first );
	*/
	
	uint32_t count = 200;
	uint32_t memorysize = TestHT64::CalcSize(1023, count);
	void* memory = malloc( memorysize );
	
	TestHT64 ht2;
	ht2.Create(1023, count, memory);
	
	srand(0);
	
	std::map<uint64_t, SPod> comparison;
	
	// insert
	for( uint32_t i = 0; i < count; ++i )
	{
		uint64_t key = static_cast<uint64_t>( rand() );
		int v1 = rand();
		int v2 = rand();
		SPod pod = {v1, v2};

		ht2.Put( key, pod );
		
		comparison[key] = pod;
	}
	ASSERT_EQ( count, ht2.Size() );

	/*
	TestHT64iterator it = ht2.begin();
	TestHT64iterator itend = ht2.end();
	for( ; it != itend; ++it )
	{
		const std::pair<uint64_t, SPod>& pp = *it;
		
		std::map<uint64_t, SPod>::const_iterator compit = comparison.find(pp.first);
		ASSERT_TRUE( compit != comparison.end() );
		ASSERT_EQ( compit->first, pp.first );
		ASSERT_EQ( compit->second, pp.second );
	}*/
	
	//ht2.Dump();
	
	free(memory);
}

static void hashtable_stress(SCtx* ctx)
{
	(void)ctx;
	uint32_t count = 10;
	uint32_t table_size = count / 3;
	uint32_t capacity = count;
	uint32_t memorysize = TestHT64::CalcSize(table_size, capacity);
	void* memory = malloc( memorysize );
	
	TestHT64 ht;
	ht.Create(table_size, capacity, memory);
	
	srand(0);
	
	std::map<uint64_t, SPod> comparison;
	
	// insert
	for( uint32_t i = 0; i < (count*PERCENT)/100; ++i )
	{
		uint32_t key = static_cast<uint32_t>( rand() );
		int v1 = rand();
		int v2 = rand();
		SPod pod = {v1, v2};

		ht.Put( static_cast<uint64_t>(key), pod );
		
		comparison[key] = pod;
		
		//printf("PUT Key %d: %u\n", i, key);
	}
	ASSERT_EQ( (count*PERCENT)/100, ht.Size() );

	TestHT64::Iterator testit = ht.Begin();
	
	//printf("\ntest\n");
	
	TestHT64::Iterator testitend = ht.End();
	for( ; testit != testitend; ++testit )
	{
		uint64_t key = *testit.GetKey();
		//printf("Key: %u\n", key);
		
		std::map<uint64_t, SPod>::const_iterator compit = comparison.find(key);
		ASSERT_TRUE( compit != comparison.end() );
		ASSERT_EQ( compit->first, *testit.GetKey() );
		ASSERT_EQ( compit->second, *testit.GetValue() );
	}


	std::map<uint64_t, SPod>::const_iterator it = comparison.begin();
	for( ; it != comparison.end(); ++it )
	{
		const uint64_t key = it->first;
		const SPod& p = it->second;
		
		const SPod* value = ht.Get(key);
		ASSERT_TRUE( value != 0 );
		ASSERT_EQ( p, *value );

		ht.Erase(key);
	}

	ASSERT_EQ( 0, ht.Size() );
	
	free(memory);
}

static void hashtable_insert_speed(SCtx* ctx)
{
	(void)ctx;
	uint32_t count = STRESS_COUNT;
	uint32_t table_size = count / 3;
	uint32_t capacity = count;
	uint32_t memorysize = TestHT64::CalcSize(table_size, capacity);
	void* memory = malloc( memorysize );
	
	TestHT64 ht;
	ht.Create(table_size, capacity, memory);
	
	srand(0);
	
	// insert
	for( uint32_t i = 0; i < (count*PERCENT)/100; ++i )
	{
		uint32_t key = static_cast<uint32_t>( rand() );
		int v1 = rand();
		int v2 = rand();
		SPod pod = {v1, v2};

		ht.Put( static_cast<uint64_t>(key), pod );
	}
	ASSERT_EQ( (count*PERCENT)/100, ht.Size() );
}

static void hashtable_iterate_bug(SCtx* ctx)
{
	(void)ctx;
	uint32_t count = 50000;
	uint32_t table_size = count;
	uint32_t capacity = count;
	uint32_t memorysize = TestHT64::CalcSize(table_size, capacity);
	void* memory = malloc( memorysize );
	
	TestHT64 ht;
	ht.Create(table_size, capacity, memory);
	
	srand(0);
	
	size_t checksum = 0;
	// insert
	for( uint32_t i = 0; i < count; ++i )
	{
		uint32_t key = static_cast<uint32_t>( rand() );
		SPod pod = {static_cast<int>( i ), 0};
		checksum += i;

		ht.Put( static_cast<uint64_t>(key), pod );
	}
	
	ASSERT_EQ( count, ht.Size() );

	size_t sum = 0;
	TestHT64::Iterator testit = ht.Begin();
	TestHT64::Iterator testitend = ht.End();
	for( ; testit != testitend; ++testit )
	{
		sum += static_cast<size_t>( testit.GetValue()->a );
	}
	ASSERT_EQ( checksum, sum );
}

struct SKeyType
{
	uint32_t value;
	SKeyType(uint32_t _value) : value(_value) {}
	uint32_t operator% (uint32_t mod) const { return value % mod; }
	uint32_t operator== (const SKeyType& rhs) const { return value == rhs.value; }
};

static void hashtable_custom_key(SCtx*)
{	
	uint32_t count = 100;
	uint32_t table_size = count / 3;
	uint32_t capacity = count;
	uint32_t memorysize = jc::HashTable<SKeyType, SPod>::CalcSize(table_size, capacity);
	void* memory = malloc( memorysize );

	jc::HashTable<SKeyType, SPod> ht;	
	ht.Create(table_size, capacity, memory);
	
	SPod pod = {3, 4};
	
	SKeyType key(17);
	
	ht.Put( key, pod );

	ASSERT_EQ( 1, ht.Size() );
	ASSERT_EQ( pod, *ht.Get(key) );
}

/*
static void hashtable_insert_speed_stl_map(SCtx*)
{
	size_t count = STRESS_COUNT;
	
	srand(0);
	
	std::map<uint64_t, SPod> comparison;
	
	// insert
	for( size_t i = 0; i < (count*PERCENT)/100; ++i )
	{
		int key = rand();
		int v1 = rand();
		int v2 = rand();
		SPod pod = {v1, v2};
		
		comparison[static_cast<uint32_t>(key)] = pod;
	}
	ASSERT_EQ( (count*PERCENT)/100, comparison.size() );
}

static void hashtable_insert_speed_stl_unordered_map(SCtx*)
{
	size_t count = STRESS_COUNT;
	
	srand(0);
	
	std::unordered_map<uint64_t, SPod> comparison;
	
	// insert
	for( size_t i = 0; i < (count*PERCENT)/100; ++i )
	{
		int key = rand();
		int v1 = rand();
		int v2 = rand();
		SPod pod = {v1, v2};
		
		comparison.insert( comparison.end(), std::make_pair(static_cast<uint32_t>(key), pod));
	}
	ASSERT_EQ( (count*PERCENT)/100, comparison.size() );
}

static void hashtable_insert_speed_dmhashtable(SCtx*)
{
	uint32_t count = STRESS_COUNT;
	
	srand(0);
	
	uint32_t table_size = count / 3;
	uint32_t capacity = count;
	size_t memorysize = dmHashTable<uint64_t, SPod>::CalcSize(table_size, capacity);
	void* mem = malloc(memorysize);
	dmHashTable<uint64_t, SPod> comparison(mem, table_size, capacity);
	
	// insert
	for( size_t i = 0; i < (count*PERCENT)/100; ++i )
	{
		int key = rand();
		int v1 = rand();
		int v2 = rand();
		SPod pod = {v1, v2};
		
		comparison.Put( static_cast<uint32_t>(key), pod);
	}
	ASSERT_EQ( (count*PERCENT)/100, comparison.Size() );
	
	free(mem);
}*/

TEST_BEGIN(hashtable_test, hashtable_main_setup, hashtable_main_teardown, test_setup, test_teardown)
    TEST(hashtable_create)
    TEST(hashtable_insert_remove)
    TEST(hashtable_iterate)
    TEST(hashtable_stress)
	//TEST(hashtable_custom_key)
	//TEST(hashtable_insert_speed)
	//TEST(hashtable_iterate_bug)
TEST_END(hashtable_test)

