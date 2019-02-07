
#include <string.h>
#include <stdio.h>
#include "testutil.h"

// To test the testing framework /////////////
void GlobalTestSetup(); // to silence a warning
void GlobalTestSetup() {
    printf("Setting up calls\n");
}
int GlobalTestTeardown(); // to silence a warning
int GlobalTestTeardown() {
    printf("Verifying the calls\n");
    return 0;
}
//////////////////////////////////////////////

struct TestParam {
    size_t      length;
    const char* str;
};

class ParamsTest : public jc_test_params_class<TestParam>
{
protected:
    virtual void SetUp();
    virtual void TearDown();
};

void ParamsTest::SetUp() {
}
void ParamsTest::TearDown() {
}


TEST_P(ParamsTest, Test1)
{
    const TestParam& p = GetParam();
    ASSERT_EQ(p.length, strlen(p.str));
}

TEST_P(ParamsTest, Test2)
{
    const TestParam& p = GetParam();
    ASSERT_EQ(p.length, strlen(p.str));
}


TEST_F(ParamsTest, Test3)
{
    ASSERT_EQ(4, 2*2);
}


const TestParam params1[] = { {5, "magic"}, {4, "bean"} };
INSTANTIATE_TEST_CASE_P(FirstParamsTest, ParamsTest, jc_test_values_in(params1));

const TestParam params2[] = { {6, "wizard"}, {5, "witch"} };
INSTANTIATE_TEST_CASE_P(SecondParamsTest, ParamsTest, jc_test_values_in(params2));



