/* jc_test.h - single-header C11 test framework
 * Copyright 2018-2026 Mathias Westerdahl
 * SPDX-License-Identifier: MIT
 *
 * C++ translation units are forwarded to jc_test.hpp for source compatibility.
 * Define JC_TEST_IMPLEMENTATION in exactly one C translation unit.
 */

#ifndef JC_TEST_C_DISPATCH_H
#define JC_TEST_C_DISPATCH_H

#if defined(__cplusplus)

#include "jc_test.hpp"

#else

#if !defined(__STDC_VERSION__) || (__STDC_VERSION__ < 201112L)
#error "jc_test.h requires C11 or newer"
#endif

#include <float.h>
#include <limits.h>
#include <inttypes.h>
#include <setjmp.h>
#include <signal.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>

#if defined(_WIN32)
#include <Windows.h>
#include <io.h>
#else
#include <sys/time.h>
#include <unistd.h>
#endif

#if !defined(JC_TEST_SNPRINTF)
#if defined(_MSC_VER)
#define JC_TEST_SNPRINTF _snprintf
#else
#define JC_TEST_SNPRINTF snprintf
#endif
#endif

#if !defined(JC_TEST_EXIT)
#define JC_TEST_EXIT exit
#endif

#if !defined(JC_TEST_ASSERT_FN)
#include <assert.h>
#define JC_TEST_ASSERT_FN assert
#endif

#if !defined(JC_TEST_DBG_BREAK)
#if defined(_MSC_VER)
#include <intrin.h>
#define JC_TEST_DBG_BREAK() __debugbreak()
#elif defined(__has_builtin)
#if __has_builtin(__builtin_debugtrap)
#define JC_TEST_DBG_BREAK() __builtin_debugtrap()
#else
#define JC_TEST_DBG_BREAK() abort()
#endif
#else
#define JC_TEST_DBG_BREAK() abort()
#endif
#endif

#if defined(__GNUC__) || defined(__clang__)
#define JC_TEST_C_UNUSED __attribute__((unused))
#else
#define JC_TEST_C_UNUSED
#endif

typedef uint64_t jc_test_time_t;

#if !defined(JC_TEST_TIMING_FUNC)
#define JC_TEST_TIMING_FUNC jc_test_get_time
jc_test_time_t jc_test_get_time(void);
#define JC_TEST_C_DEFAULT_TIMING 1
#endif

#if !defined(JCT_IS_DEBUGGER_ATTACHED)
#define JCT_IS_DEBUGGER_ATTACHED() 0
#endif

typedef struct jc_test_stats {
    int num_pass;
    int num_fail;
    int num_skipped;
    int num_assertions;
    int num_tests;
    jc_test_time_t totaltime;
} jc_test_stats;

typedef enum jc_test_value_kind {
    JC_TEST_VALUE_SIGNED,
    JC_TEST_VALUE_UNSIGNED,
    JC_TEST_VALUE_FLOAT,
    JC_TEST_VALUE_DOUBLE,
    JC_TEST_VALUE_LONG_DOUBLE,
    JC_TEST_VALUE_POINTER
} jc_test_value_kind;

typedef struct jc_test_value {
    jc_test_value_kind kind;
    unsigned int bits;
    union {
        intmax_t signed_value;
        uintmax_t unsigned_value;
        long double float_value;
        const void* pointer_value;
    } data;
} jc_test_value;

typedef void (*jc_test_c_func)(void);

typedef struct jc_test_entry {
    struct jc_test_entry* next;
    const char* suite_name;
    const char* test_name;
    const char* filename;
    int line;
    jc_test_c_func run;
    jc_test_time_t time;
    unsigned int fail:1;
    unsigned int skipped:1;
} jc_test_entry;

void jc_test_init(int* argc, char** argv);
int jc_test_run_all(void);
void jc_test_register(jc_test_entry* test);

void jc_test_assert_boolean(int value, int expected, const char* expression,
                            const char* file, int line, int fatal);
void jc_test_assert_compare(jc_test_value a, jc_test_value b, int operation,
                            const char* expression_a, const char* expression_b,
                            const char* file, int line, int fatal);
void jc_test_assert_string(const char* a, const char* b, int equal,
                           const char* expression_a, const char* expression_b,
                           const char* file, int line, int fatal);
void jc_test_assert_near(long double a, long double b, long double epsilon,
                         const char* expression_a, const char* expression_b,
                         const char* expression_epsilon,
                         const char* file, int line, int fatal);
void jc_test_assert_array(const void* a, const void* b, size_t length,
                          size_t element_size, const char* expression_a,
                          const char* expression_b,
                          const char* file, int line, int fatal);
int jc_test_current_fatal(void);
int jc_test_current_skipped(void);
void jc_test_set_test_skipped(void);
void jc_test_clear_fatal(void);

static inline jc_test_value jc_test_value_signed(intmax_t value, unsigned int bits) {
    jc_test_value result;
    result.kind = JC_TEST_VALUE_SIGNED;
    result.bits = bits;
    result.data.signed_value = value;
    return result;
}

static inline jc_test_value jc_test_value_unsigned(uintmax_t value, unsigned int bits) {
    jc_test_value result;
    if (bits < (unsigned int)(sizeof(int) * CHAR_BIT)) {
        result.kind = JC_TEST_VALUE_SIGNED;
        result.bits = (unsigned int)(sizeof(int) * CHAR_BIT);
        result.data.signed_value = (intmax_t)value;
    } else {
        result.kind = JC_TEST_VALUE_UNSIGNED;
        result.bits = bits;
        result.data.unsigned_value = value;
    }
    return result;
}

static inline jc_test_value jc_test_value_float(float value, unsigned int bits) {
    jc_test_value result;
    (void)bits;
    result.kind = JC_TEST_VALUE_FLOAT;
    result.bits = (unsigned int)(sizeof(float) * CHAR_BIT);
    result.data.float_value = (long double)value;
    return result;
}

static inline jc_test_value jc_test_value_double(double value, unsigned int bits) {
    jc_test_value result;
    (void)bits;
    result.kind = JC_TEST_VALUE_DOUBLE;
    result.bits = (unsigned int)(sizeof(double) * CHAR_BIT);
    result.data.float_value = (long double)value;
    return result;
}

static inline jc_test_value jc_test_value_long_double(long double value, unsigned int bits) {
    jc_test_value result;
    (void)bits;
    result.kind = JC_TEST_VALUE_LONG_DOUBLE;
    result.bits = (unsigned int)(sizeof(long double) * CHAR_BIT);
    result.data.float_value = value;
    return result;
}

static inline jc_test_value jc_test_value_pointer(const void* value, unsigned int bits) {
    jc_test_value result;
    (void)bits;
    result.kind = JC_TEST_VALUE_POINTER;
    result.bits = (unsigned int)(sizeof(void*) * CHAR_BIT);
    result.data.pointer_value = value;
    return result;
}

#if CHAR_MIN < 0
#define JC_TEST_C_CHAR_VALUE jc_test_value_signed
#else
#define JC_TEST_C_CHAR_VALUE jc_test_value_unsigned
#endif

#define JC_TEST_C_VALUE(_VALUE)                                                \
    _Generic((1 ? (_VALUE) : 0),                                              \
        _Bool: jc_test_value_unsigned,                                         \
        char: JC_TEST_C_CHAR_VALUE,                                            \
        signed char: jc_test_value_signed,                                     \
        unsigned char: jc_test_value_unsigned,                                 \
        short: jc_test_value_signed,                                           \
        unsigned short: jc_test_value_unsigned,                                \
        int: jc_test_value_signed,                                             \
        unsigned int: jc_test_value_unsigned,                                  \
        long: jc_test_value_signed,                                            \
        unsigned long: jc_test_value_unsigned,                                 \
        long long: jc_test_value_signed,                                       \
        unsigned long long: jc_test_value_unsigned,                            \
        float: jc_test_value_float,                                            \
        double: jc_test_value_double,                                          \
        long double: jc_test_value_long_double,                                \
        default: jc_test_value_pointer                                         \
    )((1 ? (_VALUE) : 0),                                                     \
      (unsigned int)(sizeof(1 ? (_VALUE) : 0) * CHAR_BIT))

#define JC_TEST_C_IS_NUMERIC(_VALUE)                                           \
    _Generic((1 ? (_VALUE) : 0),                                              \
        _Bool: 1, char: 1, signed char: 1, unsigned char: 1,                   \
        short: 1, unsigned short: 1, int: 1, unsigned int: 1,                  \
        long: 1, unsigned long: 1, long long: 1,                               \
        unsigned long long: 1, float: 1, double: 1, long double: 1,            \
        default: 0)

enum {
    JC_TEST_COMPARE_EQ,
    JC_TEST_COMPARE_NE,
    JC_TEST_COMPARE_LT,
    JC_TEST_COMPARE_GT,
    JC_TEST_COMPARE_LE,
    JC_TEST_COMPARE_GE
};

#define JC_TEST_C_FATAL 1
#define JC_TEST_C_NON_FATAL 0

#define JC_TEST_C_ASSERT_BOOLEAN(_VALUE, _EXPECTED, _FATAL)                    \
    do {                                                                       \
        int jc_test_c_boolean = !!(_VALUE);                                    \
        jc_test_assert_boolean(jc_test_c_boolean, (_EXPECTED), #_VALUE,         \
                               __FILE__, __LINE__, (_FATAL));                   \
        if ((_FATAL) && jc_test_current_fatal()) return;                       \
    } while (0)

#define JC_TEST_C_ASSERT_COMPARE(_A, _B, _OPERATION, _FATAL)                   \
    do {                                                                       \
        jc_test_value jc_test_c_a = JC_TEST_C_VALUE(_A);                       \
        jc_test_value jc_test_c_b = JC_TEST_C_VALUE(_B);                       \
        jc_test_assert_compare(jc_test_c_a, jc_test_c_b, (_OPERATION),         \
                               #_A, #_B, __FILE__, __LINE__, (_FATAL));         \
        if ((_FATAL) && jc_test_current_fatal()) return;                       \
    } while (0)

#define JC_TEST_C_ASSERT_ORDERED(_A, _B, _OPERATION, _FATAL)                   \
    do {                                                                       \
        _Static_assert(JC_TEST_C_IS_NUMERIC(_A) && JC_TEST_C_IS_NUMERIC(_B),   \
                       "ordered assertions require numeric operands");       \
        JC_TEST_C_ASSERT_COMPARE(_A, _B, _OPERATION, _FATAL);                  \
    } while (0)

#define JC_TEST_C_ASSERT_STRING(_A, _B, _EQUAL, _FATAL)                        \
    do {                                                                       \
        const char* jc_test_c_a = (_A);                                        \
        const char* jc_test_c_b = (_B);                                        \
        jc_test_assert_string(jc_test_c_a, jc_test_c_b, (_EQUAL), #_A, #_B,    \
                              __FILE__, __LINE__, (_FATAL));                    \
        if ((_FATAL) && jc_test_current_fatal()) return;                       \
    } while (0)

#define JC_TEST_C_ASSERT_NEAR(_A, _B, _EPSILON, _FATAL)                        \
    do {                                                                       \
        long double jc_test_c_a = (long double)(_A);                           \
        long double jc_test_c_b = (long double)(_B);                           \
        long double jc_test_c_epsilon = (long double)(_EPSILON);               \
        jc_test_assert_near(jc_test_c_a, jc_test_c_b, jc_test_c_epsilon,       \
                            #_A, #_B, #_EPSILON, __FILE__, __LINE__, (_FATAL)); \
        if ((_FATAL) && jc_test_current_fatal()) return;                       \
    } while (0)

#define JC_TEST_C_ASSERT_ARRAY(_A, _B, _LENGTH, _ELEMENT_SIZE, _FATAL)         \
    do {                                                                       \
        const void* jc_test_c_a = (const void*)(_A);                           \
        const void* jc_test_c_b = (const void*)(_B);                           \
        size_t jc_test_c_length = (size_t)(_LENGTH);                           \
        jc_test_assert_array(jc_test_c_a, jc_test_c_b, jc_test_c_length,       \
                             (size_t)(_ELEMENT_SIZE), #_A, #_B,                \
                             __FILE__, __LINE__, (_FATAL));                    \
        if ((_FATAL) && jc_test_current_fatal()) return;                       \
    } while (0)

#define ASSERT_TRUE(_VALUE) JC_TEST_C_ASSERT_BOOLEAN(_VALUE, 1, JC_TEST_C_FATAL)
#define ASSERT_FALSE(_VALUE) JC_TEST_C_ASSERT_BOOLEAN(_VALUE, 0, JC_TEST_C_FATAL)
#define ASSERT_EQ(_A, _B) JC_TEST_C_ASSERT_COMPARE(_A, _B, JC_TEST_COMPARE_EQ, JC_TEST_C_FATAL)
#define ASSERT_NE(_A, _B) JC_TEST_C_ASSERT_COMPARE(_A, _B, JC_TEST_COMPARE_NE, JC_TEST_C_FATAL)
#define ASSERT_LT(_A, _B) JC_TEST_C_ASSERT_ORDERED(_A, _B, JC_TEST_COMPARE_LT, JC_TEST_C_FATAL)
#define ASSERT_GT(_A, _B) JC_TEST_C_ASSERT_ORDERED(_A, _B, JC_TEST_COMPARE_GT, JC_TEST_C_FATAL)
#define ASSERT_LE(_A, _B) JC_TEST_C_ASSERT_ORDERED(_A, _B, JC_TEST_COMPARE_LE, JC_TEST_C_FATAL)
#define ASSERT_GE(_A, _B) JC_TEST_C_ASSERT_ORDERED(_A, _B, JC_TEST_COMPARE_GE, JC_TEST_C_FATAL)
#define ASSERT_STREQ(_A, _B) JC_TEST_C_ASSERT_STRING(_A, _B, 1, JC_TEST_C_FATAL)
#define ASSERT_STRNE(_A, _B) JC_TEST_C_ASSERT_STRING(_A, _B, 0, JC_TEST_C_FATAL)
#define ASSERT_NEAR(_A, _B, _EPSILON) JC_TEST_C_ASSERT_NEAR(_A, _B, _EPSILON, JC_TEST_C_FATAL)
#define ASSERT_ARRAY_EQ(_A, _B)                                              \
    do {                                                                      \
        _Static_assert(sizeof(_A) == sizeof(_B), "array sizes must match");   \
        JC_TEST_C_ASSERT_ARRAY(_A, _B, sizeof(_A) / sizeof((_A)[0]),          \
                               sizeof((_A)[0]), JC_TEST_C_FATAL);              \
    } while (0)
#define ASSERT_ARRAY_EQ_LEN(_A, _B, _LENGTH)                                  \
    JC_TEST_C_ASSERT_ARRAY(_A, _B, _LENGTH, sizeof((_A)[0]), JC_TEST_C_FATAL)

#define EXPECT_TRUE(_VALUE) JC_TEST_C_ASSERT_BOOLEAN(_VALUE, 1, JC_TEST_C_NON_FATAL)
#define EXPECT_FALSE(_VALUE) JC_TEST_C_ASSERT_BOOLEAN(_VALUE, 0, JC_TEST_C_NON_FATAL)
#define EXPECT_EQ(_A, _B) JC_TEST_C_ASSERT_COMPARE(_A, _B, JC_TEST_COMPARE_EQ, JC_TEST_C_NON_FATAL)
#define EXPECT_NE(_A, _B) JC_TEST_C_ASSERT_COMPARE(_A, _B, JC_TEST_COMPARE_NE, JC_TEST_C_NON_FATAL)
#define EXPECT_LT(_A, _B) JC_TEST_C_ASSERT_ORDERED(_A, _B, JC_TEST_COMPARE_LT, JC_TEST_C_NON_FATAL)
#define EXPECT_GT(_A, _B) JC_TEST_C_ASSERT_ORDERED(_A, _B, JC_TEST_COMPARE_GT, JC_TEST_C_NON_FATAL)
#define EXPECT_LE(_A, _B) JC_TEST_C_ASSERT_ORDERED(_A, _B, JC_TEST_COMPARE_LE, JC_TEST_C_NON_FATAL)
#define EXPECT_GE(_A, _B) JC_TEST_C_ASSERT_ORDERED(_A, _B, JC_TEST_COMPARE_GE, JC_TEST_C_NON_FATAL)
#define EXPECT_STREQ(_A, _B) JC_TEST_C_ASSERT_STRING(_A, _B, 1, JC_TEST_C_NON_FATAL)
#define EXPECT_STRNE(_A, _B) JC_TEST_C_ASSERT_STRING(_A, _B, 0, JC_TEST_C_NON_FATAL)
#define EXPECT_NEAR(_A, _B, _EPSILON) JC_TEST_C_ASSERT_NEAR(_A, _B, _EPSILON, JC_TEST_C_NON_FATAL)
#define EXPECT_ARRAY_EQ(_A, _B)                                              \
    do {                                                                      \
        _Static_assert(sizeof(_A) == sizeof(_B), "array sizes must match");   \
        JC_TEST_C_ASSERT_ARRAY(_A, _B, sizeof(_A) / sizeof((_A)[0]),          \
                               sizeof((_A)[0]), JC_TEST_C_NON_FATAL);          \
    } while (0)
#define EXPECT_ARRAY_EQ_LEN(_A, _B, _LENGTH)                                  \
    JC_TEST_C_ASSERT_ARRAY(_A, _B, _LENGTH, sizeof((_A)[0]), JC_TEST_C_NON_FATAL)

#define SKIP() do { jc_test_set_test_skipped(); return; } while (0)
#define SCOPED_TRACE(_MESSAGE) ((void)0)

#if defined(_MSC_VER)
#pragma section(".CRT$XCU", read)
typedef void (__cdecl *jc_test_initializer_func)(void);
#define JC_TEST_C_INITIALIZER(_NAME)                                           \
    static void __cdecl _NAME(void);                                           \
    __declspec(allocate(".CRT$XCU")) static jc_test_initializer_func          \
        JC_TEST_C_JOIN(_NAME, _initializer) = _NAME;                           \
    static void __cdecl _NAME(void)
#elif defined(__GNUC__) || defined(__clang__)
#define JC_TEST_C_INITIALIZER(_NAME)                                           \
    static void _NAME(void) __attribute__((constructor));                      \
    static void _NAME(void)
#else
#error "jc_test automatic registration requires GCC, Clang, or MSVC"
#endif

#define JC_TEST_C_JOIN2(_A, _B) _A##_B
#define JC_TEST_C_JOIN(_A, _B) JC_TEST_C_JOIN2(_A, _B)
#define JC_TEST_C_NAME3(_A, _B, _C) JC_TEST_C_JOIN(JC_TEST_C_JOIN(_A, _B), _C)
#define JC_TEST_C_TEST_NAME(_SUITE, _NAME) JC_TEST_C_NAME3(jc_test_body_##_SUITE, _, _NAME)
#define JC_TEST_C_ENTRY_NAME(_SUITE, _NAME) JC_TEST_C_NAME3(jc_test_entry_##_SUITE, _, _NAME)
#define JC_TEST_C_REGISTER_NAME(_SUITE, _NAME) JC_TEST_C_NAME3(jc_test_register_##_SUITE, _, _NAME)

#define TEST(_SUITE, _NAME)                                                    \
    static void JC_TEST_C_TEST_NAME(_SUITE, _NAME)(void);                      \
    static jc_test_entry JC_TEST_C_ENTRY_NAME(_SUITE, _NAME) = {              \
        NULL, #_SUITE, #_NAME, __FILE__, __LINE__,                             \
        JC_TEST_C_TEST_NAME(_SUITE, _NAME), 0, 0, 0                            \
    };                                                                         \
    JC_TEST_C_INITIALIZER(JC_TEST_C_REGISTER_NAME(_SUITE, _NAME)) {            \
        jc_test_register(&JC_TEST_C_ENTRY_NAME(_SUITE, _NAME));                \
    }                                                                          \
    static void JC_TEST_C_TEST_NAME(_SUITE, _NAME)(void)

#define JC_TEST_C_FIXTURE_SETUP_NAME(_TYPE) JC_TEST_C_JOIN(jc_test_fixture_setup_, _TYPE)
#define JC_TEST_C_FIXTURE_TEARDOWN_NAME(_TYPE) JC_TEST_C_JOIN(jc_test_fixture_teardown_, _TYPE)
#define JC_TEST_C_FIXTURE_BODY_NAME(_TYPE, _NAME) JC_TEST_C_NAME3(jc_test_fixture_body_##_TYPE, _, _NAME)
#define JC_TEST_C_FIXTURE_RUN_NAME(_TYPE, _NAME) JC_TEST_C_NAME3(jc_test_fixture_run_##_TYPE, _, _NAME)

#define JC_TEST_FIXTURE_SETUP(_TYPE)                                           \
    static void JC_TEST_C_FIXTURE_SETUP_NAME(_TYPE)(_TYPE* jc_test_fixture)
#define JC_TEST_FIXTURE_TEARDOWN(_TYPE)                                        \
    static void JC_TEST_C_FIXTURE_TEARDOWN_NAME(_TYPE)(_TYPE* jc_test_fixture)

#define TEST_F(_TYPE, _NAME)                                                   \
    static void JC_TEST_C_FIXTURE_SETUP_NAME(_TYPE)(_TYPE*);                   \
    static void JC_TEST_C_FIXTURE_TEARDOWN_NAME(_TYPE)(_TYPE*);                \
    static void JC_TEST_C_FIXTURE_BODY_NAME(_TYPE, _NAME)(_TYPE*);             \
    static void JC_TEST_C_FIXTURE_RUN_NAME(_TYPE, _NAME)(void) {               \
        _TYPE jc_test_fixture_value;                                           \
        memset(&jc_test_fixture_value, 0, sizeof(jc_test_fixture_value));       \
        JC_TEST_C_FIXTURE_SETUP_NAME(_TYPE)(&jc_test_fixture_value);            \
        if (!jc_test_current_fatal() && !jc_test_current_skipped())             \
            JC_TEST_C_FIXTURE_BODY_NAME(_TYPE, _NAME)(&jc_test_fixture_value); \
        jc_test_clear_fatal();                                                  \
        JC_TEST_C_FIXTURE_TEARDOWN_NAME(_TYPE)(&jc_test_fixture_value);         \
    }                                                                          \
    static jc_test_entry JC_TEST_C_ENTRY_NAME(_TYPE, _NAME) = {               \
        NULL, #_TYPE, #_NAME, __FILE__, __LINE__,                              \
        JC_TEST_C_FIXTURE_RUN_NAME(_TYPE, _NAME), 0, 0, 0                      \
    };                                                                         \
    JC_TEST_C_INITIALIZER(JC_TEST_C_REGISTER_NAME(_TYPE, _NAME)) {             \
        jc_test_register(&JC_TEST_C_ENTRY_NAME(_TYPE, _NAME));                 \
    }                                                                          \
    static void JC_TEST_C_FIXTURE_BODY_NAME(_TYPE, _NAME)(_TYPE* jc_test_fixture)

#if !defined(JC_TEST_NO_DEATH_TEST)
extern jmp_buf jc_test_death_jump_buffer;
void jc_test_begin_death_test(void);
void jc_test_end_death_test(void);
void jc_test_assert_death_failed(const char* statement, const char* file,
                                 int line, int fatal);
#define JC_TEST_C_ASSERT_DEATH(_STATEMENT, _REGEX, _FATAL)                     \
    do {                                                                       \
        (void)sizeof(_REGEX);                                                  \
        jc_test_begin_death_test();                                            \
        if (setjmp(jc_test_death_jump_buffer) == 0) {                          \
            _STATEMENT;                                                       \
            jc_test_end_death_test();                                         \
            jc_test_assert_death_failed(#_STATEMENT, __FILE__, __LINE__,       \
                                        (_FATAL));                             \
            if ((_FATAL) && jc_test_current_fatal()) return;                   \
        } else {                                                               \
            jc_test_end_death_test();                                         \
        }                                                                      \
    } while (0)
#else
#define JC_TEST_C_ASSERT_DEATH(_STATEMENT, _REGEX, _FATAL) ((void)0)
#endif

#define ASSERT_DEATH(_STATEMENT, _REGEX) JC_TEST_C_ASSERT_DEATH(_STATEMENT, _REGEX, JC_TEST_C_FATAL)
#define EXPECT_DEATH(_STATEMENT, _REGEX) JC_TEST_C_ASSERT_DEATH(_STATEMENT, _REGEX, JC_TEST_C_NON_FATAL)

#if defined(JC_TEST_USE_DEFAULT_MAIN)
#define JC_TEST_IMPLEMENTATION
#endif

#if defined(JC_TEST_IMPLEMENTATION)

#if !defined(JC_TEST_FAILURE_MALLOC)
#define JC_TEST_FAILURE_MALLOC malloc
#endif
#if !defined(JC_TEST_FAILURE_REALLOC)
#define JC_TEST_FAILURE_REALLOC realloc
#endif
#if !defined(JC_TEST_FAILURE_FREE)
#define JC_TEST_FAILURE_FREE free
#endif

typedef struct jc_test_failure {
    struct jc_test_failure* next;
    char* test_name;
    const char* file;
    int line;
    char* message;
} jc_test_failure;

#if defined(_MSC_VER)
#define JC_TEST_C_VA_COPY(_DST, _SRC) ((_DST) = (_SRC))
#else
#define JC_TEST_C_VA_COPY(_DST, _SRC) va_copy((_DST), (_SRC))
#endif

typedef struct jc_test_c_state {
    jc_test_entry* first;
    jc_test_entry* last;
    jc_test_entry* current;
    jc_test_failure* failures;
    jc_test_failure* failures_last;
    char** filters;
    size_t num_filters;
    size_t filters_capacity;
    size_t dropped_failures;
    jc_test_stats stats;
    int current_fatal;
    int use_colors;
    int break_on_failure;
} jc_test_c_state;

static jc_test_c_state jc_test_c_global_state;

#if !defined(JC_TEST_OUTPUT_FN)
#define JC_TEST_C_DEFAULT_OUTPUT 1
static void jc_test_c_default_output(const char* text, size_t length) {
#if defined(JC_TEST_USE_PRINTF)
    (void)length;
    (void)printf("%s", text);
#else
    (void)fwrite(text, 1, length, stdout);
#endif
}

#define JC_TEST_OUTPUT_FN jc_test_c_default_output
#endif

#if !defined(JC_TEST_FLUSH_OUTPUT)
#if defined(JC_TEST_C_DEFAULT_OUTPUT)
#define JC_TEST_FLUSH_OUTPUT() ((void)fflush(stdout))
#else
#define JC_TEST_FLUSH_OUTPUT() ((void)0)
#endif
#endif

static void jc_test_c_write(const char* text) {
    JC_TEST_OUTPUT_FN(text, strlen(text));
}

static void jc_test_c_writef(const char* format, ...) {
    char buffer[1024];
    int count;
    va_list args;
    va_start(args, format);
    count = vsnprintf(buffer, sizeof(buffer), format, args);
    va_end(args);
    if (count < 0) return;
    if ((size_t)count < sizeof(buffer)) {
        JC_TEST_OUTPUT_FN(buffer, (size_t)count);
    } else {
        char* dynamic_buffer = (char*)malloc((size_t)count + 1);
        if (!dynamic_buffer) return;
        va_start(args, format);
        (void)vsnprintf(dynamic_buffer, (size_t)count + 1, format, args);
        va_end(args);
        JC_TEST_OUTPUT_FN(dynamic_buffer, (size_t)count);
        free(dynamic_buffer);
    }
}

static const char* jc_test_c_color(const char* code) {
    return jc_test_c_global_state.use_colors ? code : "";
}

static char* jc_test_c_strdup(const char* text) {
    size_t length = strlen(text) + 1;
    char* copy = (char*)malloc(length);
    if (copy) memcpy(copy, text, length);
    return copy;
}

static char* jc_test_c_failure_strdup(const char* text) {
    size_t length = strlen(text) + 1;
    char* copy = (char*)JC_TEST_FAILURE_MALLOC(length);
    if (copy) memcpy(copy, text, length);
    return copy;
}

static char* jc_test_c_vformat(const char* format, va_list args) {
    size_t capacity = 256;
    char* buffer = NULL;
    for (;;) {
        int count;
        char* grown = (char*)JC_TEST_FAILURE_REALLOC(buffer, capacity);
        va_list copy;
        if (!grown) {
            JC_TEST_FAILURE_FREE(buffer);
            return NULL;
        }
        buffer = grown;
        JC_TEST_C_VA_COPY(copy, args);
        count = vsnprintf(buffer, capacity, format, copy);
        va_end(copy);
        if (count >= 0 && (size_t)count < capacity) return buffer;
        capacity = count >= 0 ? (size_t)count + 1 : capacity * 2;
    }
}

static void jc_test_c_full_name(char* buffer, size_t capacity,
                                const jc_test_entry* test) {
    (void)JC_TEST_SNPRINTF(buffer, capacity, "%s.%s",
                           test ? test->suite_name : "<no test>",
                           test ? test->test_name : "<unknown>");
}

static void jc_test_c_record_failure(const char* file, int line,
                                     const char* format, ...) {
    jc_test_failure* failure;
    char full_name[512];
    char* message;
    va_list args;
    va_start(args, format);
    message = jc_test_c_vformat(format, args);
    va_end(args);

    jc_test_c_full_name(full_name, sizeof(full_name), jc_test_c_global_state.current);
    if (message) {
        jc_test_c_writef("\n%s:%d:%s\n", file, line, message);
    } else {
        jc_test_c_writef("\n%s:%d: assertion failed (message unavailable)\n", file, line);
    }
    JC_TEST_FLUSH_OUTPUT();

    failure = (jc_test_failure*)JC_TEST_FAILURE_MALLOC(sizeof(*failure));
    if (!failure || !message) {
        JC_TEST_FAILURE_FREE(failure);
        JC_TEST_FAILURE_FREE(message);
        ++jc_test_c_global_state.dropped_failures;
        return;
    }
    failure->test_name = jc_test_c_failure_strdup(full_name);
    if (!failure->test_name) {
        JC_TEST_FAILURE_FREE(message);
        JC_TEST_FAILURE_FREE(failure);
        ++jc_test_c_global_state.dropped_failures;
        return;
    }
    failure->next = NULL;
    failure->file = file;
    failure->line = line;
    failure->message = message;
    if (jc_test_c_global_state.failures_last)
        jc_test_c_global_state.failures_last->next = failure;
    else
        jc_test_c_global_state.failures = failure;
    jc_test_c_global_state.failures_last = failure;
}

static void jc_test_c_fail(int fatal) {
    jc_test_c_global_state.current->fail = 1;
    jc_test_c_global_state.current_fatal |= fatal;
    if (jc_test_c_global_state.break_on_failure) JC_TEST_DBG_BREAK();
}

int jc_test_current_fatal(void) {
    return jc_test_c_global_state.current_fatal;
}

void jc_test_clear_fatal(void) {
    jc_test_c_global_state.current_fatal = 0;
}

int jc_test_current_skipped(void) {
    return jc_test_c_global_state.current && jc_test_c_global_state.current->skipped;
}

void jc_test_set_test_skipped(void) {
    if (jc_test_c_global_state.current) jc_test_c_global_state.current->skipped = 1;
}

void jc_test_register(jc_test_entry* test) {
    test->next = NULL;
    if (jc_test_c_global_state.last)
        jc_test_c_global_state.last->next = test;
    else
        jc_test_c_global_state.first = test;
    jc_test_c_global_state.last = test;
}

static int jc_test_c_is_float(jc_test_value value) {
    return value.kind == JC_TEST_VALUE_FLOAT ||
           value.kind == JC_TEST_VALUE_DOUBLE ||
           value.kind == JC_TEST_VALUE_LONG_DOUBLE;
}

static long double jc_test_c_as_long_double(jc_test_value value) {
    if (jc_test_c_is_float(value)) return value.data.float_value;
    if (value.kind == JC_TEST_VALUE_SIGNED) return (long double)value.data.signed_value;
    return (long double)value.data.unsigned_value;
}

static uint32_t jc_test_c_float_bits(float value) {
    uint32_t bits;
    memcpy(&bits, &value, sizeof(bits));
    return bits;
}

static uint64_t jc_test_c_double_bits(double value) {
    uint64_t bits;
    memcpy(&bits, &value, sizeof(bits));
    return bits;
}

static int jc_test_c_float_equal(float a, float b) {
    uint32_t ua = jc_test_c_float_bits(a);
    uint32_t ub = jc_test_c_float_bits(b);
    uint32_t ba = (ua & 0x80000000U) ? ~ua + 1U : ua | 0x80000000U;
    uint32_t bb = (ub & 0x80000000U) ? ~ub + 1U : ub | 0x80000000U;
    uint32_t distance;
    if (a != a || b != b) return 0;
    if (a == b) return 1;
    if (a > FLT_MAX || a < -FLT_MAX || b > FLT_MAX || b < -FLT_MAX) return 0;
    distance = ba > bb ? ba - bb : bb - ba;
    return distance <= 4U;
}

static int jc_test_c_double_equal(double a, double b) {
    uint64_t ua = jc_test_c_double_bits(a);
    uint64_t ub = jc_test_c_double_bits(b);
    uint64_t ba = (ua & UINT64_C(0x8000000000000000)) ? ~ua + 1U : ua | UINT64_C(0x8000000000000000);
    uint64_t bb = (ub & UINT64_C(0x8000000000000000)) ? ~ub + 1U : ub | UINT64_C(0x8000000000000000);
    uint64_t distance;
    if (a != a || b != b) return 0;
    if (a == b) return 1;
    if (a > DBL_MAX || a < -DBL_MAX || b > DBL_MAX || b < -DBL_MAX) return 0;
    distance = ba > bb ? ba - bb : bb - ba;
    return distance <= 4U;
}

static int jc_test_c_compare_integer(jc_test_value a, jc_test_value b) {
    if (a.kind == JC_TEST_VALUE_SIGNED && b.kind == JC_TEST_VALUE_SIGNED)
        return (a.data.signed_value > b.data.signed_value) -
               (a.data.signed_value < b.data.signed_value);
    if (a.kind == JC_TEST_VALUE_UNSIGNED && b.kind == JC_TEST_VALUE_UNSIGNED)
        return (a.data.unsigned_value > b.data.unsigned_value) -
               (a.data.unsigned_value < b.data.unsigned_value);
    if (a.kind == JC_TEST_VALUE_SIGNED) {
        if (a.bits > b.bits) {
            intmax_t bs = (intmax_t)b.data.unsigned_value;
            return (a.data.signed_value > bs) - (a.data.signed_value < bs);
        }
        {
            uintmax_t mask = UINTMAX_MAX;
            uintmax_t au;
            if (b.bits < (unsigned int)(sizeof(uintmax_t) * CHAR_BIT))
                mask = (UINTMAX_C(1) << b.bits) - UINTMAX_C(1);
            au = (uintmax_t)a.data.signed_value & mask;
            return (au > b.data.unsigned_value) - (au < b.data.unsigned_value);
        }
    }
    return -jc_test_c_compare_integer(b, a);
}

static int jc_test_c_compare_values(jc_test_value a, jc_test_value b, int operation) {
    int comparison = 0;
    if (a.kind == JC_TEST_VALUE_POINTER || b.kind == JC_TEST_VALUE_POINTER) {
        int equal;
        if (a.kind == JC_TEST_VALUE_POINTER && b.kind == JC_TEST_VALUE_POINTER)
            equal = a.data.pointer_value == b.data.pointer_value;
        else if (a.kind == JC_TEST_VALUE_POINTER && b.kind != JC_TEST_VALUE_POINTER)
            equal = a.data.pointer_value == NULL &&
                    !jc_test_c_is_float(b) &&
                    ((b.kind == JC_TEST_VALUE_SIGNED && b.data.signed_value == 0) ||
                     (b.kind == JC_TEST_VALUE_UNSIGNED && b.data.unsigned_value == 0));
        else
            equal = b.data.pointer_value == NULL &&
                    !jc_test_c_is_float(a) &&
                    ((a.kind == JC_TEST_VALUE_SIGNED && a.data.signed_value == 0) ||
                     (a.kind == JC_TEST_VALUE_UNSIGNED && a.data.unsigned_value == 0));
        return operation == JC_TEST_COMPARE_EQ ? equal : !equal;
    }
    if (jc_test_c_is_float(a) || jc_test_c_is_float(b)) {
        long double av = jc_test_c_as_long_double(a);
        long double bv = jc_test_c_as_long_double(b);
        int equal;
        if (a.kind == JC_TEST_VALUE_LONG_DOUBLE || b.kind == JC_TEST_VALUE_LONG_DOUBLE) {
            equal = av == bv;
        }
        else if (a.kind == JC_TEST_VALUE_DOUBLE || b.kind == JC_TEST_VALUE_DOUBLE) {
            double converted_a = (double)av;
            double converted_b = (double)bv;
            av = (long double)converted_a;
            bv = (long double)converted_b;
            equal = jc_test_c_double_equal(converted_a, converted_b);
        }
        else {
            float converted_a = (float)av;
            float converted_b = (float)bv;
            av = (long double)converted_a;
            bv = (long double)converted_b;
            equal = jc_test_c_float_equal(converted_a, converted_b);
        }
        if (operation == JC_TEST_COMPARE_EQ) return equal;
        if (operation == JC_TEST_COMPARE_NE) return !equal;
        comparison = (av > bv) - (av < bv);
    } else {
        comparison = jc_test_c_compare_integer(a, b);
    }
    switch (operation) {
        case JC_TEST_COMPARE_EQ: return comparison == 0;
        case JC_TEST_COMPARE_NE: return comparison != 0;
        case JC_TEST_COMPARE_LT: return comparison < 0;
        case JC_TEST_COMPARE_GT: return comparison > 0;
        case JC_TEST_COMPARE_LE: return comparison <= 0;
        case JC_TEST_COMPARE_GE: return comparison >= 0;
        default: return 0;
    }
}

static void jc_test_c_format_value(char* buffer, size_t capacity, jc_test_value value) {
    switch (value.kind) {
        case JC_TEST_VALUE_SIGNED:
            (void)JC_TEST_SNPRINTF(buffer, capacity, "%" PRIdMAX, value.data.signed_value);
            break;
        case JC_TEST_VALUE_UNSIGNED:
            (void)JC_TEST_SNPRINTF(buffer, capacity, "%" PRIuMAX, value.data.unsigned_value);
            break;
        case JC_TEST_VALUE_FLOAT:
        case JC_TEST_VALUE_DOUBLE:
            (void)JC_TEST_SNPRINTF(buffer, capacity, "%g", (double)value.data.float_value);
            break;
        case JC_TEST_VALUE_LONG_DOUBLE:
            (void)JC_TEST_SNPRINTF(buffer, capacity, "%Lg", value.data.float_value);
            break;
        case JC_TEST_VALUE_POINTER:
            (void)JC_TEST_SNPRINTF(buffer, capacity, "%p", value.data.pointer_value);
            break;
    }
}

void jc_test_assert_boolean(int value, int expected, const char* expression,
                            const char* file, int line, int fatal) {
    ++jc_test_c_global_state.stats.num_assertions;
    if (!!value == !!expected) return;
    jc_test_c_record_failure(file, line,
        "\nValue of: %s\nExpected: %s\n  Actual: %s",
        expression, expected ? "true" : "false", value ? "true" : "false");
    jc_test_c_fail(fatal);
}

void jc_test_assert_compare(jc_test_value a, jc_test_value b, int operation,
                            const char* expression_a, const char* expression_b,
                            const char* file, int line, int fatal) {
    static const char* operators[] = { "==", "!=", "<", ">", "<=", ">=" };
    char value_a[96];
    char value_b[96];
    ++jc_test_c_global_state.stats.num_assertions;
    if (jc_test_c_compare_values(a, b, operation)) return;
    jc_test_c_format_value(value_a, sizeof(value_a), a);
    jc_test_c_format_value(value_b, sizeof(value_b), b);
    jc_test_c_record_failure(file, line,
        "\nExpected: (%s) %s (%s), actual: %s vs %s",
        expression_a, operators[operation], expression_b, value_a, value_b);
    jc_test_c_fail(fatal);
}

static int jc_test_c_strings_equal(const char* a, const char* b) {
    if (!a || !b) return a == b;
    return strcmp(a, b) == 0;
}

void jc_test_assert_string(const char* a, const char* b, int equal,
                           const char* expression_a, const char* expression_b,
                           const char* file, int line, int fatal) {
    int matches = jc_test_c_strings_equal(a, b);
    ++jc_test_c_global_state.stats.num_assertions;
    if (matches == equal) return;
    jc_test_c_record_failure(file, line,
        "\nExpected: (%s) %s (%s), actual: \"%s\" vs \"%s\"",
        expression_a, equal ? "==" : "!=", expression_b,
        a ? a : "(null)", b ? b : "(null)");
    jc_test_c_fail(fatal);
}

void jc_test_assert_near(long double a, long double b, long double epsilon,
                         const char* expression_a, const char* expression_b,
                         const char* expression_epsilon,
                         const char* file, int line, int fatal) {
    long double difference = a > b ? a - b : b - a;
    ++jc_test_c_global_state.stats.num_assertions;
    if (difference <= epsilon) return;
    jc_test_c_record_failure(file, line,
        "\nValue of: abs(%s - %s) <= %s\n  Actual: abs(%Lg - %Lg) == %Lg",
        expression_a, expression_b, expression_epsilon, a, b, difference);
    jc_test_c_fail(fatal);
}

void jc_test_assert_array(const void* a, const void* b, size_t length,
                          size_t element_size, const char* expression_a,
                          const char* expression_b,
                          const char* file, int line, int fatal) {
    size_t size = length * element_size;
    size_t index;
    const unsigned char* bytes_a = (const unsigned char*)a;
    const unsigned char* bytes_b = (const unsigned char*)b;
    ++jc_test_c_global_state.stats.num_assertions;
    if (size == 0 || memcmp(a, b, size) == 0) return;
    for (index = 0; index < size && bytes_a[index] == bytes_b[index]; ++index) {}
    jc_test_c_record_failure(file, line,
        "\nValue of: %s == %s\nIndex: %zu\nExpected byte: 0x%02X\n  Actual byte: 0x%02X",
        expression_a, expression_b, index / element_size,
        (unsigned int)bytes_a[index], (unsigned int)bytes_b[index]);
    jc_test_c_fail(fatal);
}

#if !defined(JC_TEST_NO_DEATH_TEST)
jmp_buf jc_test_death_jump_buffer;
typedef void (*jc_test_c_signal_func)(int);
static jc_test_c_signal_func jc_test_c_previous_signals[4];

static void jc_test_c_signal_handler(int signal_number) {
    (void)signal_number;
    longjmp(jc_test_death_jump_buffer, 1);
}

void jc_test_begin_death_test(void) {
    ++jc_test_c_global_state.stats.num_assertions;
    jc_test_c_previous_signals[0] = signal(SIGABRT, jc_test_c_signal_handler);
    jc_test_c_previous_signals[1] = signal(SIGFPE, jc_test_c_signal_handler);
    jc_test_c_previous_signals[2] = signal(SIGILL, jc_test_c_signal_handler);
    jc_test_c_previous_signals[3] = signal(SIGSEGV, jc_test_c_signal_handler);
}

void jc_test_end_death_test(void) {
    (void)signal(SIGABRT, jc_test_c_previous_signals[0]);
    (void)signal(SIGFPE, jc_test_c_previous_signals[1]);
    (void)signal(SIGILL, jc_test_c_previous_signals[2]);
    (void)signal(SIGSEGV, jc_test_c_previous_signals[3]);
}

void jc_test_assert_death_failed(const char* statement, const char* file,
                                 int line, int fatal) {
    jc_test_c_record_failure(file, line, "\nExpected this to fail: %s", statement);
    jc_test_c_fail(fatal);
}
#endif

#if defined(JC_TEST_C_DEFAULT_TIMING)
jc_test_time_t jc_test_get_time(void) {
#if defined(_WIN32)
    LARGE_INTEGER counter;
    LARGE_INTEGER frequency;
    QueryPerformanceCounter(&counter);
    QueryPerformanceFrequency(&frequency);
    return (jc_test_time_t)((counter.QuadPart * 1000000) / frequency.QuadPart);
#else
    struct timeval value;
    gettimeofday(&value, NULL);
    return (jc_test_time_t)value.tv_sec * UINT64_C(1000000) + (jc_test_time_t)value.tv_usec;
#endif
}
#endif

static int jc_test_c_wildcard_match(const char* pattern, const char* text) {
    const char* star = NULL;
    const char* retry = NULL;
    while (*text) {
        if (*pattern == '*') {
            star = pattern++;
            retry = text;
        } else if (*pattern == *text) {
            ++pattern;
            ++text;
        } else if (star) {
            pattern = star + 1;
            text = ++retry;
        } else {
            return 0;
        }
    }
    while (*pattern == '*') ++pattern;
    return *pattern == '\0';
}

static int jc_test_c_keep_test(const char* name) {
    size_t index;
    if (jc_test_c_global_state.num_filters == 0) return 1;
    for (index = 0; index < jc_test_c_global_state.num_filters; ++index) {
        const char* pattern = jc_test_c_global_state.filters[index];
        if (strchr(pattern, '*')) {
            if (jc_test_c_wildcard_match(pattern, name)) return 1;
        } else if (strstr(name, pattern)) {
            return 1;
        }
    }
    return 0;
}

static int jc_test_c_add_filter(const char* pattern) {
    char* copy;
    if (jc_test_c_global_state.num_filters == jc_test_c_global_state.filters_capacity) {
        size_t capacity = jc_test_c_global_state.filters_capacity ?
                          jc_test_c_global_state.filters_capacity * 2 : 8;
        char** filters = (char**)realloc(jc_test_c_global_state.filters,
                                        capacity * sizeof(*filters));
        if (!filters) return 0;
        jc_test_c_global_state.filters = filters;
        jc_test_c_global_state.filters_capacity = capacity;
    }
    copy = jc_test_c_strdup(pattern);
    if (!copy) return 0;
    jc_test_c_global_state.filters[jc_test_c_global_state.num_filters++] = copy;
    return 1;
}

static void jc_test_c_remove_args(int* argc, char** argv, int index, int count) {
    int cursor;
    for (cursor = index + count; cursor < *argc; ++cursor)
        argv[cursor - count] = argv[cursor];
    *argc -= count;
}

void jc_test_init(int* argc, char** argv) {
    int index = 1;
#if defined(JC_TEST_USE_COLORS)
    jc_test_c_global_state.use_colors = JC_TEST_USE_COLORS;
#elif defined(_WIN32)
    jc_test_c_global_state.use_colors = _isatty(1) ? 1 : 0;
#else
    jc_test_c_global_state.use_colors = isatty(1) ? 1 : 0;
#endif
    jc_test_c_global_state.break_on_failure = JCT_IS_DEBUGGER_ATTACHED() ? 1 : 0;
    while (index < *argc) {
        const char* argument = argv[index];
        const char* pattern = NULL;
        int remove_count = 0;
        if (strcmp(argument, "--test-filter") == 0) {
            if (index + 1 >= *argc) {
                jc_test_c_write("jc_test: --test-filter requires a pattern\n");
                JC_TEST_EXIT(1);
            }
            pattern = argv[index + 1];
            remove_count = 2;
        } else if (strncmp(argument, "--test-filter=", 14) == 0) {
            pattern = argument + 14;
            remove_count = 1;
        } else if (strncmp(argument, "--filter=", 9) == 0) {
            pattern = argument + 9;
            remove_count = 1;
        } else if (strcmp(argument, "--test-break-on-fail") == 0) {
            jc_test_c_global_state.break_on_failure = 1;
            remove_count = 1;
        }
        if (pattern && !jc_test_c_add_filter(pattern)) {
            jc_test_c_write("jc_test: unable to store test filter\n");
            JC_TEST_EXIT(1);
        }
        if (remove_count)
            jc_test_c_remove_args(argc, argv, index, remove_count);
        else
            ++index;
    }
}

static void jc_test_c_print_failures(void) {
    jc_test_failure* failure = jc_test_c_global_state.failures;
    if (!failure && jc_test_c_global_state.dropped_failures == 0) return;
    jc_test_c_write("\nFailures:\n");
    while (failure) {
        jc_test_c_writef("\n%s\n%s:%d:%s\n",
                         failure->test_name, failure->file,
                         failure->line, failure->message);
        failure = failure->next;
    }
    if (jc_test_c_global_state.dropped_failures)
        jc_test_c_writef("\n%zu failure detail(s) could not be retained.\n",
                         jc_test_c_global_state.dropped_failures);
}

static void jc_test_c_cleanup(void) {
    size_t index;
    jc_test_failure* failure = jc_test_c_global_state.failures;
    while (failure) {
        jc_test_failure* next = failure->next;
        JC_TEST_FAILURE_FREE(failure->test_name);
        JC_TEST_FAILURE_FREE(failure->message);
        JC_TEST_FAILURE_FREE(failure);
        failure = next;
    }
    for (index = 0; index < jc_test_c_global_state.num_filters; ++index)
        free(jc_test_c_global_state.filters[index]);
    free(jc_test_c_global_state.filters);
}

int jc_test_run_all(void) {
    jc_test_entry* test;
    int result;
    memset(&jc_test_c_global_state.stats, 0, sizeof(jc_test_c_global_state.stats));
    for (test = jc_test_c_global_state.first; test; test = test->next) {
        char full_name[512];
        jc_test_time_t start;
        if (!jc_test_c_keep_test((jc_test_c_full_name(full_name, sizeof(full_name), test), full_name))) {
            test->skipped = 1;
            ++jc_test_c_global_state.stats.num_skipped;
            continue;
        }
        jc_test_c_global_state.current = test;
        jc_test_c_global_state.current_fatal = 0;
        test->fail = 0;
        test->skipped = 0;
        jc_test_c_writef("%s%s%s\n", jc_test_c_color("\x1b[36m"), full_name,
                         jc_test_c_color("\x1b[0m"));
        start = JC_TEST_TIMING_FUNC();
        test->run();
        test->time = JC_TEST_TIMING_FUNC() - start;
        ++jc_test_c_global_state.stats.num_tests;
        jc_test_c_global_state.stats.totaltime += test->time;
        if (test->skipped) {
            ++jc_test_c_global_state.stats.num_skipped;
            jc_test_c_writef("%s %sSKIPPED%s (%llu us)\n", full_name,
                             jc_test_c_color("\x1b[36m"), jc_test_c_color("\x1b[0m"),
                             (unsigned long long)test->time);
        } else if (test->fail) {
            ++jc_test_c_global_state.stats.num_fail;
            jc_test_c_writef("%s %sFAIL%s (%llu us)\n", full_name,
                             jc_test_c_color("\x1b[31m"), jc_test_c_color("\x1b[0m"),
                             (unsigned long long)test->time);
        } else {
            ++jc_test_c_global_state.stats.num_pass;
            jc_test_c_writef("%s %sPASS%s (%llu us)\n", full_name,
                             jc_test_c_color("\x1b[32m"), jc_test_c_color("\x1b[0m"),
                             (unsigned long long)test->time);
        }
    }
    jc_test_c_global_state.current = NULL;
    jc_test_c_print_failures();
    jc_test_c_writef("\nRan %d tests, with %d assertions in %llu us\n",
                     jc_test_c_global_state.stats.num_tests,
                     jc_test_c_global_state.stats.num_assertions,
                     (unsigned long long)jc_test_c_global_state.stats.totaltime);
    jc_test_c_writef("%d tests passed, %d skipped and %d tests %s\n",
                     jc_test_c_global_state.stats.num_pass,
                     jc_test_c_global_state.stats.num_skipped,
                     jc_test_c_global_state.stats.num_fail,
                     jc_test_c_global_state.stats.num_fail ? "FAILED" : "failed");
    JC_TEST_FLUSH_OUTPUT();
    result = jc_test_c_global_state.stats.num_fail;
    jc_test_c_cleanup();
    return result;
}

#endif /* JC_TEST_IMPLEMENTATION */

#if defined(JC_TEST_USE_DEFAULT_MAIN)
int main(int argc, char** argv) {
    jc_test_init(&argc, argv);
    return jc_test_run_all();
}
#endif

#endif /* __cplusplus */

#endif /* JC_TEST_C_DISPATCH_H */
