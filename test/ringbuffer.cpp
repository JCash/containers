#include <stdint.h>
#include <deque>
#include <jc/ringbuffer.h>

#define JC_TEST_USE_DEFAULT_MAIN
#include "jc_test.h"

template<typename T>
static int FillBuffer(T& a, size_t count)
{
    int sum = 0;
    for( uint32_t i = 0; i < count; ++i)
    {
        a[i] = i % 4000;
        sum += a[i];
    }
    return sum;
}

class RingBufferTest : public jc_test_base_class
{
protected:
    RingBufferTest() {}
    virtual ~RingBufferTest() JC_OVERRIDE;
    void SetUp() JC_OVERRIDE
    {
        size_t count = (size_t)(65436 + rand() % 100);
        numbers.resize(count);
        FillBuffer(numbers, count);
    }

    std::deque<int> numbers;
};

RingBufferTest::~RingBufferTest() {}


static void DebugPrint(jc::RingBuffer<int>& buf) {
    uint32_t cap = buf.Capacity();
    uint32_t tail = buf.Tail();
    uint32_t head = buf.Head();
    int* data = buf.Buffer();

    printf("\nTail %u  Head %u  Max %u  Size %u Full %u  Empty %u\n", tail, head, cap, buf.Size(), buf.Full(), buf.Empty());

    printf("  ");
    for (uint32_t i = 0; i < cap; ++i) {
        printf("%d", data[i]);
    }
    printf("\n");

    printf("  ");
    for (uint32_t i = 0; i < cap; ++i) {
        if (head == i && head == tail)
            printf("^");
        else if (head == i)
            printf("H");
        else if (tail == i)
            printf("T");
        else
            printf(" ");
    }
    printf("\n");
}

TEST_F(RingBufferTest, Create)
{
    jc::RingBuffer<int> a;
    ASSERT_FALSE(a.Empty());
    ASSERT_TRUE(a.Full());
    ASSERT_EQ(0, a.Capacity());

    jc::RingBuffer<int> b(5);
    ASSERT_TRUE(b.Empty());
    ASSERT_FALSE(b.Full());
}


TEST_F(RingBufferTest, Add)
{
    int maxcount = 5;
    int array[6] = {0};
    int count = 0;

    jc::RingBuffer<int> a(5);
    memset(a.Buffer(), 0, sizeof(int)*a.Capacity());

    ASSERT_EQ(5, a.Capacity());

    // add 3

    for (int i = 0, v = count; i < 3; ++i, ++v)
    {
        array[(count++)%maxcount] = v;
        a.Push(v);
    }
    //   01200
    //   T  H

    DebugPrint(a);

    ASSERT_EQ(3, a.Size());
    ASSERT_FALSE(a.Empty());
    ASSERT_FALSE(a.Full());

    ASSERT_ARRAY_EQ_LEN(array, a.Buffer(), a.Capacity());

    // add 2 more

    for (int i = 0, v = count; i < 2; ++i, ++v)
    {
        array[(count++)%maxcount] = v;
        a.Push(v);
    }
    //   01234
    //   ^

    DebugPrint(a);

    ASSERT_EQ(5, a.Size());
    ASSERT_FALSE(a.Empty());
    ASSERT_TRUE(a.Full());

    ASSERT_ARRAY_EQ_LEN(array, a.Buffer(), a.Capacity());

    // add 1 more, invoking an assert
    ASSERT_DEATH(a.Push(10), "Push");

    // add 2 more, overwriting elements

    for (int i = 0, v = count; i < 2; ++i, ++v)
    {
        array[(count++)%maxcount] = v;
        a.PushUnchecked(v);
    }
    //   56234
    //     ^

    DebugPrint(a);

    ASSERT_EQ(5, a.Size());
    ASSERT_FALSE(a.Empty());
    ASSERT_TRUE(a.Full());

    ASSERT_ARRAY_EQ_LEN(array, a.Buffer(), a.Capacity());

    // remove 2

    for (int i = 0; i < 2; ++i)
    {
        int va = array[(count++)%maxcount];
        int vi = a[0];
        int vb = a.Pop();
        ASSERT_EQ(va, vi);
        ASSERT_EQ(va, vb);
    }
    //   56234
    //     H T

    DebugPrint(a);

    ASSERT_EQ(3, a.Size());
    ASSERT_FALSE(a.Empty());
    ASSERT_FALSE(a.Full());

    ASSERT_ARRAY_EQ_LEN(array, a.Buffer(), a.Capacity());

    // index operator
    for(int i = 0, v = 4; i < (int)a.Size(); ++i, ++v)
    {
        int vb = a[(size_t)i];
        ASSERT_EQ(v, vb);
    }

    // Resize
    //  56234
    //    H T
    a.SetCapacity(6);
    // ->
    //  456xx
    //  T  H

    memset(a.Buffer()+a.Size(), 0, sizeof(int)*(a.Capacity()-a.Size())); // just make the printout nicer

    DebugPrint(a);

    array[0] = 4;
    array[1] = 5;
    array[2] = 6;

    ASSERT_EQ(3, a.Size());
    ASSERT_FALSE(a.Empty());
    ASSERT_FALSE(a.Full());

    // Check that the start of the buffer is the same as before
    ASSERT_ARRAY_EQ_LEN(array, a.Buffer(), a.Size());

    maxcount = 6;

    // Add 3 more items

    for (int i = 0, v = 7; i < 3; ++i, ++v)
    {
        array[(count++)%maxcount] = v;
        a.Push(v);
    }

    DebugPrint(a);

    ASSERT_EQ(6, a.Size());
    ASSERT_FALSE(a.Empty());
    ASSERT_TRUE(a.Full());

    ASSERT_ARRAY_EQ_LEN(array, a.Buffer(), a.Size());

    // Clear all elements

    while(a.Size())
        a.Pop();

    DebugPrint(a);

    ASSERT_EQ(0, a.Size());
    ASSERT_TRUE(a.Empty());
    ASSERT_FALSE(a.Full());

    // Clear it

    a.Clear();

    ASSERT_EQ(0, a.Size());
    ASSERT_TRUE(a.Empty());
    ASSERT_FALSE(a.Full());
}
