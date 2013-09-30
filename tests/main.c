#include "CuTest.h"
#include <stdio.h>

extern CuSuite *mrt_memory_get_test_suite(void);
extern CuSuite* mrt_strutils_get_test_suite(void);
extern CuSuite* mrt_list_get_test_suite(void);
extern CuSuite* mrt_none_get_test_suite(void);
extern CuSuite* mrt_boolean_get_test_suite(void);
extern CuSuite* mrt_integer_get_test_suite(void);
extern CuSuite* mrt_real_get_test_suite(void);
extern CuSuite* mrt_string_get_test_suite(void);

int main()
{
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();

  CuSuiteAddSuite(suite, mrt_memory_get_test_suite());
  CuSuiteAddSuite(suite, mrt_strutils_get_test_suite());
  CuSuiteAddSuite(suite, mrt_list_get_test_suite());
  CuSuiteAddSuite(suite, mrt_none_get_test_suite());
  CuSuiteAddSuite(suite, mrt_boolean_get_test_suite());
  CuSuiteAddSuite(suite, mrt_integer_get_test_suite());
  CuSuiteAddSuite(suite, mrt_real_get_test_suite());
  CuSuiteAddSuite(suite, mrt_string_get_test_suite());

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);

  CuSuiteDelete(suite);
  CuStringDelete(output);
}
