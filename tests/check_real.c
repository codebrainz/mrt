#include <mrt/real.h>
#include <float.h>
#include "CuTest.h"

void test_mrt_real(CuTest *tc)
{
  MRT_Value *r;
  double delta = 0.00001; // FIXME

  // is real and is number
  r = mrt_real_new(123.00);
  CuAssertTrue(tc, MRT_IS_REAL(r));
  CuAssertTrue(tc, MRT_IS_NUMBER(r));
  mrt_value_unref(r);

  // zero
  r = mrt_real_new(0.0);
  CuAssertDblEquals(tc, 0, mrt_real_get(MRT_REAL(r)), delta);
  mrt_value_unref(r);

  // positive number
  r = mrt_real_new(200);
  CuAssertDblEquals(tc, 200, mrt_real_get(MRT_REAL(r)), delta);
  mrt_value_unref(r);

  // negative number
  r = mrt_real_new(-200);
  CuAssertDblEquals(tc, -200, mrt_real_get(MRT_REAL(r)), delta);
  mrt_value_unref(r);

  // lower bounds
  r = mrt_real_new(DBL_MIN);
  CuAssertDblEquals(tc, DBL_MIN, mrt_real_get(MRT_REAL(r)), delta);
  mrt_value_unref(r);

  // upper bounds
  r = mrt_real_new(DBL_MAX);
  CuAssertDblEquals(tc, DBL_MAX, mrt_real_get(MRT_REAL(r)), delta);
  mrt_value_unref(r);
}

CuSuite* mrt_real_get_test_suite(void)
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, test_mrt_real);

    return &suite;
}
