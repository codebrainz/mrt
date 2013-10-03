#include <mlib/real.h>
#include <float.h>
#include "CuTest.h"

void test_m_real(CuTest *tc)
{
  MObject *r;
  double delta = 0.00001; // FIXME

  // is real and is number
  r = m_real_new(123.00);
  CuAssertTrue(tc, M_IS_REAL(r));
  CuAssertTrue(tc, M_IS_NUMBER(r));
  m_object_unref(r);

  // zero
  r = m_real_new(0.0);
  CuAssertDblEquals(tc, 0, m_real_get(M_REAL(r)), delta);
  m_object_unref(r);

  // positive number
  r = m_real_new(200);
  CuAssertDblEquals(tc, 200, m_real_get(M_REAL(r)), delta);
  m_object_unref(r);

  // negative number
  r = m_real_new(-200);
  CuAssertDblEquals(tc, -200, m_real_get(M_REAL(r)), delta);
  m_object_unref(r);

  // lower bounds
  r = m_real_new(DBL_MIN);
  CuAssertDblEquals(tc, DBL_MIN, m_real_get(M_REAL(r)), delta);
  m_object_unref(r);

  // upper bounds
  r = m_real_new(DBL_MAX);
  CuAssertDblEquals(tc, DBL_MAX, m_real_get(M_REAL(r)), delta);
  m_object_unref(r);
}

CuSuite* m_real_get_test_suite(void)
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, test_m_real);

    return &suite;
}
