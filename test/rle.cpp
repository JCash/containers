
#define JC_TEST_USE_DEFAULT_MAIN
#include "jc_test.h"

#define JC_RLE_IMPLEMENTATION
//#define JC_RLE_DEBUG
#include <jc/c/rle.h>

#include <memory.h>

// C++0x and above
#if !defined(_MSC_VER)
#if __cplusplus >= 201103L
    #pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
#endif
#endif


struct RleTestData
{
    uint8_t* m_Input;
    uint8_t* m_Expected;
    uint32_t m_InputSize;
    uint32_t m_ExpectedSize;
};

static uint8_t original1[] = "A";
static uint8_t encoded1[]  = {1 + 127, 'A'};

static uint8_t original2[] = "AA";
static uint8_t encoded2[]  = {2, 'A'};

static uint8_t original3[] = "ABAB";
static uint8_t encoded3[]  = {4 + 127, 'A', 'B', 'A', 'B'};

static uint8_t original4[] = "ABABB";
static uint8_t encoded4[]  = {3 + 127, 'A', 'B', 'A', 2, 'B'};

static uint8_t original5[] = "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA";
static uint8_t encoded5[]  = {127, 'A', 15, 'A'};

#define TEST_DATA(A, B) { A, B, sizeof(A), sizeof(B)}

TEST(Rle, Encode)
{
    RleTestData tests[] = {
        TEST_DATA(original1, encoded1),
        TEST_DATA(original2, encoded2),
        TEST_DATA(original3, encoded3),
        TEST_DATA(original4, encoded4),
        TEST_DATA(original5, encoded5),
    };

    printf("\n");

    for (uint32_t i = 0; i < sizeof(tests)/sizeof(RleTestData); ++i) {
        const RleTestData& test = tests[i];
        printf("%2d: %.*s\n", i, test.m_InputSize-1, test.m_Input);

        uint8_t buffer[1024] = {0};

        // Make sure it calculates the output size correctly
        ASSERT_EQ(test.m_ExpectedSize, jc_rle_encode(test.m_InputSize-1, test.m_Input, 0));

        uint32_t encodedlen = jc_rle_encode(test.m_InputSize-1, test.m_Input, buffer);
        jc_rle_debug_print(encodedlen, buffer);
        ASSERT_EQ(test.m_ExpectedSize, encodedlen);
        ASSERT_ARRAY_EQ_LEN(test.m_Expected, buffer, encodedlen);
    }
}

TEST(Rle, Decode)
{
    RleTestData tests[] = {
        TEST_DATA(encoded1, original1),
        TEST_DATA(encoded2, original2),
        TEST_DATA(encoded3, original3),
        TEST_DATA(encoded4, original4),
        TEST_DATA(encoded5, original5),
    };

    uint8_t buffer[1024];

    printf("\n");

    for (uint32_t i = 0; i < sizeof(tests)/sizeof(RleTestData); ++i) {
        memset(buffer, 0, sizeof(buffer));

        const RleTestData& test = tests[i];
        // Make sure it calculates the output size correctly
        ASSERT_EQ(test.m_ExpectedSize-1, jc_rle_decode(test.m_InputSize-1, test.m_Input, 0));

        uint32_t decodedlen = jc_rle_decode(test.m_InputSize, test.m_Input, buffer);
        printf("%2d:\n", i);
        jc_rle_debug_print(test.m_InputSize, test.m_Input);

        printf("    %.*s\n", decodedlen, buffer);
        ASSERT_EQ(test.m_ExpectedSize-1, decodedlen);
        ASSERT_ARRAY_EQ_LEN(test.m_Expected, buffer, decodedlen);
    }
}
