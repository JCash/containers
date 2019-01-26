#define JC_TEST_IMPLEMENTATION
#include <jc/test.h>
#include "algorithm.cpp"
#include "array.cpp"
#include "hashtable.cpp"

int main(int argc, char** argv)
{
    jc_test_init(&argc, argv);
	return JC_TEST_RUN_ALL();
}
