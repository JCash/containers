#if defined(USE_GTEST)
    #include <gtest/gtest.h>
#else
    #define JC_TEST_IMPLEMENTATION
    #include <jc/test.h>
#endif

extern void GlobalTestSetup();
extern int GlobalTestTeardown();

int main(int argc, char **argv)
{
    GlobalTestSetup();
#if defined(USE_GTEST)
    testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();
#else
    jc_test_init(&argc, argv);
    int ret = JC_TEST_RUN_ALL();
#endif
    if (ret != 0) {
        return ret;
    }
    ret = GlobalTestTeardown();
    if (ret != 0) {
        printf("Test verification failed");
    }
    return ret;
}
