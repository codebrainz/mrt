#include <mrt/string.h>
#include <mrt/strutils.h>
#include "CuTest.h"

void test_mrt_string(CuTest *tc)
{
  (void)tc;
#if 0 // FIXME
  MRT_Object *str;

  str = mrt_string_new("Hello");
  CuAssertTrue(tc, MRT_IS_STRING(str));
  CuAssertIntEquals(tc, 5, mrt_string_length(MRT_STRING(str)));
  CuAssertStrEquals(tc, "Hello", mrt_string_get(MRT_STRING(str)));

  mrt_string_set(MRT_STRING(str), "Hello World");
  CuAssertIntEquals(tc, mrt_strlen("Hello World"), mrt_string_length(MRT_STRING(str)));
  CuAssertStrEquals(tc, "Hello World", mrt_string_get(MRT_STRING(str)));

  mrt_object_unref(str);
#endif
}

CuSuite* mrt_string_get_test_suite(void)
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, test_mrt_string);

    return &suite;
}
