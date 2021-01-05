
#include "jc_test.h"
#include <jc/hashtable.h>

#include <stdlib.h>

const uint32_t STRESS_COUNT = 2000000;
const uint32_t PERCENT = 85;

#include <map>

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

class HashTableTest : public jc_test_base_class
{
protected:
    virtual ~HashTableTest();
    void SetUp() {
        htcount = 10;
        memorysize = TestHT64::CalcSize(htcount);
        memory = malloc( memorysize );
        ht.Create(htcount, memory);
    }
    void TearDown() {
        free(memory);
    }
    uint32_t    htcount;
    uint32_t    memorysize;
    void*       memory;
    TestHT64    ht;
};

HashTableTest::~HashTableTest() {}

TEST_F(HashTableTest, Create)
{
	TestHT64 ht(htcount, memory);

	ASSERT_TRUE( ht.Empty() );

	ht.Create(htcount, memory);

	ASSERT_TRUE( ht.Empty() );
}

TEST_F(HashTableTest, InsertRemove)
{
	ASSERT_TRUE( ht.Empty() );
	ASSERT_EQ( 0u, ht.Size() );

	for( uint32_t i = 0; i < htcount; ++i )
	{
		SPod v = { 1, 2 };
		ht.Put( 1234, v );

		ASSERT_EQ(1u, ht.Size());

		SPod* value = ht.Get(1234);
        ASSERT_TRUE( value != 0 );
        ASSERT_EQ( v, *value );

		const SPod* constvalue = const_cast<const TestHT64&>(ht).Get(1234);
		ASSERT_TRUE( constvalue != 0 );
		ASSERT_EQ( v, *constvalue );

		ht.Erase(1234);

		ASSERT_TRUE( ht.Empty() );
		ASSERT_EQ(0u, ht.Size());
	}

	// Reinsert it
	SPod v2 = { 2, 3 };
	ht.Put( 1234, v2 );
	ASSERT_EQ( 1u, ht.Size() );
	const SPod* value = ht.Get(1234);
	ASSERT_TRUE( value != 0 );
	ASSERT_EQ( v2, *value );

	// Change it
	SPod v3 = { 3, 4 };
	ASSERT_EQ( 1u, ht.Size() );
	ht.Put( 1234, v3 );
	ASSERT_EQ( 1u, ht.Size() );
	value = ht.Get(1234);
	ASSERT_TRUE( value != 0 );
	ASSERT_EQ( v3, *value );

}

TEST_F(HashTableTest, Iterate)
{
	uint32_t count = 200;
	uint32_t memorysize = TestHT64::CalcSize(count);
	void* memory = malloc( memorysize );

	TestHT64 ht2;
	ht2.Create(count, memory);

	srand(0);

	std::map<uint64_t, SPod> comparison;

	// insert
	for( uint32_t i = 0; i < count; ++i )
	{
		uint64_t key = count - i;
		int v1 = rand();
		int v2 = rand();
		SPod pod = {v1, v2};

		ht2.Put( key, pod );

		comparison[key] = pod;
	}
	ASSERT_EQ( count, ht2.Size() );

	TestHT64::Iterator it = ht2.Begin();
	TestHT64::Iterator itend = ht2.End();
	for( ; it != itend; ++it )
	{
		const uint64_t* key = it.GetKey();
		const SPod* value = it.GetValue();

		std::map<uint64_t, SPod>::const_iterator compit = comparison.find(*key);
		ASSERT_TRUE( compit != comparison.end() );
		ASSERT_EQ( compit->first, *key );
		ASSERT_EQ( compit->second, *value );
	}

	ht2.Clear();

	int numelements = 0;
    it = ht2.Begin();
    itend = ht2.End();
    for( ; it != itend; ++it )
    {
        ++numelements;
    }
    ASSERT_EQ( 0, numelements );

	free(memory);
}

TEST_F(HashTableTest, Stress)
{
	uint32_t count = 10;
	uint32_t capacity = count;
	uint32_t memorysize = TestHT64::CalcSize(capacity);
	void* memory = malloc( memorysize );

	TestHT64 ht;
	ht.Create(capacity, memory);

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
	}
	ASSERT_EQ( (count*PERCENT)/100u, ht.Size() );

	TestHT64::Iterator testit = ht.Begin();
	TestHT64::Iterator testitend = ht.End();
	for( ; testit != testitend; ++testit )
	{
		uint64_t key = *testit.GetKey();

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

	ASSERT_EQ( 0u, ht.Size() );

	free(memory);
}

TEST_F(HashTableTest, Small)
{
    for( uint32_t i = 0; i < htcount; ++i )
    {
        TestHT64 ht(i, memory);

        ASSERT_TRUE( ht.Empty() );

        for( uint32_t j = 0; j < i; ++j )
        {
            SPod pod = { static_cast<int>(j), static_cast<int>(j*2+10) };
            ht.Put(j, pod);
        }

        ASSERT_EQ( i, ht.Size() );

        for( uint32_t j = 0; j < i; ++j )
        {
            ht.Erase(j);
        }

        ASSERT_EQ( 0u, ht.Size() );

        uint32_t numelements = 0;

        TestHT64::Iterator testit = ht.Begin();
        TestHT64::Iterator testitend = ht.End();
        for( ; testit != testitend; ++testit )
        {
            ++numelements;
        }

        ASSERT_EQ( 0u, numelements );
    }
}


TEST_F(HashTableTest, AddRemoveAdd)
{
	const uint32_t N = 20;
	uint32_t memorysize = jc::HashTable<uint32_t, uint32_t>::CalcSize(N);

	void* memory = malloc( memorysize );

    for( uint32_t i = 0; i < N; ++i )
    {
       	memset(memory, 0xcd, memorysize);

        jc::HashTable<uint32_t, uint32_t> ht( i, memory );
        std::map<uint32_t, uint32_t> refmap;

        ASSERT_TRUE( ht.Empty() );

        for( uint32_t j = 0; j < i; ++j )
        {
            uint32_t key = static_cast<uint32_t>( rand() & 0x3ff ); // keys up to 1023...
            uint32_t val = static_cast<uint32_t>( rand() );
            ht.Put(key, val);
            refmap[key] = val;
        }

        ASSERT_EQ( refmap.size(), ht.Size() );

        std::map<uint32_t, uint32_t>::iterator refit = refmap.begin();
        std::map<uint32_t, uint32_t>::iterator refitend = refmap.end();
        for( ; refit != refitend; ++refit )
        {
        	uint32_t key = refit->first;
        	ASSERT_NE( reinterpret_cast<uint32_t*>(0), ht.Get(key));
        	ASSERT_EQ( refit->second, *ht.Get(key));
        	ht.Erase(key);
        }

        refmap.clear();

		// fill again, but only half the size
		for( uint32_t j = 0; j < i / 2; ++j )
        {
            uint32_t key = static_cast<uint32_t>( rand() & 0x3ff ); // keys up to 1023...
            uint32_t val = static_cast<uint32_t>( rand() );
            ht.Put(key, val);
            refmap[key] = val;
        }

        ASSERT_EQ( refmap.size(), ht.Size() );

        // Compare again
        refit = refmap.begin();
        refitend = refmap.end();
        for( ; refit != refitend; ++refit )
        {
        	uint32_t key = refit->first;
        	ASSERT_NE( reinterpret_cast<uint32_t*>(0), ht.Get(key));
        	ASSERT_EQ( refit->second, *ht.Get(key));
        	ht.Erase(key);
        }
    }

    free(memory);
}

TEST_F(HashTableTest, AddRemoveAdd2)
{
	const uint32_t N = 20;

	uint32_t memorysize = jc::HashTable<uint32_t, uint32_t>::CalcSize(N*3);

	void* memory = malloc( memorysize );

    for (uint32_t count = 1; count < N; ++count)
    {
        for (uint32_t table_size = 1; table_size <= 2*N; ++table_size)
        {
       		memset(memory, 0xcd, memorysize);

            std::map<uint32_t, uint32_t> map;
            jc::HashTable<uint32_t, uint32_t> ht( table_size > count ? table_size : count, memory );

            const uint32_t grow_shrink_iter_count = 20;
            for (uint32_t grow_shrink_iter = 0; grow_shrink_iter < grow_shrink_iter_count; ++grow_shrink_iter)
            {
                uint32_t target_size = uint32_t(rand()) % (count + 1);

                if (grow_shrink_iter == grow_shrink_iter_count/2)
                {
                    // Fill completely
                    target_size = count;
                }

                while (map.size() != target_size)
                {
                    if (map.size() < target_size)
                    {
                        uint32_t key = uint32_t(rand() & 0x3ff); // keys up to 1023...
                        uint32_t val = uint32_t(rand());

                        map[key] = val;
                        ht.Put(key, val);
                    }
                    else
                    {
                        uint32_t key = map.begin()->first;
                        map.erase(map.begin());
                        ht.Erase(key);
                    }

                    ASSERT_EQ(map.size(), ht.Size());
                }

                ASSERT_EQ(map.size(), ht.Size());
                ASSERT_EQ(target_size, ht.Size());
            }
            // Compare
            std::map<uint32_t, uint32_t>::iterator iter;
            for( iter = map.begin(); iter != map.end(); ++iter)
            {
                uint32_t key = iter->first;
                ASSERT_NE(uintptr_t(0), uintptr_t(ht.Get(key)));
                ASSERT_EQ(iter->second, *ht.Get(key));
            }
        }
    }

    free(memory);
}


TEST_F(HashTableTest, Bug_Erase)
{
	uint32_t memorysize = jc::HashTable<uint64_t, uint64_t>::CalcSize(16);
	void* memory = malloc( memorysize );
	memset(memory, 0xcd, memorysize);

    jc::HashTable<uint64_t, uint64_t> ht( 16, memory );

    ht.Put( 2061551824, 5271368961445147204 );
    ht.Put( 2061548576, 7242849836242914266 );
    ht.Put( 2081443888, 6574279858954154594 );

	uint64_t key = 2061548576;
    //printf("\nerase  %llu\n\n", key);

    ht.Erase( key );

	key = 2081443888;
    //printf("\nerase  %llu\n\n", key);

    ht.Erase( key );

    free(memory);
}
