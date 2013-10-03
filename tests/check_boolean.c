#include <mlib/boolean.h>
#include "CuTest.h"

void test_m_boolean(CuTest *tc)
{
  MObject *btrue, *bfalse;
  MObject *btrue2, *bfalse2;

  btrue = m_boolean_true();
  bfalse = m_boolean_false();

  CuAssertTrue(tc, M_IS_BOOLEAN(btrue));
  CuAssertTrue(tc, M_IS_BOOLEAN(bfalse));

  btrue2 = m_boolean_true();
  bfalse2 = m_boolean_false();

  CuAssertPtrEquals(tc, btrue, btrue2);
  CuAssertPtrEquals(tc, bfalse, bfalse2);

  btrue = m_boolean_new(true);
  CuAssertPtrEquals(tc, btrue2, btrue);
  CuAssertTrue(tc, m_boolean_is_true(btrue));
  m_object_unref(btrue);

  bfalse = m_boolean_new(false);
  CuAssertPtrEquals(tc, bfalse2, bfalse);
  CuAssertTrue(tc, m_boolean_is_false(bfalse));
  m_object_unref(bfalse);
}

CuSuite* m_boolean_get_test_suite(void)
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, test_m_boolean);

    return &suite;
}
