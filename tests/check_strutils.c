#include <mrt/strutils.h>
#include <mrt/memory.h>
#include <string.h>
#include "CuTest.h"

// Also tests m_strdup() and sort of m_strlen() by proxy
void test_m_strndup(CuTest *tc)
{
  char *s;

  // Measured automatically
  s = m_strdup("Hello World");
  CuAssertStrEquals(tc, "Hello World", s);
  m_free(s);

  // Only the first part
  s = m_strndup("Hello World", 5);
  CuAssertStrEquals(tc, "Hello", s);
  m_free(s);

  // The whole thing
  s = m_strndup("Hello", 5);
  CuAssertStrEquals(tc, "Hello", s);
  m_free(s);

  // More than the string
  s = m_strndup("Hello", 100);
  CuAssertStrEquals(tc, "Hello", s);
  m_free(s);

  // Null returns NULL
  s = m_strndup(NULL, 100);
  CuAssertPtrNull(tc, s);

  // Empty string to empty string
  s = m_strndup("", 100);
  CuAssertStrEquals(tc, "", s);
  m_free(s);
}

// Also tests m_strdup_vprintf() since _printf() uses it
void test_m_strdup_printf(CuTest *tc)
{
  char *s;

  // Passing NULL returns NULL
  s = m_strdup_printf(NULL);
  CuAssertPtrNull(tc, s);

  // Passing empty string returns empty string
  s = m_strdup_printf("");
  CuAssertStrEquals(tc, "", s);
  m_free(s);

  // Passing a string with no args
  s = m_strdup_printf("Hello World");
  CuAssertStrEquals(tc, "Hello World", s);
  m_free(s);

  // Passing some format arguments
  s = m_strdup_printf("Hello %s, %d", "World", 123);
  CuAssertStrEquals(tc, "Hello World, 123", s);
  m_free(s);
}

void test_m_strlen(CuTest *tc)
{
  static const char *s = "Hello World";

  // NULL returns 0
  CuAssertIntEquals(tc, 0, m_strlen(NULL));

  // Empty string returns 0
  CuAssertIntEquals(tc, 0, m_strlen(""));

  // Matches stdlib strlen()
  CuAssertIntEquals(tc, strlen(s), m_strlen(s));

  // Peeking part-way into a string
  CuAssertIntEquals(tc, 5, m_strlen(s + 6));
}

void test_m_strcmp(CuTest *tc)
{
  CuAssertIntZero(tc, m_strcmp(NULL, NULL));
  CuAssertIntZero(tc, m_strcmp("", ""));
  CuAssertIntPositive(tc, m_strcmp("Hello", NULL));
  CuAssertIntNegative(tc, m_strcmp(NULL, "Hello"));
  CuAssertIntZero(tc, m_strcmp("Hello", "Hello"));
  CuAssertIntNegative(tc, m_strcmp("alpha", "zebra"));
  CuAssertIntPositive(tc, m_strcmp("zebra", "alpha"));
  CuAssertIntPositive(tc, m_strcmp("alpha", "Alpha"));
  CuAssertIntNegative(tc, m_strcmp("Zebra", "zebra"));
}

CuSuite* m_strutils_get_test_suite(void)
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, test_m_strndup);
    SUITE_ADD_TEST(&suite, test_m_strdup_printf);
    SUITE_ADD_TEST(&suite, test_m_strlen);
    SUITE_ADD_TEST(&suite, test_m_strcmp);

    return &suite;
}
