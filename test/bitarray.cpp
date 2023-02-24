#include <stdint.h>
#define JC_BITARRAY_IMPLEMENTATION
#include <jc/c/bitarray.h>
#define JC_TEST_USE_DEFAULT_MAIN
#include "jc_test.h"

// static void jcba_print(jcba_bitarray* ba)
// {
//     uint32_t num_bytes = jcba_bitcountinbytes(ba);
//     for (uint32_t b = 0, bc = ba->bitcount; b < num_bytes; ++b, bc -= 8)
//     {
//         uint8_t byte = ba->bits[b];
//         for (uint32_t bit = 0; bit < 8 && bit < bc; ++bit)
//         {
//             printf("%d", (byte>>bit)&0x1);
//         }
//         printf(" ");
//     }
//     printf("\n");
//     for (uint32_t b = 0; b < num_bytes; ++b)
//     {
//         printf("0x%02X     ", ba->bits[b]);
//     }
//     printf("\n");
// }

template<typename TestType>
struct Funcs
{
    typedef typename TestType::ArrayType ArrayType;

    typedef ArrayType* (*CreateFn)(uint32_t bit_count);
    typedef void       (*DestroyFn)(ArrayType*);
};

struct TestCInterface
{
    typedef jcba_bitarray ArrayType;

    jcba_bitarray* GetInternal(ArrayType* ba)           { return ba; } // for the tests only
    ArrayType*  Create(uint32_t bit_count)              { return jcba_create(bit_count); }
    void        Destroy(ArrayType* ba)                  { jcba_destroy(ba); }
    uint32_t    Capacity(ArrayType* ba)                 { return ba->capacity; }
    uint32_t    Bitcount(ArrayType* ba)                 { return ba->bitcount; }
    void        Clear(ArrayType* ba, uint32_t value)    { return jcba_clear(ba, value); }
    bool        IsAllOnes(ArrayType* ba)                { return jcba_is_all_ones(ba); }
    bool        IsAllZeroes(ArrayType* ba)              { return jcba_is_all_zeroes(ba); }
    uint32_t    GetBit(ArrayType* ba, uint32_t index)   { return jcba_getbit(ba, index); }
    void        SetBit(ArrayType* ba, uint32_t index, uint32_t bit) { jcba_setbit(ba, index, bit); }
    void        Erase(ArrayType* ba, uint32_t index, uint32_t count) { jcba_erase(ba, index, count); }
};

struct TestCPPInterface
{
    typedef jc::BitArray ArrayType;

    jcba_bitarray* GetInternal(ArrayType* ba)           { return ba->ba; } // for the tests only
    ArrayType*  Create(uint32_t bit_count)              { return new jc::BitArray(bit_count); }
    void        Destroy(ArrayType* ba)                  { delete ba; }
    uint32_t    Capacity(ArrayType* ba)                 { return ba->Capacity(); }
    uint32_t    Bitcount(ArrayType* ba)                 { return ba->Bitcount(); }
    void        Clear(ArrayType* ba, uint32_t value)    { return ba->Clear(value); }
    bool        IsAllOnes(ArrayType* ba)                { return ba->IsAllOnes(); }
    bool        IsAllZeroes(ArrayType* ba)              { return ba->IsAllZeroes(); }
    uint32_t    GetBit(ArrayType* ba, uint32_t index)   { return ba->GetBit(index); }
    void        SetBit(ArrayType* ba, uint32_t index, uint32_t bit) { ba->SetBit(index, bit); }
    void        Erase(ArrayType* ba, uint32_t index, uint32_t count) { ba->Erase(index, count); }
};

template<typename T>
class InterfaceTest : public jc_test_base_class
{
protected:
    T m_Test;
    uint8_t pad[7]; // to silence a compiler warning
};

typedef jc_test_type2<TestCInterface, TestCPPInterface> InterfaceTestTypes;
TYPED_TEST_CASE(InterfaceTest, InterfaceTestTypes);


TEST(BitArrayTest, RoundUp)
{
    for (uint32_t n = 1; n <= 2; ++n)
    {
        uint32_t multiple = 8 * n;
        ASSERT_EQ(0U, jcba_roundup(0, multiple));
        for (uint32_t i = 1; i <= multiple; ++i )
        {
            ASSERT_EQ(multiple, jcba_roundup(1, multiple));
        }
    }
}

TYPED_TEST(InterfaceTest, CreateDestroy)
{
    uint32_t bitcount = 17;
    typename TypeParam::ArrayType* ba = TestFixture::m_Test.Create(bitcount);
    ASSERT_EQ(3U, TestFixture::m_Test.Capacity(ba));
    ASSERT_EQ(bitcount, TestFixture::m_Test.Bitcount(ba));

    TestFixture::m_Test.Destroy(ba);
}

TYPED_TEST(InterfaceTest, OutOfBounds)
{
    uint32_t bitcount = 17;
    typename TypeParam::ArrayType* ba = TestFixture::m_Test.Create(bitcount);
    ASSERT_EQ(3U, TestFixture::m_Test.Capacity(ba));

    ASSERT_DEATH(TestFixture::m_Test.GetBit(ba, 18),"");
    ASSERT_DEATH(TestFixture::m_Test.SetBit(ba, 18, 1),"");

    TestFixture::m_Test.Destroy(ba);
}

TYPED_TEST(InterfaceTest, Clear)
{
    uint32_t bitcount = 17;
    typename TypeParam::ArrayType* ba = TestFixture::m_Test.Create(bitcount);
    ASSERT_EQ(3U, TestFixture::m_Test.Capacity(ba));

    jcba_bitarray* bai = TestFixture::m_Test.GetInternal(ba);

    uint8_t zeroes[] = {0x00, 0x00, 0x00};
    uint8_t ones[] = {0xFF, 0xFF, 0xFF};

    TestFixture::m_Test.Clear(ba, 1);
    ASSERT_ARRAY_EQ_LEN(ones, bai->bits, bai->capacity);

    TestFixture::m_Test.Clear(ba, 0);
    ASSERT_ARRAY_EQ_LEN(zeroes, bai->bits, bai->capacity);

    TestFixture::m_Test.Clear(ba, 0x70); // Testing non zero values
    ASSERT_ARRAY_EQ_LEN(ones, bai->bits, bai->capacity);

    TestFixture::m_Test.Destroy(ba);
}

TYPED_TEST(InterfaceTest, IsAllSet)
{
    uint32_t bitcount = 17;
    typename TypeParam::ArrayType* ba = TestFixture::m_Test.Create(bitcount);
    ASSERT_EQ(3U, TestFixture::m_Test.Capacity(ba));

    TestFixture::m_Test.Clear(ba, 1);
    ASSERT_EQ(1U, TestFixture::m_Test.IsAllOnes(ba));
    ASSERT_EQ(0U, TestFixture::m_Test.IsAllZeroes(ba));

    TestFixture::m_Test.Clear(ba, 0);
    ASSERT_EQ(0U, TestFixture::m_Test.IsAllOnes(ba));
    ASSERT_EQ(1U, TestFixture::m_Test.IsAllZeroes(ba));

    TestFixture::m_Test.Destroy(ba);
}


TYPED_TEST(InterfaceTest, SetGetBit)
{
    uint32_t bitcount = 17;
    typename TypeParam::ArrayType* ba = TestFixture::m_Test.Create(bitcount);
    ASSERT_EQ(3U, TestFixture::m_Test.Capacity(ba));

    TestFixture::m_Test.Clear(ba, 0);

    for (uint32_t i = 0; i < bitcount; ++i)
    {
        ASSERT_EQ(0U, TestFixture::m_Test.GetBit(ba, i));
        ASSERT_NE(1U, TestFixture::m_Test.GetBit(ba, i));
    }

    TestFixture::m_Test.Clear(ba, 1);

    for (uint32_t i = 0; i < bitcount; ++i)
    {
        ASSERT_EQ(1U, TestFixture::m_Test.GetBit(ba, i));
        ASSERT_NE(0U, TestFixture::m_Test.GetBit(ba, i));
    }

    jcba_bitarray* bai = TestFixture::m_Test.GetInternal(ba);
    bai->bits[1] = (1 << 1) | (1 << 3) | (1 << 5) | (1 << 7); // 0xAA
    for (uint32_t i = 8; i < 16; ++i)
    {
        if (i % 2) // odd
            ASSERT_EQ(1U, TestFixture::m_Test.GetBit(ba, i));
        else
            ASSERT_EQ(0U, TestFixture::m_Test.GetBit(ba, i));
    }

    bai->bits[1] = 0;
    TestFixture::m_Test.SetBit(ba, 9, 1);
    TestFixture::m_Test.SetBit(ba, 11, 1);
    TestFixture::m_Test.SetBit(ba, 13, 1);
    TestFixture::m_Test.SetBit(ba, 15, 1);

    ASSERT_EQ(0xAA, bai->bits[1]);

    TestFixture::m_Test.Destroy(ba);
}

TYPED_TEST(InterfaceTest, Erase)
{
    uint32_t bitcount = 17;
    typename TypeParam::ArrayType* ba = TestFixture::m_Test.Create(bitcount);
    ASSERT_EQ(3U, TestFixture::m_Test.Capacity(ba));

    jcba_bitarray* bai = TestFixture::m_Test.GetInternal(ba);

    bai->bits[0] = 0x0F;
    bai->bits[1] = 0xF3;
    bai->bits[2] = 0x01;

    TestFixture::m_Test.Erase(ba, 4, 4);
    ASSERT_EQ(13U, TestFixture::m_Test.Bitcount(ba));

    uint8_t expected[] = {0x3F, 0xFF}; // the 0xFF is expected since we leave the old bits as-is
    ASSERT_ARRAY_EQ_LEN(expected, bai->bits, 2);

    TestFixture::m_Test.Destroy(ba);
}

TEST(Examples, C)
{
    jcba_bitarray* ba = jcba_create(17);
    jcba_clear(ba, 0); // Set all zeroes
    uint32_t v = jcba_getbit(ba, 15); // value is 0 or 1
    jcba_setbit(ba, 15, 1);
    jcba_destroy(ba);

    (void)v;
}

TEST(Examples, CPP)
{
    jc::BitArray* ba = new jc::BitArray(17);
    ba->Clear(0); // Set all zeroes
    uint32_t v = ba->GetBit(15);  // value is 0 or 1
    ba->SetBit(15, 1); // value is 0 or not
    delete ba;

    (void)v;
}
