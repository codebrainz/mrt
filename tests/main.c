#include "CuTest.h"
#include <stdio.h>

extern CuSuite *m_memory_get_test_suite(void);
extern CuSuite* m_strutils_get_test_suite(void);
extern CuSuite* m_list_get_test_suite(void);
extern CuSuite* m_none_get_test_suite(void);
extern CuSuite* m_boolean_get_test_suite(void);
extern CuSuite* m_integer_get_test_suite(void);
extern CuSuite* m_real_get_test_suite(void);
extern CuSuite* m_string_get_test_suite(void);
extern CuSuite* m_pointer_get_test_suite(void);

int main()
{
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();

  CuSuiteAddSuite(suite, m_memory_get_test_suite());
  CuSuiteAddSuite(suite, m_strutils_get_test_suite());
  CuSuiteAddSuite(suite, m_list_get_test_suite());
  CuSuiteAddSuite(suite, m_none_get_test_suite());
  CuSuiteAddSuite(suite, m_boolean_get_test_suite());
  CuSuiteAddSuite(suite, m_integer_get_test_suite());
  CuSuiteAddSuite(suite, m_real_get_test_suite());
  CuSuiteAddSuite(suite, m_string_get_test_suite());
  CuSuiteAddSuite(suite, m_pointer_get_test_suite());

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);

  CuSuiteDelete(suite);
  CuStringDelete(output);
}
