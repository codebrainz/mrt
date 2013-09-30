#include <mrt/string.h>
#include <mrt/strutils.h>
#include "CuTest.h"

void test_m_string(CuTest *tc)
{
  (void)tc;
#if 0 // FIXME
  MObject *str;

  str = m_string_new("Hello");
  CuAssertTrue(tc, M_IS_STRING(str));
  CuAssertIntEquals(tc, 5, m_string_length(M_STRING(str)));
  CuAssertStrEquals(tc, "Hello", m_string_get(M_STRING(str)));

  m_string_set(M_STRING(str), "Hello World");
  CuAssertIntEquals(tc, m_strlen("Hello World"), m_string_length(M_STRING(str)));
  CuAssertStrEquals(tc, "Hello World", m_string_get(M_STRING(str)));

  m_object_unref(str);
#endif
}

CuSuite* m_string_get_test_suite(void)
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, test_m_string);

    return &suite;
}
