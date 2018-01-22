#include <stdint.h>
#define JC_ARRAY_IMPLEMENTATION
#include <jc/array.h>
#include <vector>
#include "jc_test.h"

typedef struct SCtxArray
{
    std::vector<int> numbers;
    size_t           sum;
} SCtxArray;

template<typename T>
static size_t FillArray(T& a, size_t count)
{
    size_t sum = 0;
    for( uint32_t i = 0; i < count; ++i)
    {
        a[i] = i % 4000;
        sum += a[i];
    }
    return sum;
}

template<typename T>
static size_t Sum(T& a, size_t count)
{
    size_t sum = 0;
    for( uint32_t i = 0; i < count; ++i)
    {
        sum += a[i];
    }
    return sum;
}

static SCtxArray* array_main_setup()
{
    SCtxArray* ctx = new SCtxArray;

    size_t count = 65436 + rand() % 100;
    ctx->numbers.resize(count);
    ctx->sum = FillArray(ctx->numbers, count);
    return ctx;
}

static void array_main_teardown(SCtxArray* ctx)
{
    delete ctx;
}

static void array_test_setup(SCtxArray* ctx)
{
    (void)ctx;
}

static void array_test_teardown(SCtxArray* ctx)
{
    (void)ctx;
}

static void array_create(SCtxArray* ctx)
{
    jc::Array<int> a;
    ASSERT_TRUE(a.Empty());
    ASSERT_TRUE(a.Full());

    a.SetCapacity(ctx->numbers.size());

    ASSERT_EQ(ctx->numbers.size(), a.Capacity());
    ASSERT_EQ(0, a.Size());

    a.SetSize(ctx->numbers.size());
    ASSERT_EQ(ctx->numbers.size(), a.Size());

    size_t sum = FillArray(a, a.Size());
    ASSERT_EQ(ctx->sum, sum);
}


static void array_first_last(SCtxArray*)
{
    jc::Array<int> a;
    a.SetSize(4);
    int* begin = a.Begin();
    begin[0] = 10;
    begin[1] = 20;
    begin[2] = 30;
    begin[3] = 40;
    ASSERT_EQ(10, a.First());
    ASSERT_EQ(40, a.Last());
}

static void array_resize(SCtxArray* ctx)
{
    (void)ctx;

    jc::Array<int> a;
    a.SetSize(32);
    size_t sum = FillArray(a, a.Size());

    int* begin = a.Begin();

    // increase until it has reallocated array
    while( begin == a.Begin() )
    {
        a.SetCapacity(a.Capacity() + 16);
    }
    size_t sum2 = Sum(a, a.Size());
    ASSERT_EQ(sum, sum2);
}

static void array_push(SCtxArray* ctx)
{
    jc::Array<int> a;
    a.SetCapacity(ctx->numbers.size());

    for( uint32_t i = 0; i < a.Capacity(); ++i)
        a.Push(i % 4000);

    ASSERT_EQ(ctx->numbers.size(), a.Size());

    size_t sum = Sum(a, a.Size());
    ASSERT_EQ(ctx->sum, sum);
}

static void array_pop(SCtxArray* ctx)
{
    jc::Array<int> a;
    a.SetSize(ctx->numbers.size());
    FillArray(a, a.Size());

    size_t sum = 0;
    while( !a.Empty() )
        sum += a.Pop();

    ASSERT_EQ(0, a.Size());
    ASSERT_EQ(ctx->sum, sum);
}

template<typename S, typename T>
static bool Compare(const S& a, const T& b, size_t count)
{
    for ( size_t i = 0; i < count; ++i )
    {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

static void array_erase_swap(SCtxArray*)
{
    jc::Array<int> a;
    a.SetSize(4);
    a[0] = 10;
    a[1] = 20;
    a[2] = 30;
    a[3] = 40;

    const int check1[] = { 10, 20, 30, 40 };
    const int check2[] = { 40, 20, 30 };
    const int check3[] = { 40, 30 };
    const int check4[] = { 30 };

    const int* p = check1;
    ASSERT_TRUE(Compare(a, p, a.Size()));

    a.EraseSwap(0);
    p = check2;
    ASSERT_EQ(3, a.Size());
    ASSERT_TRUE(Compare(a, p, a.Size()));
    ASSERT_EQ(p[0], a.First());
    ASSERT_EQ(p[2], a.Last());

    a.EraseSwap(1);
    p = check3;
    ASSERT_EQ(2, a.Size());
    ASSERT_TRUE(Compare(a, p, a.Size()));
    ASSERT_EQ(p[0], a.First());
    ASSERT_EQ(p[1], a.Last());

    a.EraseSwap(0);
    p = check4;
    ASSERT_EQ(1, a.Size());
    ASSERT_TRUE(Compare(a, p, a.Size()));
    ASSERT_EQ(p[0], a.First());
    ASSERT_EQ(p[0], a.Last());

    a.EraseSwap(0);
    ASSERT_EQ(0, a.Size());
}

TEST_BEGIN(array_test, array_main_setup, array_main_teardown, array_test_setup, array_test_teardown)
    TEST(array_create)
    TEST(array_first_last)
    TEST(array_resize)
    TEST(array_push)
    TEST(array_pop)
    TEST(array_erase_swap)
TEST_END(array_test)
