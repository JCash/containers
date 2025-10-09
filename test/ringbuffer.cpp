#include <stdint.h>
#include <string.h> // memset
#include <jc/cpp/ringbuffer.h>

#define JC_TEST_USE_DEFAULT_MAIN
#include "jc_test.h"

static void DebugPrint(jc::RingBuffer<int>& buf)
{
    uint32_t cap = buf.Capacity();
    uint32_t tail = buf.Tail();
    uint32_t head = buf.Head();
    int* data = buf.Buffer();

    printf("\nTail %u  Head %u  Max %u  Size %u Full %u  Empty %u\n", tail, head, cap, buf.Size(), buf.Full(), buf.Empty());

    printf("  ");
    for (uint32_t i = 0; i < cap; ++i) {
        printf("%2d", data[i]);
    }
    printf("\n");

    printf("  ");
    for (uint32_t i = 0; i < cap; ++i) {
        if (head == i && head == tail)
            printf(" ^");
        else if (head == i)
            printf(" H");
        else if (tail == i)
            printf(" T");
        else
            printf("  ");
    }
    printf("\n");
}

TEST(RingBufferTest, Create)
{
    jc::RingBuffer<int> a;
    ASSERT_EQ(0, a.Capacity());
    ASSERT_EQ(0, a.Size());
    ASSERT_TRUE(a.Empty());
    ASSERT_TRUE(a.Full());

    jc::RingBuffer<int> b(5);
    ASSERT_TRUE(b.Empty());
    ASSERT_FALSE(b.Full());
}


TEST(RingBufferTest, Add)
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

TEST(RingBufferTest, Swap)
{
    jc::RingBuffer<int> a(5);
    jc::RingBuffer<int> b(3);

    a.Push(1);
    a.Push(2);
    a.Push(3);

    b.Push(4);
    b.Push(5);

    ASSERT_EQ(5, a.Capacity());
    ASSERT_EQ(3, a.Size());
    ASSERT_EQ(1, a[0]);
    ASSERT_EQ(2, a[1]);
    ASSERT_EQ(3, a[2]);

    ASSERT_EQ(3, b.Capacity());
    ASSERT_EQ(2, b.Size());
    ASSERT_EQ(4, b[0]);
    ASSERT_EQ(5, b[1]);

    a.Swap(b);

    ASSERT_EQ(5, b.Capacity());
    ASSERT_EQ(3, b.Size());
    ASSERT_EQ(1, b[0]);
    ASSERT_EQ(2, b[1]);
    ASSERT_EQ(3, b[2]);

    ASSERT_EQ(3, a.Capacity());
    ASSERT_EQ(2, a.Size());
    ASSERT_EQ(4, a[0]);
    ASSERT_EQ(5, a[1]);
}

TEST(RingBufferTest, Flatten_InPlace_ContiguousOffset)
{
    jc::RingBuffer<int> rb(10);
    // Push 6 elements: 0..5
    for (int i = 0; i < 6; ++i) rb.Push(i);
    // Pop 2 -> logical sequence 2..5, contiguous but offset (tail=2)
    rb.Pop(); rb.Pop();

    ASSERT_EQ(4u, rb.Size());
    rb.Flatten();

    ASSERT_EQ(0u, rb.Tail());
    ASSERT_EQ(4u, rb.Head());
    const int expected1[4] = {2,3,4,5};
    ASSERT_ARRAY_EQ_LEN(expected1, rb.Buffer(), 4);
}

TEST(RingBufferTest, Flatten_InPlace_Wrapped)
{
    jc::RingBuffer<int> rb(10);
    // Fill to full 0..9
    for (int i = 0; i < 10; ++i) rb.Push(i);
    // Pop 6 -> tail moves to 6, size=4
    for (int i = 0; i < 6; ++i) rb.Pop();
    // Push 4 more -> wrap head, logical seq 6..13, size=8
    for (int i = 10; i < 14; ++i) rb.Push(i);

    ASSERT_EQ(8u, rb.Size());
    rb.Flatten();

    ASSERT_EQ(0u, rb.Tail());
    ASSERT_EQ(8u, rb.Head());
    const int expected2[8] = {6,7,8,9,10,11,12,13};
    ASSERT_ARRAY_EQ_LEN(expected2, rb.Buffer(), 8);
}

TEST(RingBufferTest, Flatten_HeadZero_TailPositive)
{
    jc::RingBuffer<int> rb(10);
    // Push 6 elements: 0..5  => head=6, tail=0
    for (int i = 0; i < 6; ++i) rb.Push(i);
    // Pop 4              => head=6, tail=4, size=2
    for (int i = 0; i < 4; ++i) rb.Pop();
    // Push 4 elements: 6..9 => head wraps to 0, tail=4, size=6, not full
    for (int i = 6; i < 10; ++i) rb.Push(i);

    ASSERT_EQ(0u, rb.Head());
    ASSERT_EQ(4u, rb.Tail());
    ASSERT_EQ(6u, rb.Size());
    ASSERT_FALSE(rb.Full());

    rb.Flatten();

    ASSERT_EQ(0u, rb.Tail());
    ASSERT_EQ(6u, rb.Head());
    const int expected[6] = {4,5,6,7,8,9};
    ASSERT_ARRAY_EQ_LEN(expected, rb.Buffer(), 6);
}

TEST(RingBufferTest, Flatten_AlreadyContiguous_Empty)
{
    jc::RingBuffer<int> rb(10);
    ASSERT_EQ(0u, rb.Size());
    ASSERT_EQ(0u, rb.Tail());
    ASSERT_EQ(0u, rb.Head());
    ASSERT_FALSE(rb.Full());

    rb.Flatten();

    ASSERT_EQ(0u, rb.Size());
    ASSERT_EQ(0u, rb.Tail());
    ASSERT_EQ(0u, rb.Head());
    ASSERT_FALSE(rb.Full());
}

TEST(RingBufferTest, Flatten_AlreadyContiguous_TailZero_NotFull)
{
    jc::RingBuffer<int> rb(10);
    for (int i = 0; i < 6; ++i) rb.Push(i);

    ASSERT_EQ(0u, rb.Tail());
    ASSERT_EQ(6u, rb.Head());
    ASSERT_EQ(6u, rb.Size());
    ASSERT_FALSE(rb.Full());

    rb.Flatten();

    ASSERT_EQ(0u, rb.Tail());
    ASSERT_EQ(6u, rb.Head());
    const int expected[6] = {0,1,2,3,4,5};
    ASSERT_ARRAY_EQ_LEN(expected, rb.Buffer(), 6);
}

TEST(RingBufferTest, Flatten_AlreadyContiguous_TailZero_Full)
{
    jc::RingBuffer<int> rb(10);
    for (int i = 0; i < 10; ++i) rb.Push(i);
    ASSERT_TRUE(rb.Full());
    ASSERT_EQ(10u, rb.Size());
    ASSERT_EQ(0u, rb.Tail());
    ASSERT_EQ(0u, rb.Head());

    rb.Flatten();

    ASSERT_TRUE(rb.Full());
    ASSERT_EQ(0u, rb.Tail());
    ASSERT_EQ(0u, rb.Head());
    const int expected[10] = {0,1,2,3,4,5,6,7,8,9};
    ASSERT_ARRAY_EQ_LEN(expected, rb.Buffer(), 10);
}

// Removed AssertSetEquals; use ASSERT_ARRAY_EQ_LEN to enforce physical start at index 0

TEST(RingBufferTest, FlattenUnordered_Contiguous_NoOp)
{
    jc::RingBuffer<int> rb(8);
    for (int i = 0; i < 5; ++i) rb.Push(i);
    ASSERT_EQ(0u, rb.Tail());
    ASSERT_EQ(5u, rb.Head());
    const int before[5] = {0,1,2,3,4};
    ASSERT_ARRAY_EQ_LEN(before, rb.Buffer(), 5);

    rb.FlattenUnordered();

    ASSERT_EQ(0u, rb.Tail());
    ASSERT_EQ(5u, rb.Head());
    ASSERT_ARRAY_EQ_LEN(before, rb.Buffer(), 5);
}

TEST(RingBufferTest, FlattenUnordered_ContiguousOffset)
{
    jc::RingBuffer<int> rb(8);
    for (int i = 0; i < 5; ++i) rb.Push(i); // 0..4
    rb.Pop(); rb.Pop(); // logical: 2..4
    // make it contiguous offset: tail=2, head=5
    ASSERT_EQ(2u, rb.Tail());
    ASSERT_EQ(5u, rb.Head());
    rb.FlattenUnordered();

    ASSERT_EQ(0u, rb.Tail());
    ASSERT_EQ(3u, rb.Head());
    const int expected[3] = {2,3,4};
    ASSERT_ARRAY_EQ_LEN(expected, rb.Buffer(), 3);
}

TEST(RingBufferTest, FlattenUnordered_Wrapped)
{
    jc::RingBuffer<int> rb(8);
    for (int i = 0; i < 8; ++i) rb.Push(i); // full
    for (int i = 0; i < 5; ++i) rb.Pop();   // size=3, tail moves to 5
    for (int i = 8; i < 12; ++i) rb.Push(i); // wrap, size=7, tail=5, head=4

    ASSERT_EQ(5u, rb.Tail());
    ASSERT_EQ(4u, rb.Head());
    ASSERT_EQ(7u, rb.Size());

    rb.FlattenUnordered();

    ASSERT_EQ(0u, rb.Tail());
    ASSERT_EQ(7u, rb.Head());
    const int expected[7] = {8,9,10,11,5,6,7};
    ASSERT_ARRAY_EQ_LEN(expected, rb.Buffer(), 7);
}

TEST(RingBufferTest, Erase_Contiguous_Middle)
{
    jc::RingBuffer<int> rb(8);
    for (int i = 0; i < 6; ++i) rb.Push(i); // 0..5

    int removed = rb.Erase(2); // remove '2'
    ASSERT_EQ(2, removed);
    ASSERT_EQ(5u, rb.Size());
    const int expected1[5] = {0,1,3,4,5};
    for (uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_EQ(expected1[i], rb[i]);
    }
}

TEST(RingBufferTest, Erase_Wrapped_Middle)
{
    jc::RingBuffer<int> rb(8);
    for (int i = 0; i < 8; ++i) rb.Push(i); // 0..7 full
    for (int i = 0; i < 5; ++i) rb.Pop();   // -> [5,6,7]
    for (int i = 8; i < 12; ++i) rb.Push(i); // wrap -> [5,6,7,8,9,10,11]

    int removed2 = rb.Erase(3); // remove '8'
    ASSERT_EQ(8, removed2);

    ASSERT_EQ(6u, rb.Size());
    const int expected2[6] = {5,6,7,9,10,11};
    for (uint32_t i = 0; i < 6; ++i)
    {
        ASSERT_EQ(expected2[i], rb[i]);
    }
}

TEST(RingBufferTest, Erase_HeadZero_TailPositive)
{
    jc::RingBuffer<int> rb(10);
    // Create head==0, tail>0, sequence [4,5,6,7,8,9]
    for (int i = 0; i < 6; ++i) rb.Push(i); // 0..5
    for (int i = 0; i < 4; ++i) rb.Pop();   // tail=4, size=2
    for (int i = 6; i < 10; ++i) rb.Push(i); // wraps, head==0

    ASSERT_EQ(0u, rb.Head());
    ASSERT_EQ(4u, rb.Tail());

    int removed3 = rb.Erase(1); // remove '5'
    ASSERT_EQ(5, removed3);

    ASSERT_EQ(5u, rb.Size());
    const int expected3[5] = {4,6,7,8,9};
    for (uint32_t i = 0; i < 5; ++i)
    {
        ASSERT_EQ(expected3[i], rb[i]);
    }
}
