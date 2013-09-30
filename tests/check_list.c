#include <mrt/sequence.h>
#include <mrt/list.h>
#include "CuTest.h"

// Boilerplate to use sequence tests with the list
#define MAKE_TEST_FUNC_NAME(fn) test_m_list_ ## fn
#define MAKE_TEST_FUNC(fn) void MAKE_TEST_FUNC_NAME(fn) (CuTest *tc)
#define MAKE_SUITE_GETTER CuSuite *m_list_get_test_suite(void)
#include "check_sequence.c"
