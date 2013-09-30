#include <mrt/boolean.h>
#include "CuTest.h"

void test_mrt_boolean(CuTest *tc)
{
  MRT_Object *btrue, *bfalse;
  MRT_Object *btrue2, *bfalse2;

  btrue = mrt_boolean_true();
  bfalse = mrt_boolean_false();

  CuAssertTrue(tc, MRT_IS_BOOLEAN(btrue));
  CuAssertTrue(tc, MRT_IS_BOOLEAN(bfalse));

  btrue2 = mrt_boolean_true();
  bfalse2 = mrt_boolean_false();

  CuAssertPtrEquals(tc, btrue, btrue2);
  CuAssertPtrEquals(tc, bfalse, bfalse2);

  btrue = mrt_boolean_new(true);
  CuAssertPtrEquals(tc, btrue2, btrue);
  CuAssertTrue(tc, mrt_boolean_is_true(btrue));
  mrt_object_unref(btrue);

  bfalse = mrt_boolean_new(false);
  CuAssertPtrEquals(tc, bfalse2, bfalse);
  CuAssertTrue(tc, mrt_boolean_is_false(bfalse));
  mrt_object_unref(bfalse);
}

CuSuite* mrt_boolean_get_test_suite(void)
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, test_mrt_boolean);

    return &suite;
}
