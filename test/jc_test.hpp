/* jc_test.hpp    Copyright 2018-2026 Mathias Westerdahl
 *
 * https://github.com/JCash/jctest
 * https://jcash.github.io/jctest
 *
 * BRIEF:
 *
 *      A small, single header only C++11 test framework
 *
 * DISCLAIMER:
 *
 *      This software is supplied "AS IS" without any warranties and support
 *
 * LICENSE:
 *     The MIT License (MIT)
 *     Copyright (c) 2018-2026 Mathias Westerdahl
 *     (For full text, see bottom of document)
 *
 * USAGE:
 *      For more use cases, see end of document
 */

#ifndef JC_TEST_HPP
#define JC_TEST_HPP

#if defined(_MSC_VER)
    #if _MSC_VER < 1900
        #error "jc_test.hpp requires C++11 or newer"
    #endif
#elif __cplusplus < 201103L
    #error "jc_test.hpp requires C++11 or newer"
#endif

// ***************************************************************************************
// PUBLIC API

// May modify the argument list, to remove the test specific arguments
extern void jc_test_init(int* argc, char** argv);

// Runs all registered tests
extern int jc_test_run_all();

// The standard test class
struct jc_test_base_class {
    virtual ~jc_test_base_class();
    static void SetUpTestCase() {}      // The UserClass::SetUpTestCase is called before each test case runs
    static void TearDownTestCase() {}   // The UserClass::TearDownTestCase is called after all tests have run
    virtual void SetUp();               // Called before each test
    virtual void TearDown();            // Called after each test
    virtual void TestBody() = 0;        // Implemented by TEST_F and TEST_P
private:
    struct Setup_should_be_spelled_SetUp {};
    virtual Setup_should_be_spelled_SetUp* Setup(); // Trick from GTEST to make sure users don't accidentally misspell the function
};

// A parameterized test class, to use with TEST_P and INSTANTIATE_TEST_CASE_P
template<typename ParamType>
struct jc_test_params_class : public jc_test_base_class {
    typedef ParamType param_t;
    jc_test_params_class() {}
    static const ParamType&    GetParam()                           { return *param; }
    static void                SetParam(const ParamType* _param)    { param = _param; }
    static const ParamType* param;
};

// ***************************************************************************************
// TEST API

// Smallest test case:
//
// #define JC_TEST_IMPLEMENTATION
// #include <jc_test.hpp>
//
// TEST(FixtureName, TestName) {
//     ASSERT_EQ(4, 2*2);
// }
//
// int main(int argc, char** argv) {
//     jc_test_init(&argc, argv);
//     return jc_test_run_all();
// }

// Basic test
// #define TEST(testfixture,testfn)
//
// Basic tests using a user defined fixture class (jc_test_base_class)
// #define TEST_F(testfixture,testfn)
//
// Parameterized tests using a user defined fixture class (jc_test_params_class<T>)
// #define TEST_P(testfixture,testfn)
//
// Instantiation of parameterisaed test
// #define INSTANTIATE_TEST_CASE_P(prefix,testfixture,testvalues)

// ***************************************************************************************
// ASSERTION API

// #define SKIP()                           Skips the test

// Fatal failures are prefixed ASSERT_
// Non fatal failures are prefixed EXPECT_

// #define ASSERT_TRUE( VALUE )             value
// #define ASSERT_FALSE( VALUE )            !value
// #define ASSERT_EQ( A, B )                A == B
// #define ASSERT_NE( A, B )                A != B
// #define ASSERT_LT( A, B )                A <  B
// #define ASSERT_GT( A, B )                A >  B
// #define ASSERT_LE( A, B )                A <= B
// #define ASSERT_GE( A, B )                A >= B
// #define ASSERT_STREQ( A, B )             strcmp(A,B) == 0
// #define ASSERT_STRNE( A, B )             strcmp(A,B) != 0
// #define ASSERT_NEAR( A, B, EPSILON )     abs(a - b) < epsilon
// #define ASSERT_DEATH(S, RE)
// #define ASSERT_ARRAY_EQ( A, B )              memcmp(A, B, sizeof(A)) == 0
// #define ASSERT_ARRAY_EQ_LEN( A, B, LENGTH)   memcmp(A, B, LENGTH) == 0

// #define SCOPED_TRACE(_MSG)               // nop


// ***************************************************************************************
// Possible modifications for the included files

 #include <string.h> // memcpy

#if defined(_MSC_VER)
    #include <Windows.h>
#endif

// Can be used to override the logging entirely (e.g. for writing html output)
#ifndef JC_TEST_LOGGER_CLASS
    #include <stdarg.h> //va_list
    // Can be overridden to log in a different way
    #define JC_TEST_LOGGER_CLASS jc_test_print_logger
#endif

#ifndef JC_TEST_SNPRINTF
    #include <stdio.h>  //snprintf
    #if defined(_MSC_VER)
        #define JC_TEST_SNPRINTF _snprintf
    #else
        #define JC_TEST_SNPRINTF snprintf
    #endif
#endif

#ifndef JC_TEST_ASSERT_FN
    #include <assert.h>
    #define JC_TEST_ASSERT_FN assert
#endif

#ifndef JC_TEST_EXIT
    #include <stdlib.h>
    #define JC_TEST_EXIT exit
#endif

#ifndef JC_TEST_NO_DEATH_TEST
    #include <signal.h>
    #include <setjmp.h>
#if defined(_WIN32) || defined(__CYGWIN__) || defined(__EMSCRIPTEN__)
    typedef jmp_buf jc_test_jmp_buf;
    #if defined(__EMSCRIPTEN__) || defined(__MINGW32__)
        #define JC_TEST_SETJMP setjmp
    #else
        #define JC_TEST_SETJMP _setjmp
    #endif
    #define JC_TEST_LONGJMP longjmp
#else
    typedef sigjmp_buf jc_test_jmp_buf;
    // Restore the signal mask when a death test jumps out of its handler.
    #define JC_TEST_SETJMP(env) sigsetjmp((env), 1)
    #define JC_TEST_LONGJMP siglongjmp
#endif
#endif

#ifndef JC_TEST_DBG_BREAK
    #if defined(_MSC_VER)
        #include <intrin.h>
        #define JC_TEST_DBG_BREAK() __debugbreak()
    #elif __has_builtin(__builtin_debugtrap)
        #define JC_TEST_DBG_BREAK() __builtin_trap()
    #else
        #include <stdlib.h>
        #define JC_TEST_DBG_BREAK() abort()
    #endif
#endif

#include <type_traits> // painful

#if !defined(_MSC_VER)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
    #pragma GCC diagnostic ignored "-Wold-style-cast"
    #pragma GCC diagnostic ignored "-Wformat-nonliteral"
#endif

#if defined(__GNUC__) || defined(__clang__)
    #define JC_TEST_UNUSED __attribute__ ((unused))
#else
    #define JC_TEST_UNUSED
#endif

#if !defined(JC_TEST_NO_STDINT_H)
    #include <stdint.h>
#endif

#if !defined(JC_FMT_U64)
    #if defined(__has_include)
        #if __has_include(<inttypes.h>)
            #include <inttypes.h>
        #endif
    #endif

    #if !defined(PRId64)
        #if defined(_MSC_VER)
            #define PRId64 "I64d"
            #define PRIi64 "I64i"
            #define PRIu64 "I64u"
            #define PRIx64 "I64x"
        #else
            #define PRIu64 "llu"
            #define PRIx64 "lld"
        #endif
    #endif

    #define JC_FMT_U64 "%" PRIu64
    #define JC_FMT_I64 "%" PRId64
#endif

#if defined(__x86_64__) || defined(__arm64) || defined(__aarch64__) || defined(__ppc64__) || defined(_WIN64)
    #define JC_TEST_64BIT
#endif

#ifndef JC_TEST_TIMING_FUNC
    #define JC_TEST_TIMING_FUNC jc_test_get_time // returns micro seconds

    typedef unsigned long jc_test_time_t;
    extern jc_test_time_t jc_test_get_time(void);
#endif

// Returns the user defined context for the fixture
typedef void* (*jc_test_fixture_setup_func)();

struct jc_test_factory_base_interface;
typedef void (*jc_test_void_staticfunc)();
typedef void (jc_test_base_class::*jc_test_void_memberfunc)();

typedef struct jc_test_entry {
    jc_test_entry*            next;       // linked list
    const char*               name;
    jc_test_base_class*       instance;
    jc_test_factory_base_interface* factory;    // Factory for parameterized tests
    jc_test_time_t            time;       // The time spent in this test
    uint32_t                  fail:1;
    uint32_t                  skipped:1;
    uint32_t                  :30;
    #if defined(JC_TEST_64BIT)
    uint32_t                  :32;
    #endif
} jc_test_entry;

typedef struct jc_test_stats {
    int num_pass;
    int num_fail:16;
    int num_skipped:16;
    int num_assertions;
    int num_tests;
    jc_test_time_t totaltime;
} jc_test_stats;

typedef struct jc_test_failure {
    struct jc_test_failure* next;
    char* test_name;
    const char* filename;
    char* message;
    int line;
    int _pad;
} jc_test_failure;

typedef struct jc_test_fixture {
    virtual ~jc_test_fixture();
    virtual void SetParam();
    virtual void Instantiate();
    jc_test_fixture*            next;       // linked list
    jc_test_entry*              tests;      // linked list
    const char*                 name;       // The name of the fixture
    const char*                 filename;   // The filename of the current ASSERT/EXPECT
    const char*                 prototype;  // The name of any prototype fixture
    struct jc_test_fixture*     parent;     // In case of parameterized tests, this points to the first test
    jc_test_void_staticfunc     fixture_setup;
    jc_test_void_staticfunc     fixture_teardown;
    jc_test_stats               stats;
    unsigned int                fail:26;
    unsigned int                type:2;     // 0: function, 1: class, 2: params class, 3: params instance
    unsigned int                first:1;    // If it's the first in a range of fixtures
    unsigned int                last:1;     // If it's the last in a range of fixtures
    unsigned int                fatal:1;    // If set, it aborts the test
    unsigned int                skipped:1;  // All tests are skipped, we skip the whole fixture
    unsigned int                index;      // the index of the param in the original params array
    int                         signum:8;   // If we're checking for a signal
    int                         line:16;    // The line of the current ASSERT/EXPECT
    int                         _pad:8;
    int                         num_tests;
} jc_test_fixture;

#if defined(__GNUC__) || defined(__clang__)
    #define JCT_PRINTF_CHECK(_JCT_IDX_FMT, _JCT_IDX_ARGS) __attribute__ ((format (printf, _JCT_IDX_FMT, _JCT_IDX_ARGS)))
#else
    #define JCT_PRINTF_CHECK(_JCT_IDX_FMT, _JCT_IDX_ARGS)
#endif

struct jc_test_print_logger
{
    // Public api
    void OnFixtureSetup(const jc_test_fixture* fixture);
    void OnFixtureTeardown(const jc_test_fixture* fixture);
    void OnTestSetup(const jc_test_fixture* fixture, const jc_test_entry* test);
    void OnTestTeardown(const jc_test_fixture* fixture, const jc_test_entry* test);
    void OnSummary(const jc_test_stats* stats, const struct jc_test_state* state);
    void OnTestFailed(const jc_test_fixture* fixture, const jc_test_entry* test, const char* format, ...) JCT_PRINTF_CHECK(4, 5);

    void Log(const char* str);
    void Log(const char* str, size_t len);
    void Logf(const char* format, ...) JCT_PRINTF_CHECK(2, 3);

    jc_test_print_logger();
    ~jc_test_print_logger();

    // private api
    struct jc_buffered_string* str;
    void ResetBuffer();
    void FlushBuffer();
};

typedef struct jc_test_state {
    #if !defined(JC_TEST_NO_DEATH_TEST)
    jc_test_jmp_buf     jumpenv;
    // remove padding warning due to jumpenv alignment
    unsigned char _pad[sizeof(void*) + sizeof(jumpenv) % sizeof(void*)];
    #endif

    jc_test_stats       stats;
    JC_TEST_LOGGER_CLASS* logger;
    jc_test_entry*      current_test;
    jc_test_fixture*    current_fixture;
    jc_test_fixture*    fixtures;
    jc_test_failure*    failures;
    jc_test_failure*    failures_last;
    char**              filter_patterns;
    size_t              dropped_failures;
    uint32_t            num_filter_patterns:8;
    uint32_t            use_colors:1;
    uint32_t            break_on_failure:1;
    uint32_t            num_fixtures:22;
    uint32_t            :32;
} jc_test_state;

// ***************************************************************************************
// Private functions

extern jc_test_state* jc_test_get_state();
extern void jc_test_exit(); // called by jc_test_run_all
extern void jc_test_set_test_fail(int fatal);
extern void jc_test_set_test_skipped();
extern void jc_test_increment_assertions();
extern void jc_test_set_signal_handler();
extern void jc_test_unset_signal_handler();
extern int jc_test_streq(const char* a, const char* b);
extern int jc_test_cmp_double_eq(double, double);
extern int jc_test_cmp_float_eq(float, float);
extern int jc_test_cmp_STREQ(const char* a, const char* b, const char* exprA, const char* exprB);
extern int jc_test_cmp_STRNE(const char* a, const char* b, const char* exprA, const char* exprB);
extern int jc_test_cmp_NEAR(double a, double b, double epsilon, const char* exprA, const char* exprB, const char* exprC);

#define JC_TEST_CAST(_TYPE_, _EXPR_)            reinterpret_cast< _TYPE_ >( _EXPR_ )
#define JC_TEST_STATIC_CAST(_TYPE_, _EXPR_)     static_cast< _TYPE_ >( _EXPR_ )

static inline jc_test_fixture* jc_test_get_fixture() {
    return jc_test_get_state()->current_fixture;
}
static inline jc_test_entry* jc_test_get_test() {
    return jc_test_get_state()->current_test;
}
static inline JC_TEST_LOGGER_CLASS* jc_test_get_logger() {
    return jc_test_get_state()->logger;
}

template <typename T>
typename std::enable_if<std::is_enum<T>::value, char*>::type
jc_test_print_value(char* buffer, size_t buffer_len, const T value) {
    return buffer + JC_TEST_SNPRINTF(buffer, buffer_len, "%d", JC_TEST_STATIC_CAST(int, value));
}

template <typename T>
typename std::enable_if< !std::is_enum<T>::value && std::is_pointer<T>::value, char*>::type
jc_test_print_value(char* buffer, size_t buffer_len, const T value) {
    return buffer + JC_TEST_SNPRINTF(buffer, buffer_len, "%p", JC_TEST_CAST(const void*, value));
}

template <typename T>
typename std::enable_if< !std::is_enum<T>::value && !std::is_pointer<T>::value && std::is_integral<T>::value && std::is_signed<T>::value, char*>::type
jc_test_print_value(char* buffer, size_t buffer_len, const T value) {
    return buffer + JC_TEST_SNPRINTF(buffer, buffer_len, JC_FMT_I64, JC_TEST_STATIC_CAST(int64_t, value));
}

template <typename T>
typename std::enable_if< !std::is_enum<T>::value && !std::is_pointer<T>::value && std::is_integral<T>::value && !std::is_signed<T>::value, char*>::type
jc_test_print_value(char* buffer, size_t buffer_len, const T value) {
    return buffer + JC_TEST_SNPRINTF(buffer, buffer_len, JC_FMT_U64, JC_TEST_STATIC_CAST(uint64_t, value));
}

template <typename T>
typename std::enable_if< !std::is_enum<T>::value && !std::is_pointer<T>::value && std::is_floating_point<T>::value, char*>::type
jc_test_print_value(char* buffer, size_t buffer_len, const T value) {
    return buffer + JC_TEST_SNPRINTF(buffer, buffer_len, "%f", JC_TEST_STATIC_CAST(double, value));
}

template <typename T>
typename std::enable_if< !std::is_enum<T>::value && !std::is_pointer<T>::value && !std::is_integral<T>::value && !std::is_floating_point<T>::value, char*>::type
jc_test_print_value(char* buffer, size_t, const T) {
    buffer[0] = '?'; buffer[1] = 0;
    return buffer+2;
}

template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const double value);
template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const float value);
template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const int8_t value);
template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const uint8_t value);
template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const int16_t value);
template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const uint16_t value);
template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const int32_t value);
template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const uint32_t value);
template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const int64_t value);
template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const uint64_t value);
template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const char* value);
template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const std::nullptr_t value);
template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const struct jct_test_null_literal* value);

template <typename T1, typename T2>
static inline void jc_test_log_failure(T1 a, T2 b, const char* exprA, const char* exprB, const char* op) {
    char bufferA[64]; jc_test_print_value(bufferA, sizeof(bufferA), a);
    char bufferB[64]; jc_test_print_value(bufferB, sizeof(bufferB), b);
    jc_test_get_logger()->OnTestFailed(jc_test_get_fixture(), jc_test_get_test(), "\nExpected: (%s) %s (%s), actual: %s vs %s\n", exprA, op, exprB, bufferA, bufferB);
}

template <typename T>
static inline void jc_test_log_failure_boolean(T v, const char* expr) {
    jc_test_get_logger()->OnTestFailed(jc_test_get_fixture(), jc_test_get_test(), "\nValue of: %s\nExpected: %s\n  Actual: %s\n", expr, (!v)?"true":"false", v?"true":"false");
}

template <typename T>
static inline void jc_test_log_failure_str(const T* a, const T* b, const char* exprA, const char* exprB, const char* op) {
    jc_test_get_logger()->OnTestFailed(jc_test_get_fixture(), jc_test_get_test(), "\nValue of: %s %s %s\nExpected: %s\n  Actual: %s\n", exprA, op, exprB, a, b);
}

template <typename T>
int jc_test_cmp_TRUE(T v, const char* expr) {
    if (v) return 1;
    jc_test_log_failure_boolean(v, expr);
    return 0;
}
template <typename T>
int jc_test_cmp_FALSE(T v, const char* expr) {
    if (!v) return 1;
    jc_test_log_failure_boolean(v, expr);
    return 0;
}

#define JC_TEST_COMPARE_FUNC(OP_NAME, OP)                                           \
    template <typename T1, typename T2>                                             \
    int jc_test_cmp_ ## OP_NAME(T1 a, T2 b, const char* exprA, const char* exprB) { \
        if (a OP b) return 1;                                                       \
        jc_test_log_failure(a, b, exprA, exprB, #OP);                               \
        return 0;                                                                   \
    }

JC_TEST_COMPARE_FUNC(EQ, ==)
JC_TEST_COMPARE_FUNC(NE, !=)
JC_TEST_COMPARE_FUNC(LE, <=)
JC_TEST_COMPARE_FUNC(LT, <)
JC_TEST_COMPARE_FUNC(GE, >=)
JC_TEST_COMPARE_FUNC(GT, >)

template <typename T> int jc_test_cmp_EQ(double a, T b, const char* exprA, const char* exprB) {
    if (jc_test_cmp_double_eq(a, JC_TEST_STATIC_CAST(double, b))) return 1;
    jc_test_log_failure(a, b, exprA, exprB, "==");
    return 0;
}
template <typename T> int jc_test_cmp_EQ(float a, T b, const char* exprA, const char* exprB) {
    if (jc_test_cmp_float_eq(a, JC_TEST_STATIC_CAST(float, b))) return 1;
    jc_test_log_failure(a, b, exprA, exprB, "==");
    return 0;
}

template <typename T> int jc_test_cmp_NE(double a, T b, const char* exprA, const char* exprB) {
    if (!jc_test_cmp_double_eq(a, JC_TEST_STATIC_CAST(double, b))) return 1;
    jc_test_log_failure(a, b, exprA, exprB, "!=");
    return 0;
}
template <typename T> int jc_test_cmp_NE(float a, T b, const char* exprA, const char* exprB) {
    if (!jc_test_cmp_float_eq(a, JC_TEST_STATIC_CAST(float, b))) return 1;
    jc_test_log_failure(a, b, exprA, exprB, "!=");
    return 0;
}

int jc_test_cmp_array(const uint8_t* a, const uint8_t* b, size_t len, size_t typesize, int valuetype, const char* exprA, const char* exprB);

template<size_t N>
int jc_test_cmp_ARRAY_EQ(const char (&a)[N], const char (&b)[N], const char* exprA, const char* exprB) {
   return jc_test_cmp_array(JC_TEST_CAST(const uint8_t*, a), JC_TEST_CAST(const uint8_t*, b), N, sizeof(char), 1, exprA, exprB);
}

template<size_t N, typename T>
int jc_test_cmp_ARRAY_EQ(T (&a)[N], T (&b)[N], const char* exprA, const char* exprB) {
   return jc_test_cmp_array(JC_TEST_CAST(const uint8_t*, a), JC_TEST_CAST(const uint8_t*, b), N, sizeof(T), 0, exprA, exprB);
}

template<typename T>
int jc_test_cmp_ARRAY_EQ_LEN(const T* a, const T* b, size_t length, const char* exprA, const char* exprB, const char*) {
   return jc_test_cmp_array(JC_TEST_CAST(const uint8_t*, a), JC_TEST_CAST(const uint8_t*, b), length, sizeof(T), 0, exprA, exprB);
}

template<>
inline int jc_test_cmp_ARRAY_EQ_LEN(const char* a, const char* b, size_t length, const char* exprA, const char* exprB, const char*) {
   return jc_test_cmp_array(JC_TEST_CAST(const uint8_t*, a), JC_TEST_CAST(const uint8_t*, b), length, sizeof(char), 1, exprA, exprB);
}

struct jc_test_cmp_eq_helper {
    template <typename T1, typename T2,
        typename std::enable_if<!std::is_integral<T1>::value ||
                                !std::is_pointer<T2>::value>::type* = nullptr>
    static int compare(const T1& a, const T2& b, const char* exprA, const char* exprB) {
        return jc_test_cmp_EQ(a, b, exprA, exprB);
    }

    static int Compare(const long long& a, const long long& b, const char* exprA, const char* exprB) {
        return jc_test_cmp_EQ(a, b, exprA, exprB);
    }

    // static int Compare(const size_t& a, const size_t& b, const char* exprA, const char* exprB) {
    //     return jc_test_cmp_EQ(a, b, exprA, exprB);
    // }

    template<typename T>
    static int compare(jct_test_null_literal*, T* b, const char* exprA, const char* exprB) {
        return jc_test_cmp_EQ(JC_TEST_STATIC_CAST(T*, 0), b, exprA, exprB);
    }
};

#define JC_TEST_ASSERT_SETUP                                                    \
    jc_test_get_fixture()->line = __LINE__;                                     \
    jc_test_get_fixture()->filename = __FILE__;                                 \
    jc_test_increment_assertions()

#define JC_TEST_FATAL_FAILURE       jc_test_set_test_fail(1); return
#define JC_TEST_NON_FATAL_FAILURE   jc_test_set_test_fail(0);

#define JC_ASSERT_TEST_BOOLEAN(OP, VALUE, FAIL_FUNC)                            \
    do {                                                                        \
        JC_TEST_ASSERT_SETUP;                                                   \
        if ( jc_test_cmp_##OP (VALUE, #VALUE) == 0 ) {                          \
            FAIL_FUNC;                                                          \
        }                                                                       \
    } while(0)
#define JC_ASSERT_TEST_EQ(A, B, FAIL_FUNC)                                      \
    do {                                                                        \
        JC_TEST_ASSERT_SETUP;                                                   \
        if ( jc_test_cmp_eq_helper::compare(A, B, #A, #B) == 0 ) {              \
            FAIL_FUNC;                                                          \
        }                                                                       \
    } while(0)
#define JC_ASSERT_TEST_OP(OP, A, B, FAIL_FUNC)                                  \
    do {                                                                        \
        JC_TEST_ASSERT_SETUP;                                                   \
        if ( jc_test_cmp_##OP (A, B, #A, #B) == 0 ) {                           \
            FAIL_FUNC;                                                          \
        }                                                                       \
    } while(0)
#define JC_ASSERT_TEST_3OP(OP, A, B, C, FAIL_FUNC)                              \
    do {                                                                        \
        JC_TEST_ASSERT_SETUP;                                                   \
        if ( jc_test_cmp_##OP (A, B, C, #A, #B, #C) == 0 ) {                    \
            FAIL_FUNC;                                                          \
        }                                                                       \
    } while(0)
#if !defined(JC_TEST_NO_DEATH_TEST)
#define JC_ASSERT_TEST_DEATH_OP(STATEMENT, RE, FAIL_FUNC)                       \
    do {                                                                        \
        JC_TEST_ASSERT_SETUP;                                                   \
        if (JC_TEST_SETJMP(jc_test_get_state()->jumpenv) == 0) {                \
            jc_test_set_signal_handler();                                       \
            jc_test_get_logger()->Log("\njc_test: Death test begin ->\n");      \
            STATEMENT;                                                          \
            jc_test_get_logger()->OnTestFailed(jc_test_get_fixture(), jc_test_get_test(), "\nExpected this to fail: %s", #STATEMENT ); \
            jc_test_unset_signal_handler();                                     \
            FAIL_FUNC;                                                          \
        }                                                                       \
        jc_test_unset_signal_handler();                                         \
        jc_test_get_logger()->Log("jc_test: <- Death test end\n");              \
    } while(0)
#else
#define JC_ASSERT_TEST_DEATH_OP(STATEMENT, RE, FAIL_FUNC)
#endif

// TEST API Begin -->

#define SKIP()                          { jc_test_set_test_skipped(); return; }

#define ASSERT_TRUE( VALUE )            JC_ASSERT_TEST_BOOLEAN( TRUE, VALUE, JC_TEST_FATAL_FAILURE )
#define ASSERT_FALSE( VALUE )           JC_ASSERT_TEST_BOOLEAN( FALSE, VALUE, JC_TEST_FATAL_FAILURE )
#define ASSERT_EQ( A, B )               JC_ASSERT_TEST_EQ( A, B, JC_TEST_FATAL_FAILURE )
#define ASSERT_NE( A, B )               JC_ASSERT_TEST_OP( NE, A, B, JC_TEST_FATAL_FAILURE )
#define ASSERT_LT( A, B )               JC_ASSERT_TEST_OP( LT, A, B, JC_TEST_FATAL_FAILURE )
#define ASSERT_GT( A, B )               JC_ASSERT_TEST_OP( GT, A, B, JC_TEST_FATAL_FAILURE )
#define ASSERT_LE( A, B )               JC_ASSERT_TEST_OP( LE, A, B, JC_TEST_FATAL_FAILURE )
#define ASSERT_GE( A, B )               JC_ASSERT_TEST_OP( GE, A, B, JC_TEST_FATAL_FAILURE )
#define ASSERT_STREQ( A, B )            JC_ASSERT_TEST_OP( STREQ, A, B, JC_TEST_FATAL_FAILURE )
#define ASSERT_STRNE( A, B )            JC_ASSERT_TEST_OP( STRNE, A, B, JC_TEST_FATAL_FAILURE )
#define ASSERT_NEAR( A, B, EPS )        JC_ASSERT_TEST_3OP( NEAR, A, B, EPS, JC_TEST_FATAL_FAILURE )
#define ASSERT_DEATH(S, RE)             JC_ASSERT_TEST_DEATH_OP( S, RE, JC_TEST_FATAL_FAILURE )
#define ASSERT_ARRAY_EQ( A, B )         JC_ASSERT_TEST_OP( ARRAY_EQ, A, B, JC_TEST_FATAL_FAILURE )
#define ASSERT_ARRAY_EQ_LEN( A, B, LEN )JC_ASSERT_TEST_3OP( ARRAY_EQ_LEN, A, B, LEN, JC_TEST_FATAL_FAILURE )

#define EXPECT_TRUE( VALUE )            JC_ASSERT_TEST_BOOLEAN( TRUE, VALUE, JC_TEST_NON_FATAL_FAILURE )
#define EXPECT_FALSE( VALUE )           JC_ASSERT_TEST_BOOLEAN( FALSE, VALUE, JC_TEST_NON_FATAL_FAILURE )
#define EXPECT_EQ( A, B )               JC_ASSERT_TEST_EQ( A, B, JC_TEST_NON_FATAL_FAILURE )
#define EXPECT_NE( A, B )               JC_ASSERT_TEST_OP( NE, A, B, JC_TEST_NON_FATAL_FAILURE )
#define EXPECT_LT( A, B )               JC_ASSERT_TEST_OP( LT, A, B, JC_TEST_NON_FATAL_FAILURE )
#define EXPECT_GT( A, B )               JC_ASSERT_TEST_OP( GT, A, B, JC_TEST_NON_FATAL_FAILURE )
#define EXPECT_LE( A, B )               JC_ASSERT_TEST_OP( LE, A, B, JC_TEST_NON_FATAL_FAILURE )
#define EXPECT_GE( A, B )               JC_ASSERT_TEST_OP( GE, A, B, JC_TEST_NON_FATAL_FAILURE )
#define EXPECT_STREQ( A, B )            JC_ASSERT_TEST_OP( STREQ, A, B, JC_TEST_NON_FATAL_FAILURE )
#define EXPECT_STRNE( A, B )            JC_ASSERT_TEST_OP( STRNE, A, B, JC_TEST_NON_FATAL_FAILURE )
#define EXPECT_NEAR( A, B, EPS )        JC_ASSERT_TEST_3OP( NEAR, A, B, EPS, JC_TEST_NON_FATAL_FAILURE )
#define EXPECT_DEATH(S, RE)             JC_ASSERT_TEST_DEATH_OP(S, RE, JC_TEST_NON_FATAL_FAILURE )
#define EXPECT_ARRAY_EQ( A, B )         JC_ASSERT_TEST_OP( ARRAY_EQ, A, B, JC_TEST_NON_FATAL_FAILURE )
#define EXPECT_ARRAY_EQ_LEN( A, B, LEN )JC_ASSERT_TEST_3OP( ARRAY_EQ_LEN, A, B, LEN, JC_TEST_NON_FATAL_FAILURE )

#define SCOPED_TRACE(_MSG)  // nop

template<typename T>
struct jc_test_value_iterator {
    virtual ~jc_test_value_iterator();
    virtual const T* Get() const = 0;
    virtual void Advance() = 0;
    virtual bool Empty() const = 0;   // return false when out of values
    virtual void Rewind() = 0;
};
template<typename T> jc_test_value_iterator<T>::~jc_test_value_iterator() {} // separate line to silence warning

template<typename T>
struct jc_test_array_iterator : public jc_test_value_iterator<T> {
    const T *begin, *cursor, *end;
    jc_test_array_iterator(const T* _begin, const T* _end) : begin(_begin), cursor(_begin), end(_end) {}
    const T* Get() const{ return cursor; }
    void Advance()      { ++cursor; }
    bool Empty() const  { return cursor == end; }
    void Rewind()       { cursor = begin; }
};

template<typename T> jc_test_array_iterator<T>* jc_test_values_in(const T* begin, const T* end) {
    return new jc_test_array_iterator<T>(begin, end);
}
template<typename T, size_t N> jc_test_array_iterator<T>* jc_test_values_in(const T (&arr)[N] ) {
    return jc_test_values_in(arr, arr+N);
}

template<typename ParamType> const ParamType* jc_test_params_class<ParamType>::param = 0;

template<typename ParamType>
struct jc_test_fixture_with_param : public jc_test_fixture {
    void SetParam() { JC_TEST_CAST(jc_test_params_class<ParamType>*, jc_test_get_state()->current_test)->SetParam(param); }
    void Instantiate();
    const ParamType* param;
};

template<typename ParamType>
void jc_test_create_from_prototype(jc_test_fixture_with_param<ParamType>* fixture);

template<typename ParamType>
void jc_test_fixture_with_param<ParamType>::Instantiate() { jc_test_create_from_prototype(this); }


struct jc_test_factory_base_interface {
    virtual ~jc_test_factory_base_interface();
};

template<typename ParamType>
struct jc_test_factory_interface : public jc_test_factory_base_interface {
    virtual jc_test_params_class<ParamType>* New() = 0;
    virtual void SetParam(const ParamType* param) = 0;
};

template<typename T>
struct jc_test_factory : public jc_test_factory_interface<typename T::param_t> {
    jc_test_params_class<typename T::param_t>* New()    { return new T(); }
    void SetParam(const typename T::param_t* param)     { T::SetParam(param); }
};

#define JC_TEST_FIXTURE_TYPE_CLASS              0
#define JC_TEST_FIXTURE_TYPE_PARAMS_CLASS       1
#define JC_TEST_FIXTURE_TYPE_TYPED_CLASS        2

extern jc_test_fixture* jc_test_find_fixture(const char* name, unsigned int fixture_type);
extern jc_test_fixture* jc_test_alloc_fixture(const char* name, unsigned int fixture_type);
extern jc_test_fixture* jc_test_create_fixture(jc_test_fixture* fixture, const char* name, unsigned int fixture_type);
extern jc_test_entry*   jc_test_add_test_to_fixture(jc_test_fixture* fixture, const char* test_name, jc_test_base_class* instance, jc_test_factory_base_interface* factory);
extern void             jc_test_memcpy(void* dst, const void* src, size_t size);

extern int jc_test_keep_test(jc_test_state* state, const char* name); // checks if the name is tagged for skipping

extern int jc_test_register_class_test(const char* fixture_name, const char* test_name,
                                                jc_test_void_staticfunc class_setup, jc_test_void_staticfunc class_teardown,
                                                jc_test_base_class* instance, unsigned int fixture_type);
template <typename ParamType>
int jc_test_register_param_class_test(const char* fixture_name, const char* test_name,
                        jc_test_void_staticfunc class_setup, jc_test_void_staticfunc class_teardown,
                        jc_test_factory_interface<ParamType>* factory) {
    jc_test_fixture* fixture = jc_test_find_fixture(fixture_name, JC_TEST_FIXTURE_TYPE_PARAMS_CLASS);
    if (!fixture) {
        fixture = jc_test_alloc_fixture(fixture_name, JC_TEST_FIXTURE_TYPE_PARAMS_CLASS);
        fixture->fixture_setup = class_setup;
        fixture->fixture_teardown = class_teardown;
    }
    jc_test_add_test_to_fixture(fixture, test_name, 0, factory);
    return 0;
}

struct jc_test_type0 {};

template<typename T1>
struct jc_test_type1 {
    typedef T1 head; typedef jc_test_type0 tail;
};
template<typename T1, typename T2>
struct jc_test_type2 {
    typedef T2 head; typedef jc_test_type1<T1> tail;
};
template<typename T1, typename T2, typename T3>
struct jc_test_type3 {
    typedef T3 head; typedef jc_test_type2<T1, T2> tail;
};
template<typename T1, typename T2, typename T3, typename T4>
struct jc_test_type4 {
    typedef T4 head; typedef jc_test_type3<T1, T2, T3> tail;
};

template <typename BaseClassSelector, typename TypeList>
struct jc_test_register_typed_class_test {
    static int register_test(const char* fixture_name, const char* test_name, unsigned int index) {
        typedef typename TypeList::head TypeParam;
        typedef typename BaseClassSelector::template bind<TypeParam>::type TestClass;

        jc_test_fixture* fixture = jc_test_find_fixture(fixture_name, JC_TEST_FIXTURE_TYPE_TYPED_CLASS);
        if (!fixture) {
            fixture = jc_test_alloc_fixture(fixture_name, JC_TEST_FIXTURE_TYPE_CLASS);
            fixture->fixture_setup = TestClass::SetUpTestCase;
            fixture->fixture_teardown = TestClass::TearDownTestCase;
        }
        fixture->index = index;
        jc_test_add_test_to_fixture(fixture, test_name, new TestClass, 0);
        return jc_test_register_typed_class_test<BaseClassSelector, typename TypeList::tail>::
                    register_test(fixture_name, test_name, index+1);
    }
};

template <typename BaseClassSelector>
struct jc_test_register_typed_class_test<BaseClassSelector,jc_test_type0> {
    static int register_test(const char*, const char*, unsigned int) {
        return 0;
    }
};

template<typename ParamType>
jc_test_fixture* jc_test_alloc_fixture_with_param(const char* name, unsigned int type) {
    return jc_test_create_fixture(new jc_test_fixture_with_param<ParamType>(), name, type);
}

template<typename ParamType>
void jc_test_create_from_prototype(jc_test_fixture_with_param<ParamType>* fixture) {

    jc_test_fixture* prototype_fixture = jc_test_find_fixture(fixture->prototype, JC_TEST_FIXTURE_TYPE_PARAMS_CLASS);
    if (!prototype_fixture) {
        jc_test_get_logger()->Logf("Couldn't find fixture of name %s\n", fixture->prototype);
        JC_TEST_ASSERT_FN(prototype_fixture != 0);
    }
    JC_TEST_ASSERT_FN(prototype_fixture->type == JC_TEST_FIXTURE_TYPE_PARAMS_CLASS);

    fixture->fixture_setup = prototype_fixture->fixture_setup;
    fixture->fixture_teardown = prototype_fixture->fixture_teardown;

    fixture->num_tests = prototype_fixture->num_tests;
    jc_test_entry* prototype_test = prototype_fixture->tests;
    jc_test_entry* first = 0;
    jc_test_entry* prev = 0;
    while (prototype_test) {
        jc_test_entry* test = new jc_test_entry();
        test->next = 0;
        test->name = prototype_test->name;
        test->factory = 0;
        test->time = 0;
        test->fail = 0;
        test->skipped = 0;

        jc_test_factory_interface<ParamType>* factory = JC_TEST_CAST(jc_test_factory_interface<ParamType>*, prototype_test->factory);
        factory->SetParam(fixture->param);
        test->instance = factory->New();

        if (!first) {
            first = test;
            prev = test;
        } else {
            prev->next = test;
            prev = test;
        }
        prototype_test = prototype_test->next;
    }
    fixture->tests = first;
}

template<typename ParamType>
int jc_test_register_param_tests(const char* prototype_fixture_name, const char* fixture_name, jc_test_value_iterator<ParamType>* values)
{
    unsigned int index = 0;
    jc_test_fixture* first_fixture = 0;
    while (!values->Empty()) {

        // Allocate a new fixture, and create the test class
        jc_test_fixture_with_param<ParamType>* fixture = JC_TEST_CAST(jc_test_fixture_with_param<ParamType>*,
                                jc_test_alloc_fixture_with_param<ParamType>(fixture_name, JC_TEST_FIXTURE_TYPE_CLASS) );
        if (!fixture) {
            delete values;
            return 1;
        }

        fixture->first = first_fixture == 0 ? 1 : 0;
        if (!first_fixture) {
            first_fixture = fixture; // A silly trick to make the first fixture accumulate all the timings from this batch
        }
        fixture->parent = first_fixture;
        fixture->index = index++;
        fixture->param = values->Get();
        fixture->prototype = prototype_fixture_name;

        values->Advance();

        fixture->last = values->Empty() ? 1 : 0;
    }

    delete values;
    return 0;
}

#define JC_TEST_MAKE_NAME2(X,Y)                 X ## _ ## Y
#define JC_TEST_MAKE_NAME3(X,Y,Z)               X ## _ ## Y ## _ ## Z
#define JC_TEST_MAKE_CLASS_NAME(X, Y)           JC_TEST_MAKE_NAME3(X, Y, TestCase)
#define JC_TEST_MAKE_FUNCTION_NAME(X, Y)        JC_TEST_MAKE_NAME2(X, Y)
#define JC_TEST_MAKE_UNIQUE_NAME(X, Y, LINE)    JC_TEST_MAKE_NAME3(X, Y, LINE)

#define TEST3(testfixture,testfn,testname)                                                                                  \
class JC_TEST_MAKE_CLASS_NAME(testfixture,testfn) : public jc_test_base_class {                                             \
    virtual void TestBody() override;                                                                                       \
};                                                                                                                          \
static int JC_TEST_MAKE_UNIQUE_NAME(testfixture,testfn,__LINE__) JC_TEST_UNUSED = jc_test_register_class_test(              \
        testname, #testfn, jc_test_base_class::SetUpTestCase, jc_test_base_class::TearDownTestCase,                         \
        new JC_TEST_MAKE_CLASS_NAME(testfixture,testfn), JC_TEST_FIXTURE_TYPE_CLASS);                                       \
void JC_TEST_MAKE_CLASS_NAME(testfixture,testfn)::TestBody()

#define TEST(testfixture,testfn) TEST3(testfixture,testfn,#testfixture)

#define TEST_F(testfixture,testfn)                                                                                          \
    class JC_TEST_MAKE_CLASS_NAME(testfixture,testfn) : public testfixture {                                                \
        virtual void TestBody() override;                                                                                   \
    };                                                                                                                      \
    static int JC_TEST_MAKE_UNIQUE_NAME(testfixture,testfn,__LINE__) JC_TEST_UNUSED = jc_test_register_class_test(          \
            #testfixture, #testfn, testfixture::SetUpTestCase, testfixture::TearDownTestCase,                               \
            new JC_TEST_MAKE_CLASS_NAME(testfixture,testfn), JC_TEST_FIXTURE_TYPE_CLASS);                                   \
    void JC_TEST_MAKE_CLASS_NAME(testfixture,testfn)::TestBody()

#define TEST_P(testfixture,testfn)                                                                                          \
    class JC_TEST_MAKE_CLASS_NAME(testfixture,testfn) : public testfixture {                                                \
        virtual void TestBody() override;                                                                                   \
    };                                                                                                                      \
    static int JC_TEST_MAKE_UNIQUE_NAME(testfixture,testfn,__LINE__) JC_TEST_UNUSED = jc_test_register_param_class_test(    \
            #testfixture, #testfn, testfixture::SetUpTestCase, testfixture::TearDownTestCase,                               \
            new jc_test_factory<JC_TEST_MAKE_CLASS_NAME(testfixture,testfn)>());                                            \
    void JC_TEST_MAKE_CLASS_NAME(testfixture,testfn)::TestBody()

#define INSTANTIATE_TEST_CASE_P(prefix,testfixture,testvalues)                                                              \
    static int JC_TEST_MAKE_UNIQUE_NAME(prefix,testfixture,__LINE__) JC_TEST_UNUSED =                                       \
        jc_test_register_param_tests<testfixture::param_t>(#testfixture, #prefix "/" #testfixture, testvalues)


template<typename T> struct jc_test_typed_list {
    typedef T type;
};

template<template <typename T> class BaseClass> struct jc_test_template_sel {
    template <typename TypeParam> struct bind {
        typedef BaseClass<TypeParam> type;
    };
};

#define TYPED_TEST_CASE(testfixture,testtypes)                                                             \
    typedef jc_test_typed_list<testtypes>::type JC_TEST_MAKE_NAME2(testfixture,Types)

#define TYPED_TEST(testfixture,testfn)                                                                      \
    template<typename T> class JC_TEST_MAKE_CLASS_NAME(testfixture,testfn) : public testfixture<T> {        \
        virtual void TestBody() override;                                                                   \
        typedef testfixture<T> TestFixture;                                                                 \
        typedef T TypeParam;                                                                                \
    };                                                                                                      \
    static int JC_TEST_MAKE_UNIQUE_NAME(testfixture,testfn,__LINE__) JC_TEST_UNUSED =                       \
            jc_test_register_typed_class_test<                                                              \
                jc_test_template_sel<JC_TEST_MAKE_CLASS_NAME(testfixture,testfn)>,                          \
                JC_TEST_MAKE_NAME2(testfixture,Types)>::register_test(#testfixture, #testfn, 0);            \
    template<typename T> void JC_TEST_MAKE_CLASS_NAME(testfixture,testfn)<T>::TestBody()

#if !defined(_MSC_VER)
#pragma GCC diagnostic pop
#endif

#endif // JC_TEST_HPP

#ifdef JC_TEST_USE_DEFAULT_MAIN
#define JC_TEST_IMPLEMENTATION
#endif

#ifdef JC_TEST_IMPLEMENTATION
#undef JC_TEST_IMPLEMENTATION

#if !defined(JC_TEST_FAILURE_MALLOC)
#define JC_TEST_FAILURE_MALLOC malloc
#endif
#if !defined(JC_TEST_FAILURE_REALLOC)
#define JC_TEST_FAILURE_REALLOC realloc
#endif
#if !defined(JC_TEST_FAILURE_FREE)
#define JC_TEST_FAILURE_FREE free
#endif

#if defined(_MSC_VER)
    #include <debugapi.h> // OutputDebugString, IsDebuggerPresent
#endif

#if defined(__GNUC__) || defined(__clang__)
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Wzero-as-null-pointer-constant"
    #pragma GCC diagnostic ignored "-Wold-style-cast"
    #pragma GCC diagnostic ignored "-Wformat-nonliteral"
#endif

#if defined(_MSC_VER)
#define JC_TEST_VA_COPY(_DST, _SRC) ((_DST) = (_SRC))
#else
#define JC_TEST_VA_COPY(_DST, _SRC) va_copy((_DST), (_SRC))
#endif


struct jc_buffered_string
{
    char* buffer;
    size_t capacity;
    size_t size;
    jc_buffered_string(size_t _capacity)
        : buffer(0)
        , capacity(0)
        , size(0)
    {
        Grow(_capacity);
        buffer[0] = 0;
    }
    ~jc_buffered_string()
    {
        free(buffer);
    }

    size_t Size()
    {
        return size;
    }

    void Reset()
    {
        size = 0;
    }

    void Grow(size_t _size)
    {
        capacity += _size;
#if defined(_MSC_VER)
        // C6308: realloc may return null and overwrite the original pointer, causing a leak.
        #pragma warning(suppress:6308)
#endif
        buffer = (char*)realloc(buffer, capacity);
        assert(buffer != 0);
    }

    void Append(const char* str, size_t len)
    {
        size_t left = capacity - size;
        if ( left <= len )
        {
            Grow(len - left + 1);
        }

        memcpy(buffer+size, str, len);
        size += len;
        buffer[size] = 0;
    }

    void Append(const char* str)
    {
        Append(str, strlen(str));
    }

    void AppendTime(jc_test_time_t us) // Micro seconds
    {
    #ifdef _MSC_VER
        #define JC_TEST_MICROSECONDS_STR "us"
    #else
        #define JC_TEST_MICROSECONDS_STR "\u00b5s"
    #endif
        if( us < 5000 )
            Appendf("%g %s", (double)(us), JC_TEST_MICROSECONDS_STR);
        else if( us < 500000 )
            Appendf("%g %s", (double)us / 1000.0, "ms");
        else
            Appendf("%g %s", (double)us / 1000000.0, "s");
    }

    void AppendList(const char* const format, va_list args)
    {
        for (int i = 0; i < 2; ++i)
        {
            uint32_t left = (uint32_t)(capacity - size);

            va_list copy;
            JC_TEST_VA_COPY(copy, args);
            int n = vsnprintf(buffer+size, capacity-size, format, copy);
            va_end(copy);

            if (n < 0)
                return; // Something went really wrong
            if (n > 0 && n < (int)left)
            {
                size += (size_t)n;
                return;
            }
            // the string was truncated, so let's try again, with more memory
            Grow((size_t)n - (capacity - size) + 1);
        }
        assert(false); // Should never get here
    }

    void Appendf(const char* const format, ...) JCT_PRINTF_CHECK(2,3)
    {
        va_list args;
        va_start(args, format);
        AppendList(format, args);
        va_end(args);
    }
};

#define JC_TEST_PRINT_TYPE_FN(TYPE, FORMAT) \
    template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const TYPE value) { \
        return buffer + JC_TEST_SNPRINTF(buffer, buffer_len, FORMAT, value); \
    }

// Note that you have to add the corresponding declaration above too
JC_TEST_PRINT_TYPE_FN(double,   "%f")
JC_TEST_PRINT_TYPE_FN(int8_t,   "%hhd")
JC_TEST_PRINT_TYPE_FN(int16_t,  "%hd")
JC_TEST_PRINT_TYPE_FN(int32_t,  "%d")
JC_TEST_PRINT_TYPE_FN(uint8_t,  "%hhu")
JC_TEST_PRINT_TYPE_FN(uint16_t, "%hu")
JC_TEST_PRINT_TYPE_FN(uint32_t, "%u")
JC_TEST_PRINT_TYPE_FN(uint64_t, JC_FMT_U64)
JC_TEST_PRINT_TYPE_FN(int64_t,  JC_FMT_I64)
JC_TEST_PRINT_TYPE_FN(char*,    "%s")

template <> char* jc_test_print_value(char* buffer, size_t buffer_len, const float value) {
    return buffer + JC_TEST_SNPRINTF(buffer, buffer_len, "%f", JC_TEST_STATIC_CAST(double, value));
}

template <> char* jc_test_print_value(char* buffer, size_t buffer_len, std::nullptr_t) {
    return buffer + JC_TEST_SNPRINTF(buffer, buffer_len, "nullptr_t");
}

#define JC_TEST_CLR_DEFAULT "\x1B[0m"
#define JC_TEST_CLR_RED     "\x1B[31m"
#define JC_TEST_CLR_GREEN   "\x1B[32m"
#define JC_TEST_CLR_YELLOW  "\x1B[33m"
#define JC_TEST_CLR_MAGENTA "\x1B[35m"
#define JC_TEST_CLR_CYAN    "\x1B[36m"

#define JC_TEST_CLR_PASS    JC_TEST_CLR_GREEN
#define JC_TEST_CLR_FAIL    JC_TEST_CLR_RED
#define JC_TEST_CLR_SKIP    JC_TEST_CLR_CYAN

#define JC_TEST_COL(CLR)            (jc_test_get_state()->use_colors ? JC_TEST_CLR_ ## CLR : "")
#define JC_TEST_COL2(CLR, USECOLOR) ((USECOLOR) ? JC_TEST_CLR_ ## CLR : "")

//static size_t jc_test_snprint_time(char* buffer, size_t buffer_len, jc_test_time_t t);

static int jc_get_formatted_test_name(char* buffer, size_t buffer_len, const jc_test_fixture* fixture, const jc_test_entry* test, int usecolor) {
    if (fixture->index != 0xFFFFFFFF)
        return JC_TEST_SNPRINTF(buffer, buffer_len, "%s%s%s.%s%s%s/%u", JC_TEST_COL2(CYAN,usecolor), fixture->name, JC_TEST_COL2(DEFAULT,usecolor), JC_TEST_COL2(YELLOW,usecolor), test->name, JC_TEST_COL2(DEFAULT,usecolor), fixture->index);
    else
        return JC_TEST_SNPRINTF(buffer, buffer_len, "%s%s%s.%s%s%s", JC_TEST_COL2(CYAN,usecolor), fixture->name, JC_TEST_COL2(DEFAULT,usecolor), JC_TEST_COL2(YELLOW,usecolor), test->name, JC_TEST_COL2(DEFAULT,usecolor));
}

static char* jc_test_format_failure_message(const char* format, va_list args)
{
    size_t capacity = 256;
    char* buffer = 0;
    for (;;) {
        char* grown = JC_TEST_CAST(char*, JC_TEST_FAILURE_REALLOC(buffer, capacity));
        if (grown == 0) {
            JC_TEST_FAILURE_FREE(buffer);
            return 0;
        }
        buffer = grown;
        va_list copy;
        JC_TEST_VA_COPY(copy, args);
        int count = vsnprintf(buffer, capacity, format, copy);
        va_end(copy);
        if (count >= 0 && JC_TEST_STATIC_CAST(size_t, count) < capacity)
            return buffer;
        capacity = count >= 0 ? JC_TEST_STATIC_CAST(size_t, count) + 1 : capacity * 2;
    }
}

static void jc_test_record_failure(const jc_test_fixture* fixture, const jc_test_entry* test,
                                   const char* format, va_list args)
{
    jc_test_state* state = jc_test_get_state();
    size_t name_capacity = strlen(fixture->name) + (test ? strlen(test->name) : 9) + 32;
    char* test_name = JC_TEST_CAST(char*, JC_TEST_FAILURE_MALLOC(name_capacity));
    char* message = jc_test_format_failure_message(format, args);
    jc_test_failure* failure = JC_TEST_CAST(jc_test_failure*, JC_TEST_FAILURE_MALLOC(sizeof(jc_test_failure)));
    if (test_name == 0 || message == 0 || failure == 0) {
        JC_TEST_FAILURE_FREE(test_name);
        JC_TEST_FAILURE_FREE(message);
        JC_TEST_FAILURE_FREE(failure);
        ++state->dropped_failures;
        return;
    }
    if (test != 0)
        jc_get_formatted_test_name(test_name, name_capacity, fixture, test, 0);
    else
        JC_TEST_SNPRINTF(test_name, name_capacity, "%s.<unknown>", fixture->name);
    failure->next = 0;
    failure->test_name = test_name;
    failure->filename = fixture->filename;
    failure->line = fixture->line;
    failure->message = message;
    failure->_pad = 0;
    if (state->failures_last != 0)
        state->failures_last->next = failure;
    else
        state->failures = failure;
    state->failures_last = failure;
}

static inline void jc_test_memset(void* _mem, unsigned int pattern, size_t size)
{
    uint8_t* mem = (uint8_t*)_mem;
    for (size_t i = 0; i < size; ++i) {
        mem[i] = (uint8_t)(pattern & 0xFF);
    }
}

static inline size_t jc_test_memcmp(const uint8_t* a, const uint8_t* b, size_t size)
{
    for (size_t i = 0; i < size; ++i) {
        if (a[i] != b[i])
            return i;
    }
    return (size_t)~0;
}

jc_test_base_class::Setup_should_be_spelled_SetUp* jc_test_base_class::Setup() { return 0; } // Trick from GTEST to make sure users don't accidentally misspell the function


jc_test_print_logger::jc_test_print_logger()
{
    str = new jc_buffered_string(1024);
}

jc_test_print_logger::~jc_test_print_logger()
{
    delete str;
}

void jc_test_print_logger::ResetBuffer()
{
    str->Reset();
}

#if !defined(JC_TEST_OUTPUT_FN)
    static void jc_write_output(const char* text, size_t text_len)
    {
#if defined(_MSC_VER)
        OutputDebugStringA(text);
#endif

#if defined(JC_TEST_USE_PRINTF)
        (void)text_len;
        printf("%s", text);
#else
        fwrite(text, text_len, 1, stdout);
#endif
        fflush(stdout);
    }
#endif

#ifndef JC_TEST_OUTPUT_FN
    #include <assert.h>
    #define JC_TEST_OUTPUT_FN jc_write_output
#endif

void jc_test_print_logger::FlushBuffer()
{
    JC_TEST_OUTPUT_FN(str->buffer, str->size);
    str->Reset();
}

void jc_test_print_logger::Log(const char* text, size_t text_len)
{
    JC_TEST_OUTPUT_FN(text, text_len);
}

void jc_test_print_logger::Log(const char* text)
{
    Log(text, strlen(text));
}

void jc_test_print_logger::Logf(const char* format, ...)
{
    ResetBuffer();

    va_list args;
    va_start(args, format);
    str->AppendList(format, args);
    va_end(args);

    FlushBuffer();
}

void jc_test_print_logger::OnSummary(const jc_test_stats* stats, const jc_test_state* state)
{
    ResetBuffer();

    const jc_test_failure* failure = state->failures;
    if (failure != 0 || state->dropped_failures != 0) {
        str->Append("\nFailures:\n");
        while (failure != 0) {
            str->Appendf("\n%s\n%s:%d:%s\n", failure->test_name,
                         failure->filename, failure->line, failure->message);
            failure = failure->next;
        }
        if (state->dropped_failures != 0) {
            str->Appendf("\n%zu failure detail(s) could not be retained.\n",
                         state->dropped_failures);
        }
    }

    str->Appendf("Ran %d tests, with %d assertions in ", stats->num_tests, stats->num_assertions);
    str->AppendTime(stats->totaltime);
    if( stats->num_fail)
    {
        str->Appendf("\n%d tests passed, %d skipped and %d tests %sFAILED%s\n", stats->num_pass, stats->num_skipped, stats->num_fail, JC_TEST_COL(RED), JC_TEST_COL(DEFAULT));
    }
    else
    {
        str->Appendf("\n%d tests %sPASSED%s and %d skipped\n", stats->num_pass, JC_TEST_COL(GREEN), JC_TEST_COL(DEFAULT), stats->num_skipped);
    }

    FlushBuffer();
}

void jc_test_print_logger::OnFixtureSetup(const jc_test_fixture* fixture)
{
    ResetBuffer();
    str->Appendf("%s%s%s\n", JC_TEST_COL(CYAN), fixture->name, JC_TEST_COL(DEFAULT));
    FlushBuffer();
}
void jc_test_print_logger::OnFixtureTeardown(const jc_test_fixture* fixture)
{
    ResetBuffer();

    jc_test_time_t totaltime = fixture->stats.totaltime;
    if (fixture->parent) {
        totaltime = fixture->parent->stats.totaltime;
    }
    str->Appendf("%s%s%s took ", JC_TEST_COL(CYAN), fixture->name, JC_TEST_COL(DEFAULT));
    str->AppendTime(totaltime);
    str->Appendf("\n");

    FlushBuffer();
}

void jc_test_print_logger::OnTestSetup(const jc_test_fixture* fixture, const jc_test_entry* test)
{
    char name[1024];
    ResetBuffer();

    jc_get_formatted_test_name(name, sizeof(name), fixture, test,
                               jc_test_get_state()->use_colors);
    str->Append(name);
    str->Append("\n");

    FlushBuffer();
}

void jc_test_print_logger::OnTestTeardown(const jc_test_fixture* fixture, const jc_test_entry* test)
{
    char name[1024];
    ResetBuffer();

    jc_get_formatted_test_name(name, sizeof(name), fixture, test,
                               jc_test_get_state()->use_colors);
    str->Append(name);
    if (test->fail)
        str->Appendf(" %s%s%s (", JC_TEST_COL(FAIL), "FAIL", JC_TEST_COL(DEFAULT));
    else if (test->skipped)
        str->Appendf(" %s%s%s (", JC_TEST_COL(SKIP), "SKIPPED", JC_TEST_COL(DEFAULT));
    else
        str->Appendf(" %s%s%s (", JC_TEST_COL(PASS), "PASS", JC_TEST_COL(DEFAULT));
    str->AppendTime(test->time);
    str->Append(")\n");

    FlushBuffer();
}

void jc_test_print_logger::OnTestFailed(const jc_test_fixture* fixture, const jc_test_entry* test, const char* format, ...)
{
    ResetBuffer();

    str->Appendf("\n%s%s%s:%d:", JC_TEST_COL(MAGENTA), fixture->filename, JC_TEST_COL(DEFAULT), fixture->line);
    if (format) {
        va_list args;
        va_start(args, format);
        str->AppendList(format, args);
        va_end(args);

        va_start(args, format);
        jc_test_record_failure(fixture, test, format, args);
        va_end(args);
    }

    FlushBuffer();
}

int jc_test_cmp_array(const uint8_t* a, const uint8_t* b, size_t len, size_t typesize, int valuetype, const char* exprA, const char* exprB) {
    size_t erroroffset = jc_test_memcmp(a, b, typesize*len);
    if (erroroffset == JC_TEST_STATIC_CAST(size_t, -1)) return 1;

    // max number of differing characters displayed
    const size_t max_num_to_display = 32;
    // Each byte is shown as two characters + start/end color
    const size_t stringsize = max_num_to_display*(2 + sizeof(JC_TEST_CLR_RED)*2) + 1;
    jc_buffered_string stra(stringsize);
    jc_buffered_string strb(stringsize);
    char indexprefix[stringsize] = {0};
    jc_buffered_string diff(stringsize);
    size_t size = len*typesize;

    // try to frame the output around the diff
    // also slide the view frame to always show num_elements (if available)
    size_t num_local_elements = max_num_to_display / typesize;
    size_t start = erroroffset/typesize - num_local_elements;
    size_t end = erroroffset/typesize + num_local_elements;

    if (start > size) { // overflow
        start = 0;
        end = len < num_local_elements ? len : num_local_elements;
    }
    if (end > len) {
        end = len;
        start = len < num_local_elements ? 0 : len - num_local_elements;
    }

    start *= typesize;
    end *= typesize;

    // index of element in the shown sub array
    size_t local_index = (erroroffset - start) / typesize;

    jc_test_memset(indexprefix, ' ', 1 + local_index * typesize * (valuetype == 1 ? 1 : 2) + (valuetype == 1 ? 0 : local_index));

    for(size_t i = start; i < end; i += typesize) {
        int byte_diff = jc_test_memcmp(a+i, b+i, typesize) != JC_TEST_STATIC_CAST(size_t, -1);
        const char* color_a = byte_diff ? JC_TEST_COL(GREEN) : JC_TEST_COL(DEFAULT);
        const char* color_b = byte_diff ? JC_TEST_COL(RED) : JC_TEST_COL(DEFAULT);

        stra.Append(color_a);
        strb.Append(color_b);

        if (valuetype == 1) // char
        {
            stra.Appendf("%c", JC_TEST_STATIC_CAST(char, a[i]));
            strb.Appendf("%c", JC_TEST_STATIC_CAST(char, b[i]));
            diff.Append(byte_diff ? "^" : " ");
        }
        else {
            for (int t = JC_TEST_STATIC_CAST(int, typesize)-1; t >= 0; --t) {
                stra.Appendf("%02X", a[JC_TEST_STATIC_CAST(size_t, t) + i]);
                strb.Appendf("%02X", b[JC_TEST_STATIC_CAST(size_t, t) + i]);
                diff.Append(byte_diff ? "^^" : "  ");
            }
            diff.Append(" ");
        }
        stra.Append(JC_TEST_COL(DEFAULT));
        strb.Append(JC_TEST_COL(DEFAULT));
        if (valuetype != 1 && i < end - typesize) {
            stra.Append(" ");
            strb.Append(" ");
        }
    }
    const char* emptyprefix = "   ";
    const char* prefix = start == 0 ? (valuetype == 1 ? "  \"" : "  [") : (valuetype == 1 ? "\".." : "[..");
    const char* suffix = end < size ? (valuetype == 1 ? "..\"" : "..]") : (valuetype == 1 ? "\"" : "]");

    jc_test_get_logger()->OnTestFailed(jc_test_get_fixture(), jc_test_get_test(),
            "\nValue of %s == %s\nIndex:   %s%s%zu\nExpected: %s%s%s\nActual:   %s%s%s\nDiff:     %s%s\n",
            exprA, exprB,
            emptyprefix, indexprefix, erroroffset/typesize,
            prefix, stra.buffer, suffix,
            prefix, strb.buffer, suffix,
            emptyprefix, diff.buffer);
    return 0;
}

#undef JC_TEST_COL
#undef JC_TEST_CLR_DEFAULT
#undef JC_TEST_CLR_RED
#undef JC_TEST_CLR_GREEN
#undef JC_TEST_CLR_YELLOW
#undef JC_TEST_CLR_MAGENTA
#undef JC_TEST_CLR_CYAN

void jc_test_memcpy(void* dst, const void* src, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        JC_TEST_CAST(unsigned char*, dst)[i] = JC_TEST_CAST(const unsigned char*, src)[i];
    }
}

int jc_test_streq(const char* a, const char* b) {
    if (a == 0) return (b == 0) ? 1 : 0;
    if (b == 0) return 0;
    while (*a && (*a == *b)) {
        ++a; ++b;
    }
    return (*a - *b) == 0 ? 1 : 0;
}

static inline int jc_test_compare_str(const char* a, const char* b) { // returns 1 if the strings are equal
    while(*a && *b) {
        if (*a != *b) return 0;
        ++a; ++b;
    }
    return *b == 0;
}

static const char* jc_test_strstr(const char* a, const char* b) { // returns non-null if the string B is found in A
    while (*a) {
        if (*a == *b && jc_test_compare_str(a, b))
            return a;
        ++a;
    }
    return 0;
}

int jc_test_cmp_NEAR(double a, double b, double epsilon, const char* exprA, const char* exprB, const char* exprC) {
    double diff = a > b ? a - b : b - a;
    if (diff <= epsilon) return 1;
    char bA[64]; jc_test_print_value(bA, sizeof(bA), a);
    char bB[64]; jc_test_print_value(bB, sizeof(bB), b);
    char bEpsilon[64]; jc_test_print_value(bEpsilon, sizeof(bEpsilon), epsilon);
    char bDiff[64]; jc_test_print_value(bDiff, sizeof(bDiff), diff);
    jc_test_get_logger()->OnTestFailed(jc_test_get_fixture(), jc_test_get_test(), "\nValue of: abs(%s - %s) <= %s\nExpected: abs(%s - %s) <= %s\n  Actual: abs(%s - %s) == %s\n", exprA, exprB, exprC, bA, bB, bEpsilon, bA, bB, bDiff);
    return 0;
}

int jc_test_cmp_STREQ(const char* a, const char* b, const char* exprA, const char* exprB) {
    if (jc_test_streq(a, b)) return 1;
    jc_test_log_failure_str(a, b, exprA, exprB, "==");
    return 0;
}

int jc_test_cmp_STRNE(const char* a, const char* b, const char* exprA, const char* exprB) {
    if (!jc_test_streq(a, b)) return 1;
    jc_test_log_failure_str(a, b, exprA, exprB, "!=");
    return 0;
}

// http://en.wikipedia.org/wiki/Signed_number_representations
template <typename IntType>
static inline IntType jc_test_float_to_biased(IntType bits) {
    const IntType sign_bit = JC_TEST_STATIC_CAST(IntType, 1) << (8*sizeof(IntType) - 1);
    return (sign_bit & bits) ? ~bits + 1 : bits | sign_bit;
}

template <typename FloatType, typename IntType>
static int jc_test_cmp_float_almost_equal(FloatType a, FloatType b) {
    static const int max_ulp = 4;
    union {
        FloatType f; IntType i;
    } ua, ub; ua.f = a; ub.f = b;
    IntType biased_a = jc_test_float_to_biased<IntType>(ua.i);
    IntType biased_b = jc_test_float_to_biased<IntType>(ub.i);
    IntType dist_ulp = (biased_a > biased_b) ? (biased_a - biased_b) : (biased_b - biased_a);
    return dist_ulp <= max_ulp;
}

int jc_test_cmp_double_eq(double a, double b) {
    return jc_test_cmp_float_almost_equal<double, uint64_t>(a, b);
}
int jc_test_cmp_float_eq(float a, float b) {
    return jc_test_cmp_float_almost_equal<float, uint32_t>(a, b);
}

jc_test_factory_base_interface::~jc_test_factory_base_interface() {}

jc_test_fixture::~jc_test_fixture() {}
void jc_test_fixture::SetParam() {}
void jc_test_fixture::Instantiate() {}

jc_test_base_class::~jc_test_base_class() {}
void jc_test_base_class::SetUp() {}
void jc_test_base_class::TearDown() {}

jc_test_fixture* jc_test_create_fixture(jc_test_fixture* fixture, const char* name, unsigned int fixture_type) {
    fixture->next = 0;
    fixture->tests = 0;
    fixture->name = name;
    fixture->filename = 0;
    fixture->prototype = 0;
    fixture->type = fixture_type;
    fixture->parent = 0;
    fixture->fail = 0;
    fixture->fatal = 0;
    fixture->skipped = 0;
    fixture->index = 0xFFFFFFFF;
    fixture->num_tests = 0;
    fixture->first = fixture->last = 1;
    fixture->signum = 0;
    fixture->line = 0;
    fixture->_pad = 0;
    fixture->fixture_setup = 0;
    fixture->fixture_teardown = 0;
    jc_test_memset(&fixture->stats, 0, sizeof(fixture->stats));
    jc_test_get_state()->num_fixtures++;
    jc_test_fixture* prev = jc_test_get_state()->fixtures;
    if (!prev) jc_test_get_state()->fixtures = fixture;
    else {
        while (prev->next) prev = prev->next;
        prev->next = fixture;
    }
    return fixture;
}

jc_test_entry* jc_test_add_test_to_fixture(jc_test_fixture* fixture, const char* test_name, jc_test_base_class* instance, jc_test_factory_base_interface* factory) {
    jc_test_entry* test = new jc_test_entry();
    test->next = 0;
    test->name = test_name;
    test->instance = instance;
    test->factory = factory;
    test->time = 0;
    test->fail = 0;
    test->skipped = 0;
    jc_test_entry* prev = fixture->tests;
    if (!prev) fixture->tests = test;
    else {
        while(prev->next) prev = prev->next;
        prev->next = test;
    }
    fixture->num_tests++;
    return test;
}

jc_test_fixture* jc_test_find_fixture(const char* name, unsigned int fixture_type) {
    jc_test_fixture* fixture = jc_test_get_state()->fixtures;
    while (fixture) {
        if (fixture->type == fixture_type && jc_test_streq(fixture->name, name))
            return fixture;
        fixture = fixture->next;
    }
    return 0;
}

jc_test_fixture* jc_test_alloc_fixture(const char* name, unsigned int fixture_type) {
    return jc_test_create_fixture(new jc_test_fixture(), name, fixture_type);
}

int jc_test_register_class_test(const char* fixture_name, const char* test_name,
                        jc_test_void_staticfunc class_setup, jc_test_void_staticfunc class_teardown,
                        jc_test_base_class* instance, unsigned int fixture_type) {
    jc_test_fixture* fixture = jc_test_find_fixture(fixture_name, fixture_type);
    if (!fixture) {
        fixture = jc_test_alloc_fixture(fixture_name, fixture_type);
        fixture->fixture_setup = class_setup;
        fixture->fixture_teardown = class_teardown;
    }
    jc_test_add_test_to_fixture(fixture, test_name, instance, 0);
    return 0;
}

void jc_test_exit() {
    jc_test_state* state = jc_test_get_state();
    jc_test_fixture* fixture = state->fixtures;
    while (fixture) {
        jc_test_entry* test = fixture->tests;
        while (test) {
            delete test->instance;
            delete test->factory;
            jc_test_entry* tmp_test = test;
            test = test->next;
            delete tmp_test;
        }
        jc_test_fixture* tmp_fixture = fixture;
        fixture = fixture->next;
        delete tmp_fixture;
    }

    for (uint32_t i = 0; i < state->num_filter_patterns; ++i) {
        delete[] state->filter_patterns[i];
    }
    delete[] state->filter_patterns;

    jc_test_failure* failure = state->failures;
    while (failure) {
        jc_test_failure* next = failure->next;
        JC_TEST_FAILURE_FREE(failure->test_name);
        JC_TEST_FAILURE_FREE(failure->message);
        JC_TEST_FAILURE_FREE(failure);
        failure = next;
    }
}

#if defined(_MSC_VER)
    static int jct_is_debugger_attached()
    {
        return IsDebuggerPresent();
    }

#elif defined(__MACH__)

    #include <sys/types.h>
    #include <sys/sysctl.h>
    #include <unistd.h>

    static int jct_is_debugger_attached()
    {
        // From https://developer.apple.com/library/archive/qa/qa1361/_index.html

        // Initialize mib, which tells sysctl the info we want, in this case
        // we're looking for information about a specific process ID.
        int mib[4] = { CTL_KERN, KERN_PROC, KERN_PROC_PID, getpid() };

        struct kinfo_proc   info;
        size_t size = sizeof(info);
        // Initialize the flags so that, if sysctl fails for some bizarre
        // reason, we get a predictable result.
        info.kp_proc.p_flag = 0;

        int junk = sysctl(mib, sizeof(mib) / sizeof(*mib), &info, &size, NULL, 0);
        if (junk != 0)
            return 0;

        // We're being debugged if the P_TRACED flag is set.
        return ( (info.kp_proc.p_flag & P_TRACED) != 0 );
    }

#elif defined(__linux__)
    #include <stdio.h> // FILE
    #include <stdlib.h> // atoi

    static int jct_is_debugger_attached()
    {
        FILE* f = fopen("/proc/self/status", "rt");
        if (!f)
            return 0;

        const char* kTracerPid = "TracerPid:";

        size_t linesize = 1024;
        char* line = (char*)malloc(linesize);
        int tracer_pid = 0;
        while ( !feof(f) )
        {
            ssize_t nread = getline(&line, &linesize, f);
            if (nread < 0)
                break;

            if (strstr(line, kTracerPid) != 0)
            {
                tracer_pid = atoi(line + 10);
                break;
            }
        }
        fclose(f);
        free(line);
        return tracer_pid != 0 ? 1 : 0;
    }
#else
    static int jct_is_debugger_attached()
    {
        return 0;
    }
#endif

#ifndef JCT_IS_DEBUGGER_ATTACHED
    #define JCT_IS_DEBUGGER_ATTACHED() jct_is_debugger_attached()
#endif


static void jc_test_dbg_break()
{
    if (!jc_test_get_state()->break_on_failure)
        return;
    JC_TEST_DBG_BREAK();
}

void jc_test_set_test_fail(int fatal) {
    jc_test_get_test()->fail = 1;
    jc_test_get_fixture()->fail = 1;
    jc_test_get_fixture()->fatal |= fatal;

    jc_test_dbg_break(); // break if enabled
}

void jc_test_set_test_skipped() {
    jc_test_get_test()->skipped = 1;
}

void jc_test_increment_assertions() {
    jc_test_get_fixture()->stats.num_assertions++;
}

// static size_t jc_test_snprint_time(char* buffer, size_t buffer_len, jc_test_time_t t) { // Micro seconds
// #ifdef _MSC_VER
//     #define JC_TEST_MICROSECONDS_STR "us"
// #else
//     #define JC_TEST_MICROSECONDS_STR "\u00b5s"
// #endif
//     int printed;
//     if( t < 5000 )
//         printed = JC_TEST_SNPRINTF(buffer, buffer_len, "%g %s", JC_TEST_STATIC_CAST(double, t), JC_TEST_MICROSECONDS_STR);
//     else if( t < 500000 )
//         printed = JC_TEST_SNPRINTF(buffer, buffer_len, "%g %s", t / 1000.0, "ms");
//     else
//         printed = JC_TEST_SNPRINTF(buffer, buffer_len, "%g %s", t / 1000000.0, "s");
//     return JC_TEST_STATIC_CAST(size_t, printed);
// }

#define JC_TEST_INVOKE_MEMBER_FN(INSTANCE, FN) \
    (JC_TEST_CAST(jc_test_base_class*,INSTANCE) ->* JC_TEST_CAST(jc_test_void_memberfunc,FN)) ()

static void jc_test_disable_tests(jc_test_state* state, jc_test_fixture* fixture) {
    jc_test_entry* test = fixture->tests;
    int num_skipped = 0;
    while (test) {
        char name_buffer[256];
        jc_get_formatted_test_name(name_buffer, sizeof(name_buffer), fixture, test, 0);
        if (!jc_test_keep_test(state, name_buffer))
            test->skipped = 1;
        num_skipped += test->skipped;
        test = test->next;
    }
    fixture->skipped = num_skipped == fixture->num_tests ? 1 : 0;
}


static void jc_test_run_fixture(jc_test_fixture* fixture) {
    jc_test_get_state()->current_fixture = fixture;

    if (fixture->type == JC_TEST_FIXTURE_TYPE_PARAMS_CLASS) {
        return;
    }

    jc_test_memset(&fixture->stats, 0, sizeof(fixture->stats));

    if (fixture->prototype)
        fixture->Instantiate(); // instantiate the parameterized tests so we can (potentially) filter them

    // check for skipping tests
    jc_test_disable_tests(jc_test_get_state(), fixture);

    if (fixture->skipped) {
        fixture->stats.num_skipped += fixture->num_tests;
        return;
    }

    jc_test_time_t timestart = JC_TEST_TIMING_FUNC();
    if (fixture->first) {
        jc_test_get_logger()->OnFixtureSetup(fixture);
    }

    if (fixture->first && fixture->fixture_setup != 0) {
        fixture->fixture_setup();
    }

    fixture->fail = 0;

    jc_test_entry* test = fixture->tests;
    while (test) {
        test->fail = 0;
        fixture->fatal = 0;

        if (!test->skipped) {
            jc_test_get_state()->current_test = test;
            fixture->SetParam();

            jc_test_get_logger()->OnTestSetup(fixture, test);

            jc_test_time_t teststart = 0;
            jc_test_time_t testend = 0;

            jc_test_void_memberfunc cppfns[3] = { &jc_test_base_class::SetUp, &jc_test_base_class::TestBody, &jc_test_base_class::TearDown };

            for( int i = 0; i < 3; ++i ) {
                if( i == 1 ) {
                    teststart = JC_TEST_TIMING_FUNC();
                }

                JC_TEST_INVOKE_MEMBER_FN(test->instance, cppfns[i]);

                if( i == 1 ) {
                    testend = JC_TEST_TIMING_FUNC();
                }

                if( fixture->fatal ) {
                    break;
                }
            }

            test->time = testend-teststart;
            jc_test_get_logger()->OnTestTeardown(fixture, test);

            fixture->stats.num_fail += test->fail ? 1 : 0;
        }

        fixture->stats.num_skipped += test->skipped ? 1 : 0;
        test = test->next;
    }
    fixture->stats.num_tests = fixture->num_tests - fixture->stats.num_skipped;
    fixture->stats.num_pass = fixture->stats.num_tests - fixture->stats.num_fail;
    jc_test_get_state()->current_test = 0;

    if (fixture->last && fixture->fixture_teardown != 0) {
        fixture->fixture_teardown();
    }

    jc_test_time_t timeend = JC_TEST_TIMING_FUNC();
    fixture->stats.totaltime = timeend - timestart;
    if (fixture->parent) {
        fixture->parent->stats.totaltime += fixture->stats.totaltime;
    }

    if (fixture->last) {
        jc_test_get_logger()->OnFixtureTeardown(fixture);
    }
    jc_test_get_state()->current_fixture = 0;
}

#if defined(_WIN32)
    jc_test_time_t jc_test_get_time(void) {
        LARGE_INTEGER tickPerSecond;
        LARGE_INTEGER tick;
        QueryPerformanceFrequency(&tickPerSecond);
        QueryPerformanceCounter(&tick);
        return JC_TEST_STATIC_CAST(jc_test_time_t, tick.QuadPart / (tickPerSecond.QuadPart / 1000000));
    }
#else
    #include <sys/time.h>
    jc_test_time_t jc_test_get_time(void) {
        struct timeval tv;
        gettimeofday(&tv, 0);
        return JC_TEST_STATIC_CAST(jc_test_time_t, tv.tv_sec) * 1000000U + JC_TEST_STATIC_CAST(jc_test_time_t, tv.tv_usec);
    }
#endif

#if !defined(_MSC_VER)
#pragma GCC diagnostic pop
#endif


#if !defined(JC_TEST_NO_DEATH_TEST)
#if defined(__clang__) || defined(__GNUC__)
__attribute__ ((noreturn))
#endif
static void jc_test_signal_handler(int) {
    JC_TEST_LONGJMP(jc_test_get_state()->jumpenv, 1);
}

#if defined(_WIN32) || defined(__CYGWIN__)
    typedef void (*jc_test_signal_handler_fn)(int);
    static jc_test_signal_handler_fn g_signal_handlers[4];
    void jc_test_set_signal_handler() {
        g_signal_handlers[0] = signal(SIGILL, jc_test_signal_handler);
        g_signal_handlers[1] = signal(SIGABRT, jc_test_signal_handler);
        g_signal_handlers[2] = signal(SIGFPE, jc_test_signal_handler);
        g_signal_handlers[3] = signal(SIGSEGV, jc_test_signal_handler);
    }
    void jc_test_unset_signal_handler() {
        signal(SIGILL, g_signal_handlers[0]);
        signal(SIGABRT, g_signal_handlers[1]);
        signal(SIGFPE, g_signal_handlers[2]);
        signal(SIGSEGV, g_signal_handlers[3]);
    }
#else
    static struct sigaction g_signal_handlers[6];

    void jc_test_set_signal_handler() {
        #if !defined(_MSC_VER) && defined(__clang__)
            #pragma GCC diagnostic push
            #pragma GCC diagnostic ignored "-Wdisabled-macro-expansion"
        #endif
        struct sigaction handler;
        jc_test_memset(&handler, 0, sizeof(struct sigaction));
        handler.sa_handler = jc_test_signal_handler;
        sigaction(SIGILL, &handler, &g_signal_handlers[0]);
        sigaction(SIGABRT, &handler, &g_signal_handlers[1]);
        sigaction(SIGBUS, &handler, &g_signal_handlers[2]);
        sigaction(SIGFPE, &handler, &g_signal_handlers[3]);
        sigaction(SIGSEGV, &handler, &g_signal_handlers[4]);
        sigaction(SIGPIPE, &handler, &g_signal_handlers[5]);
        #if !defined(_MSC_VER) && defined(__clang__)
            #pragma GCC diagnostic pop
        #endif
    }
    void jc_test_unset_signal_handler() {
        sigaction(SIGILL, &g_signal_handlers[0], 0);
        sigaction(SIGABRT, &g_signal_handlers[1], 0);
        sigaction(SIGBUS, &g_signal_handlers[2], 0);
        sigaction(SIGFPE, &g_signal_handlers[3], 0);
        sigaction(SIGSEGV, &g_signal_handlers[4], 0);
        sigaction(SIGPIPE, &g_signal_handlers[5], 0);
    }
#endif
#endif

jc_test_state* jc_test_get_state() {
    static jc_test_state g_state;
    static int g_state_first = 1;
    if (g_state_first) {
        g_state_first = 0;
        jc_test_memset(&g_state, 0, sizeof(jc_test_state));
    }
    return &g_state;
}


static void jc_test_usage() {
    jc_test_get_logger()->Log("jc_test options:\n");
    jc_test_get_logger()->Log("\t--test-filter <pattern>  substring or '*' wildcard\n");
    jc_test_get_logger()->Log("\t--test-filter=<pattern>  equivalent form\n");
    jc_test_get_logger()->Log("\t--filter=<pattern>       utest-compatible form\n");
}

static int jc_test_wildcard_match(const char* pattern, const char* text) {
    const char* star = 0;
    const char* retry = 0;
    while (*text) {
        if (*pattern == '*') {
            star = pattern++;
            retry = text;
        }
        else if (*pattern == *text) {
            ++pattern;
            ++text;
        }
        else if (star) {
            pattern = star + 1;
            text = ++retry;
        }
        else {
            return 0;
        }
    }
    while (*pattern == '*') ++pattern;
    return *pattern == 0;
}

int jc_test_keep_test(jc_test_state* state, const char* name) {
    if (state->num_filter_patterns == 0)
        return 1;
    for (uint32_t i = 0; i < state->num_filter_patterns; ++i) {
        const char* pattern = state->filter_patterns[i];
        if (pattern == 0)
            continue;
        if (strchr(pattern, '*') != 0) {
            if (jc_test_wildcard_match(pattern, name))
                return 1;
        }
        else if (jc_test_strstr(name, pattern) != 0) {
            return 1;
        }
    }
    return 0;
}


static size_t jc_test_strlen(const char* str) {
    const char *s;
    for (s = str; *s; ++s);
    return JC_TEST_STATIC_CAST(size_t, s - str);
}

static char* jc_test_strdup(const char* s) {
    size_t len = jc_test_strlen(s);
    char* dup = new char[len+1];
    jc_test_memcpy(JC_TEST_CAST(void*, dup), JC_TEST_CAST(const void*, s), len+1);
    return dup;
}

static void jc_test_add_test_filter(jc_test_state* state, const char* pattern) {
    if (state->filter_patterns == 0) {
        state->filter_patterns = new char*[255];
        jc_test_memset(state->filter_patterns, 0, sizeof(char*) * 255);
    }
    if (state->num_filter_patterns == 255)
        return;
    state->filter_patterns[state->num_filter_patterns++] = jc_test_strdup(pattern);
}

// checks for jctest specific command line arguments: e.g. "--test-filter Foo"
static int jc_test_parse_commandline(int* argc, char** argv) {
    int i = 1;
    while (i < *argc) {
        const char* arg = argv[i];
        const char* pattern = 0;
        int remove_count = 0;
        if (jc_test_streq(arg, "--test-filter")) {
            if (i+1>=*argc) return 1;
            pattern = argv[i+1];
            remove_count = 2;
        }
        else if (strncmp(arg, "--test-filter=", 14) == 0) {
            pattern = arg + 14;
            remove_count = 1;
        }
        else if (strncmp(arg, "--filter=", 9) == 0) {
            pattern = arg + 9;
            remove_count = 1;
        }
        else if(jc_test_streq(arg, "--test-break-on-fail")) {
            jc_test_get_state()->break_on_failure = 1;
            remove_count = 1;
        }
        if (pattern != 0)
            jc_test_add_test_filter(jc_test_get_state(), pattern);
        if (remove_count != 0) {
            for(int j = i + remove_count; j < *argc; ++j)
                argv[j - remove_count] = argv[j];
            *argc -= remove_count;
        }
        else
            ++i;
    }
    return 0;
}

int jc_test_run_all() {
    jc_test_state* state = jc_test_get_state();
    state->logger = new JC_TEST_LOGGER_CLASS();
    state->stats.totaltime = 0;
    jc_test_fixture* fixture = state->fixtures;
    while (fixture) {
        jc_test_run_fixture( fixture );
        state->stats.num_assertions += fixture->stats.num_assertions;
        state->stats.num_pass += fixture->stats.num_pass;
        state->stats.num_fail += fixture->stats.num_fail;
        state->stats.num_skipped += fixture->stats.num_skipped;
        state->stats.num_tests += fixture->stats.num_tests;
        state->stats.totaltime += fixture->stats.totaltime;
        fixture = fixture->next;
    }

    jc_test_get_logger()->OnSummary(&state->stats, state);

    int num_fail = state->stats.num_fail;
    jc_test_exit();
    return num_fail;
}

#if !defined(JC_TEST_USE_COLORS)
#if !defined(JC_TEST_ISATTY) // this is only needed if we're trying to find out if the output supports ansi colors

#if defined(__CYGWIN__) || !defined(_WIN32)
    #include <unistd.h> // isatty
#else // _WIN32
    #include <io.h>     // _isatty
    #include <string.h>
#endif

#if !defined(_WIN32)
    #define JC_TEST_ISATTY(_X) isatty(_X) ? 1U : 0U
#else
    #define JC_TEST_ISATTY(_X) (_isatty(_X) || jctest_cyg_isatty(_X)) ? 1U : 0U

    #ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
        #define ENABLE_VIRTUAL_TERMINAL_PROCESSING  0x0004
    #endif

    // credit: https://github.com/ggreer/the_silver_searcher/pull/1146/files

    // Cygwin/msys2 pty is a pipe with the following format (H: hex-digit, N: 0-9):
    // '\{cygwin,msys}-HHHHHHHHHHHHHHHH-ptyN-{from,to}-master'
    static int jctest_cyg_isatty(int fd) {
    // The API here needs Vista or later SDK (WINVER 0x0600 or higher), and the
    // binary won't run on XP - unless NO_CYGTTY is defined (which disables it).
    // It's not impossible to make it work on XP, but not worth jumping through
    // the hoops, especially after msys2 and Cygwin dropped XP support in 2016.
    #if WINVER < 0x0600
        (void)fd;
        return 0;
    #else
        HANDLE h = (HANDLE)_get_osfhandle(fd);
        if ((h == INVALID_HANDLE_VALUE) || (GetFileType(h) != FILE_TYPE_PIPE))
            return 0;

    #define INFOSIZE (sizeof(FILE_NAME_INFO) + sizeof(WCHAR) * MAX_PATH)
        char buf[INFOSIZE + sizeof(WCHAR)]; // +1 WCHAR for our '\0'
        if (!GetFileInformationByHandleEx(h, FileNameInfo, buf, INFOSIZE))
            return 0;

        FILE_NAME_INFO *info = (FILE_NAME_INFO *)buf;
        WCHAR *n = info->FileName; // no \0 from the API. We reserved extra char.
        n[info->FileNameLength / sizeof(WCHAR)] = 0;
        return ((wcsstr(n, L"\\msys-") == n) || (wcsstr(n, L"\\cygwin-") == n)) && wcsstr(n, L"-pty") && (wcsstr(n, L"-from-master") || wcsstr(n, L"-to-master"));
    #endif // WINVER
    }
#endif // _WIN32
#endif // JC_TEST_ISATTY
#endif // JC_TEST_USE_COLORS

static int jct_get_tty_color_support() {
    #if defined(JC_TEST_USE_COLORS)
        return JC_TEST_USE_COLORS;
    #else
        int is_a_tty = JC_TEST_ISATTY(1);
        #if defined(_WIN32)
        if (is_a_tty) { // Try enabling ANSI escape sequence support on Windows 10 terminals.
            DWORD mode;
            HANDLE console_ = GetStdHandle(STD_OUTPUT_HANDLE);
            if (GetConsoleMode(console_, &mode)) {
                SetConsoleMode(console_, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
            } else {
                is_a_tty = 0;
            }
        }
        #endif
        return is_a_tty;
    #endif
}

void jc_test_init(int* argc, char** argv) {
    jc_test_get_state()->use_colors = (uint32_t)jct_get_tty_color_support();
    jc_test_get_state()->break_on_failure = (uint32_t)JCT_IS_DEBUGGER_ATTACHED();

    if (jc_test_parse_commandline(argc, argv)) {
        jc_test_usage();
        JC_TEST_EXIT(1);
    }
}

#endif

#ifdef JC_TEST_USE_DEFAULT_MAIN
int main(int argc, char** argv) {
    jc_test_init(&argc, argv);
    return jc_test_run_all();
}
#endif

/*

// Use case 2:

// Test fixtures are good if you wish to call code before or after the test or fixture itself.

struct MyTest : public jc_test_base_class {
 static void SetUpTestCase()      {...};
 static void TearDownTestCase()   {...};
 virtual void SetUp()             {...};
 virtual void TearDown()          {...};
};

TEST_F(MyTest, TestName) {
 ASSERT_EQ(4, 2*2);
}

// Use case 3:

// Parameterized tests are good if you wish to call a test case with different parameters

struct MyParamTest : public jc_test_params_class<ParamType> {
    static void SetUpTestCase()      {...};
    static void TearDownTestCase()   {...};
    virtual void SetUp()             {...};
    virtual void TearDown()          {...};
    static const ParamType&          GetParam(); // New param for each test iteration
};

TEST_P(MyParamTest, IsEven) {
    ParamType value = GetParam();
    ASSERT_EQ(0, value & 1);
}

// Creates a new fixture for each test param
INSTANTIATE_TEST_CASE_P(EvenValues, MyParamTest, jc_test_values(2,4,6,8,10));
*/

/*
 * BRIEF:
 *
 *      A small, single header only C++-11 test framework
 *      Made sure to compile with highest warning/error levels possible
 *
 * HISTORY:
 *      0.15    2026-07-22  * Renamed the C++ header to jc_test.hpp
 *                          * Added wildcard filter forms
 *                          * Added detailed end-of-run failure recaps
 *      0.14    2026-06-01  * Fix for log buffer overrun
 *                          * Fix for numeric formatting in messages
 *      0.13    2026-02-21  * Fix for uninitialized values
 *      0.12    2025-09-24  * Added more robust way to check for PRIu64 etc
 *      0.11    2023-10-13  * Added JC_TEST_OUTPUT_FN for customizing log output
 *                          * Added JC_TEST_USE_PRINTF to choose printf() over write()
 *      0.10    2023-05-19  * Introduced JC_TEXT_LOGGER_CLASS for easier log printing
 *                          * Added --test-break-on-fail for breaking into the debugger.
 *                          Can be configured with JC_TEST_DBG_BREAK define.
 *                          * Added automatic check for an attached debugger
 *              2023-05-27  * Added JCT_IS_DEBUGGER_ATTACHED for easier overrides
 *      0.9     2022-12-22  Fixed proper printout for pointer values
 *                          Minimum version is now C++11 due to usage of <type_traits>
 *                          Removed doctest support
 *      0.8     2021-04-03  Added fflush to logging to prevent test output becoming out of order
 *      0.7     2021-02-07  Fixed null pointer warning on C++11 and above
 *                          Test filtering now works on parameterized tests
 *      0.6     2020-03-12  Fixed bootstrap issue w/static initializers
 *                          Added support for JC_TEST_USE_COLORS to force color on/off
 *                          Added support for JC_TEST_USE_DEFAULT_MAIN
 *      0.5     2019-11-10  Added support for logging enum values
 *                          Added ASSERT_ARRAY_EQ
 *      0.4     2019-08-10  Fix for outputting 64 bit integer values upon error
 *                          Skipping tests now doesn't output extraneous info
 *      0.3     2019-04-25  Ansi colors for Win32
 *                          Msys2 + Cygwin support
 *                          setjmp fix for Emscripten
 *                          Removed limit on number of tests
 *      0.2     2019-04-14  Fixed ASSERT_EQ for single precision floats
 *      0.1     2019-01-19  Added GTEST-like C++ interface
 *
 * LICENSE:
 *
 *     The MIT License (MIT)
 *
 *     Copyright (c) 2018-2026 Mathias Westerdahl
 *
 *     Permission is hereby granted, free of charge, to any person obtaining a copy
 *     of this software and associated documentation files (the "Software"), to deal
 *     in the Software without restriction, including without limitation the rights
 *     to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *     copies of the Software, and to permit persons to whom the Software is
 *     furnished to do so, subject to the following conditions:
 *
 *     The above copyright notice and this permission notice shall be included in all
 *     copies or substantial portions of the Software.
 *
 *     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *     IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *     FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *     AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *     LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *     OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *     SOFTWARE.
 *
 * DISCLAIMER:
 *
 *      This software is supplied "AS IS" without any warranties and support
 *
 *      This software was designed to be a (non complete) replacement for GTEST,
 *      with the intent to replace the library in an existing code base.
 *      Although the supported features were implemented in the same spirit as the GTEST
 *      fixtures/functions, there will be discprepancies. However, those differences have
 *      been chosen from a pragmatic standpoint, in favor of making porting of the existing
 *      tests feasible with minimal changes, as well as keeping this library
 *      as light weight as possible.
 */
