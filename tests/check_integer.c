#include <mrt/integer.h>
#include "CuTest.h"

void test_mrt_integer(CuTest *tc)
{
  MRT_Value *i;

  // is integer and is number
  i = mrt_integer_new(123);
  CuAssertTrue(tc, MRT_IS_INTEGER(i));
  CuAssertTrue(tc, MRT_IS_NUMBER(i));
  mrt_value_unref(i);

  // zero
  i = mrt_integer_new(0);
  CuAssertInt64Equals(tc, 0, mrt_integer_get(MRT_INTEGER(i)));
  mrt_value_unref(i);

  // positive number
  i = mrt_integer_new(200);
  CuAssertInt64Equals(tc, 200, mrt_integer_get(MRT_INTEGER(i)));
  mrt_value_unref(i);

  // negative number
  i = mrt_integer_new(-200);
  CuAssertInt64Equals(tc, -200, mrt_integer_get(MRT_INTEGER(i)));
  mrt_value_unref(i);

  // lower bounds
  i = mrt_integer_new(INT64_MIN);
  CuAssertInt64Equals(tc, INT64_MIN, mrt_integer_get(MRT_INTEGER(i)));
  mrt_value_unref(i);

  // upper bounds
  i = mrt_integer_new(INT64_MAX);
  CuAssertInt64Equals(tc, INT64_MAX, mrt_integer_get(MRT_INTEGER(i)));
  mrt_value_unref(i);
}

CuSuite* mrt_integer_get_test_suite(void)
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, test_mrt_integer);

    return &suite;
}
