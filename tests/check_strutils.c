#include <mrt/strutils.h>
#include <mrt/memory.h>
#include <string.h>
#include "CuTest.h"

// Also tests mrt_strdup() and sort of mrt_strlen() by proxy
void test_mrt_strndup(CuTest *tc)
{
  char *s;

  // Measured automatically
  s = mrt_strdup("Hello World");
  CuAssertStrEquals(tc, "Hello World", s);
  mrt_free(s);

  // Only the first part
  s = mrt_strndup("Hello World", 5);
  CuAssertStrEquals(tc, "Hello", s);
  mrt_free(s);

  // The whole thing
  s = mrt_strndup("Hello", 5);
  CuAssertStrEquals(tc, "Hello", s);
  mrt_free(s);

  // More than the string
  s = mrt_strndup("Hello", 100);
  CuAssertStrEquals(tc, "Hello", s);
  mrt_free(s);

  // Null returns NULL
  s = mrt_strndup(NULL, 100);
  CuAssertPtrNull(tc, s);

  // Empty string to empty string
  s = mrt_strndup("", 100);
  CuAssertStrEquals(tc, "", s);
  mrt_free(s);
}

// Also tests mrt_strdup_vprintf() since _printf() uses it
void test_mrt_strdup_printf(CuTest *tc)
{
  char *s;

  // Passing NULL returns NULL
  s = mrt_strdup_printf(NULL);
  CuAssertPtrNull(tc, s);

  // Passing empty string returns empty string
  s = mrt_strdup_printf("");
  CuAssertStrEquals(tc, "", s);
  mrt_free(s);

  // Passing a string with no args
  s = mrt_strdup_printf("Hello World");
  CuAssertStrEquals(tc, "Hello World", s);
  mrt_free(s);

  // Passing some format arguments
  s = mrt_strdup_printf("Hello %s, %d", "World", 123);
  CuAssertStrEquals(tc, "Hello World, 123", s);
  mrt_free(s);
}

void test_mrt_strlen(CuTest *tc)
{
  static const char *s = "Hello World";

  // NULL returns 0
  CuAssertIntEquals(tc, 0, mrt_strlen(NULL));

  // Empty string returns 0
  CuAssertIntEquals(tc, 0, mrt_strlen(""));

  // Matches stdlib strlen()
  CuAssertIntEquals(tc, strlen(s), mrt_strlen(s));

  // Peeking part-way into a string
  CuAssertIntEquals(tc, 5, mrt_strlen(s + 6));
}

void test_mrt_strcmp(CuTest *tc)
{
  CuAssertIntZero(tc, mrt_strcmp(NULL, NULL));
  CuAssertIntZero(tc, mrt_strcmp("", ""));
  CuAssertIntPositive(tc, mrt_strcmp("Hello", NULL));
  CuAssertIntNegative(tc, mrt_strcmp(NULL, "Hello"));
  CuAssertIntZero(tc, mrt_strcmp("Hello", "Hello"));
  CuAssertIntNegative(tc, mrt_strcmp("alpha", "zebra"));
  CuAssertIntPositive(tc, mrt_strcmp("zebra", "alpha"));
  CuAssertIntPositive(tc, mrt_strcmp("alpha", "Alpha"));
  CuAssertIntNegative(tc, mrt_strcmp("Zebra", "zebra"));
}

CuSuite* mrt_strutils_get_test_suite(void)
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, test_mrt_strndup);
    SUITE_ADD_TEST(&suite, test_mrt_strdup_printf);
    SUITE_ADD_TEST(&suite, test_mrt_strlen);
    SUITE_ADD_TEST(&suite, test_mrt_strcmp);

    return &suite;
}
