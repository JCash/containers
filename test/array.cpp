#include <stdint.h>
#include <jc/array.h>
#include <vector>
#define JC_TEST_USE_DEFAULT_MAIN
#include "jc_test.h"

template<typename T>
static int FillArray(T& a, size_t count)
{
    int sum = 0;
    for( uint32_t i = 0; i < count; ++i)
    {
        a[i] = i % 4000;
        sum += a[i];
    }
    return sum;
}

template<typename T>
static int Sum(T& a, size_t count)
{
    int sum = 0;
    for( uint32_t i = 0; i < count; ++i)
    {
        sum += a[i];
    }
    return sum;
}

class ArrayTest : public jc_test_base_class
{
protected:
    ArrayTest() {}
    virtual ~ArrayTest();
    void SetUp()
    {
        size_t count = 65436 + rand() % 100;
        numbers.resize(count);
        sum = FillArray(numbers, count);
    }

    std::vector<int> numbers;
    int              sum;
    int              _pad;
};

ArrayTest::~ArrayTest() {}


TEST_F(ArrayTest, Create)
{
    jc::Array<int> a;
    ASSERT_TRUE(a.Empty());
    ASSERT_TRUE(a.Full());

    a.SetCapacity(numbers.size());

    ASSERT_EQ(numbers.size(), a.Capacity());
    ASSERT_EQ(0u, a.Size());

    a.SetSize(numbers.size());
    ASSERT_EQ(numbers.size(), a.Size());

    int asum = FillArray(a, a.Size());
    ASSERT_EQ(sum, asum);
}


TEST_F(ArrayTest, FirstLast)
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

TEST_F(ArrayTest, Resize)
{
    jc::Array<int> a;
    a.SetSize(32);
    int sum1 = FillArray(a, a.Size());

    int* begin = a.Begin();

    // increase until it has reallocated array
    while( begin == a.Begin() )
    {
        a.SetCapacity(a.Capacity() + 16);
    }
    int sum2 = Sum(a, a.Size());
    ASSERT_EQ(sum1, sum2);
}

TEST_F(ArrayTest, Push)
{
    jc::Array<int> a;
    a.SetCapacity(numbers.size());

    for( uint32_t i = 0; i < a.Capacity(); ++i)
        a.Push(i % 4000);

    ASSERT_EQ(numbers.size(), a.Size());

    int sum1 = Sum(a, a.Size());
    ASSERT_EQ(sum, sum1);
}

TEST_F(ArrayTest, Pop)
{
    jc::Array<int> a;
    a.SetSize(numbers.size());
    FillArray(a, a.Size());

    int sum1 = 0;
    while( !a.Empty() )
        sum1 += a.Pop();

    ASSERT_EQ(0u, a.Size());
    ASSERT_EQ(sum, sum1);
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

TEST_F(ArrayTest, EraseSwap)
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
    ASSERT_EQ(3u, a.Size());
    ASSERT_TRUE(Compare(a, p, a.Size()));
    ASSERT_EQ(p[0], a.First());
    ASSERT_EQ(p[2], a.Last());

    a.EraseSwap(1);
    p = check3;
    ASSERT_EQ(2u, a.Size());
    ASSERT_TRUE(Compare(a, p, a.Size()));
    ASSERT_EQ(p[0], a.First());
    ASSERT_EQ(p[1], a.Last());

    a.EraseSwap(0);
    p = check4;
    ASSERT_EQ(1u, a.Size());
    ASSERT_TRUE(Compare(a, p, a.Size()));
    ASSERT_EQ(p[0], a.First());
    ASSERT_EQ(p[0], a.Last());

    a.EraseSwap(0);
    ASSERT_EQ(0u, a.Size());
}
