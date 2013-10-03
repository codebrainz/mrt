#include <mlib/integer.h>
#include "CuTest.h"

void test_m_integer(CuTest *tc)
{
  MObject *i;

  // is integer and is number
  i = m_integer_new(123);
  CuAssertTrue(tc, M_IS_INTEGER(i));
  CuAssertTrue(tc, M_IS_NUMBER(i));
  m_object_unref(i);

  // zero
  i = m_integer_new(0);
  CuAssertInt64Equals(tc, 0, m_integer_get(M_INTEGER(i)));
  m_object_unref(i);

  // positive number
  i = m_integer_new(200);
  CuAssertInt64Equals(tc, 200, m_integer_get(M_INTEGER(i)));
  m_object_unref(i);

  // negative number
  i = m_integer_new(-200);
  CuAssertInt64Equals(tc, -200, m_integer_get(M_INTEGER(i)));
  m_object_unref(i);

  // lower bounds
  i = m_integer_new(INT64_MIN);
  CuAssertInt64Equals(tc, INT64_MIN, m_integer_get(M_INTEGER(i)));
  m_object_unref(i);

  // upper bounds
  i = m_integer_new(INT64_MAX);
  CuAssertInt64Equals(tc, INT64_MAX, m_integer_get(M_INTEGER(i)));
  m_object_unref(i);
}

CuSuite* m_integer_get_test_suite(void)
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, test_m_integer);

    return &suite;
}
