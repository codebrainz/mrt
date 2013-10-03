
#include <mlib/none.h>

MAKE_TEST_FUNC(get)
{
#if 0
  MSeq *s;
  MObject *v_in, *v_out;

  s = m_list_new();

  // Single item get
  v_in = m_none();
  m_seq_add(s, 0, v_in);
  v_out = m_seq_get(s, 0);
  CuAssertPtrEquals(tc, v_in, v_out);



  m_object_unref(v_in);
  m_object_unref(M_OBJECT(s));
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
