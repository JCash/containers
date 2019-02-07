#pragma once

#if defined(USE_GTEST)
    #include <gtest/gtest.h>
    class jc_test_base_class : public ::testing::Test {};

    template<typename T>
    class jc_test_params_class : public ::testing::TestWithParam<T> {};

    #define jc_test_values_in ::testing::ValuesIn
#else
    #include <jc/test.h>
#endif
