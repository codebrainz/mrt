#include <mrt/pointer.h>
#include "CuTest.h"

struct TestData
{
  int count;
};

static void *fake_ptr_copy(const void *ptr)
{
  struct TestData *dat = (struct TestData*) ptr;
  dat->count++;
  return dat;
}

static void fake_ptr_free(void *ptr)
{
  struct TestData *dat = ptr;
  dat->count--;
}

void test_m_pointer(CuTest *tc)
{
  struct TestData dat = {1}; // inc
  MObject *obj = m_pointer_new(&dat, fake_ptr_copy, fake_ptr_free);
  MPointer *p = M_POINTER(obj);
  MPointer *p2;

  // Test getting and setting the pointer and NULL
  CuAssertTrue(tc, M_IS_POINTER(obj));
  CuAssertPtrEquals(tc, &dat, m_pointer_get(p));
  m_pointer_set(p, NULL);
  CuAssertPtrNull(tc, m_pointer_get(p));
  m_pointer_set(p, &dat);
  CuAssertPtrEquals(tc, &dat, m_pointer_get(p));

  // Test copy
  p2 = M_POINTER(m_object_copy(M_OBJECT(obj))); // inc
  CuAssertTrue(tc, M_IS_POINTER(obj));
  CuAssertPtrEquals(tc, &dat, m_pointer_get(p2));
  CuAssertIntEquals(tc, 2, dat.count);

  // Test free
  m_object_unref(M_OBJECT(p2)); // dec
  CuAssertIntEquals(tc, 1, dat.count);
  m_object_unref(M_OBJECT(p)); // dec
  CuAssertIntEquals(tc, 0, dat.count);
}

CuSuite* m_pointer_get_test_suite(void)
{
  static CuSuite suite;

  CuSuiteInit(&suite);

  SUITE_ADD_TEST(&suite, test_m_pointer);

  return &suite;
}
