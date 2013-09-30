#include <mrt/none.h>
#include "CuTest.h"

void test_mrt_none(CuTest *tc)
{
  MRT_Value *none1, *none2;

  none1 = mrt_none();
  CuAssertPtrNotNull(tc, none1);

  none2 = mrt_none();
  CuAssertPtrNotNull(tc, none2);

  CuAssertTrue(tc, MRT_IS_NONE(none1));
  CuAssertTrue(tc, MRT_IS_NONE(none2));

  CuAssertPtrEquals(tc, none1, none2);

  mrt_value_unref(MRT_VALUE(none1));
  mrt_value_unref(MRT_VALUE(none2));
}

CuSuite* mrt_none_get_test_suite(void)
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, test_mrt_none);

    return &suite;
}
