#include <mlib/none.h>
#include "CuTest.h"

void test_m_none(CuTest *tc)
{
  MObject *none1, *none2;

  none1 = m_none();
  CuAssertPtrNotNull(tc, none1);

  none2 = m_none();
  CuAssertPtrNotNull(tc, none2);

  CuAssertTrue(tc, M_IS_NONE(none1));
  CuAssertTrue(tc, M_IS_NONE(none2));

  CuAssertPtrEquals(tc, none1, none2);

  m_object_unref(M_OBJECT(none1));
  m_object_unref(M_OBJECT(none2));
}

CuSuite* m_none_get_test_suite(void)
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, test_m_none);

    return &suite;
}
