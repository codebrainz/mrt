
#include <mrt/none.h>

MAKE_TEST_FUNC(get)
{
#if 0
  MRT_Seq *s;
  MRT_Value *v_in, *v_out;

  s = mrt_list_new();

  // Single item get
  v_in = mrt_none();
  mrt_seq_add(s, 0, v_in);
  v_out = mrt_seq_get(s, 0);
  CuAssertPtrEquals(tc, v_in, v_out);



  mrt_value_unref(v_in);
  mrt_value_unref(MRT_VALUE(s));
#endif
  (void)tc;
}

MAKE_TEST_FUNC(set)
{
  (void)tc;
}

MAKE_TEST_FUNC(add)
{
  (void)tc;
}

MAKE_TEST_FUNC(del)
{
  (void)tc;
}

MAKE_TEST_FUNC(size)
{
  (void)tc;
}

MAKE_TEST_FUNC(first)
{
  (void)tc;
}

MAKE_TEST_FUNC(last)
{
  (void)tc;
}

MAKE_SUITE_GETTER
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, MAKE_TEST_FUNC_NAME(get));
    SUITE_ADD_TEST(&suite, MAKE_TEST_FUNC_NAME(set));
    SUITE_ADD_TEST(&suite, MAKE_TEST_FUNC_NAME(add));
    SUITE_ADD_TEST(&suite, MAKE_TEST_FUNC_NAME(del));
    SUITE_ADD_TEST(&suite, MAKE_TEST_FUNC_NAME(size));
    SUITE_ADD_TEST(&suite, MAKE_TEST_FUNC_NAME(first));
    SUITE_ADD_TEST(&suite, MAKE_TEST_FUNC_NAME(last));

    return &suite;
}
