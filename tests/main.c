#include "CuTest.h"
#include <stdio.h>

extern CuSuite *mrt_malloc_get_test_suite(void);

int main()
{
  CuString *output = CuStringNew();
  CuSuite* suite = CuSuiteNew();

  CuSuiteAddSuite(suite, mrt_malloc_get_test_suite());

  CuSuiteRun(suite);
  CuSuiteSummary(suite, output);
  CuSuiteDetails(suite, output);
  printf("%s\n", output->buffer);

  CuSuiteDelete(suite);
}
