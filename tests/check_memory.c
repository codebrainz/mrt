#include <mrt/memory.h>
#include <stdlib.h>
#include <stdint.h>
#include <limits.h>
#include <time.h>
#include "CuTest.h"

// Fake functions for testing mrt_set_allocator()
static void *fake_test_realloc(void *ptr, size_t sz) { return realloc(ptr, sz); }
static void fake_test_free(void *ptr) { free(ptr); }

void test_mrt_set_allocator_custom(CuTest *tc)
{
  bool result;

  // Custom functions
  result = mrt_set_allocator(fake_test_realloc, fake_test_free);
  CuAssertTrue(tc, result);

  // Invalid to not set all functions
  result = mrt_set_allocator(NULL, fake_test_free);
  CuAssertFalse(tc, result);

  // Default functions
  result = mrt_set_allocator(NULL, NULL);
  CuAssertTrue(tc, result);
}

// Also tests mrt_malloc() since it's just a wrapper if mrt_realloc()
void test_mrt_realloc(CuTest *tc)
{
  void *chunk, *chunk2;
  uint8_t *bytes;
  size_t i, size, size2;

// test mrt_malloc()

  // Zero size makes NULL ptr
  chunk = mrt_malloc(0);
  CuAssertPtrNull(tc, chunk);

  // Small allocation
  chunk = mrt_malloc(8);
  CuAssertPtrNotNull(tc, chunk);
  CuAssertIntEquals(tc, 8, mrt_memsize(chunk));
  mrt_free(chunk);

  // "Large"(er) allocation
  chunk = mrt_malloc(UINT16_MAX);
  CuAssertPtrNotNull(tc, chunk);
  CuAssertIntEquals(tc, UINT16_MAX, mrt_memsize(chunk));

  bytes = (uint8_t*) chunk;
  size = mrt_memsize(chunk);

  // That each byte is zeroed out (and can be read)
  for (i = 0; i < size; i++)
    CuAssertIntEquals(tc, 0, bytes[i]);

  // That each byte can be set
  for (i = 0; i < size; i++)
    bytes[i] = UINT8_MAX;

  // That each byte hold the value just set
  for (i = 0; i < size; i++)
    CuAssertIntEquals(tc, UINT8_MAX, bytes[i]);

// test mrt_realloc()

  // Make it a bit bigger
  size2 = size + UINT8_MAX;
  chunk2 = mrt_realloc(chunk, size2);
  CuAssertPtrNotNull(tc, chunk2);
  CuAssertIntEquals(tc, size2, mrt_memsize(chunk2));
  chunk = chunk2;
  bytes = (uint8_t*) chunk;

  // That each byte hold the value just set before the resize
  for (i = 0; i < size; i++)
    CuAssertIntEquals(tc, UINT8_MAX, bytes[i]);

  // That each new byte is zeroed out, can be read, and can be set
  for (i = size; i < size2; i++) {
    CuAssertIntEquals(tc, 0, bytes[i]);
    bytes[i] = UINT8_MAX;
  }

  size = size2;

  // That each byte now holds the value expected
  for (i = 0; i < size; i++)
    CuAssertIntEquals(tc, UINT8_MAX, bytes[i]);

  // Test shrink the memory
  size2 = UINT8_MAX;
  chunk2 = mrt_realloc(chunk, size2);
  CuAssertPtrNotNull(tc, chunk2);
  chunk = chunk2;
  bytes = chunk;
  CuAssertIntEquals(tc, size2, mrt_memsize(chunk));
  size = size2;

  // That each byte still holds the value expected
  for (i = 0; i < size; i++)
    CuAssertIntEquals(tc, UINT8_MAX, bytes[i]);

  mrt_free(chunk);
}

// Also tested out a bit in test_mrt_realloc()
void test_mrt_memsize(CuTest *tc)
{
  void *chunk = NULL;
  const size_t max_size = UINT8_MAX;
  size_t i;

  // Passing NULL returns 0.
  CuAssertIntEquals(tc, 0, mrt_memsize(NULL));

  // Try resizing to a bunch of different sizes and checking the
  // resulting mem size.
  for (i = 1; i < max_size; i++) {
    chunk = mrt_realloc(chunk, i);
    CuAssertPtrNotNull(tc, chunk);
    CuAssertIntEquals(tc, i, mrt_memsize(chunk));
  }

  mrt_free(chunk);
}

// Includes mrt_memclear(), mrt_memfill(), mrt_memclear_range()
void test_mrt_memfill_range(CuTest *tc)
{
  void *chunk;
  uint8_t *bytes;
  size_t i, len, start, size = UINT8_MAX;

  // check if it crashes will null ptr
  mrt_memfill_range(NULL, 0, (size_t)-1, UINT8_MAX);

  chunk = mrt_malloc(size);
  CuAssertPtrNotNull(tc, chunk);
  CuAssertIntEquals(tc, size, mrt_memsize(chunk));

  // check setting the whole thing
  mrt_memfill_range(chunk, 0, (size_t)-1, UINT8_MAX);
  bytes = chunk;

  // check each byte was set
  for (i = 0; i < size; i++)
    CuAssertIntEquals(tc, UINT8_MAX, bytes[i]);

  // check setting a subset
  start = 25;
  len = 43;
  mrt_memfill_range(chunk, start, len, 133);

  // check each byte in range was set
  for (i = 0; i < size; i++) {
    if (i >= start && i < (start + len))
      CuAssertIntEquals(tc, 133, bytes[i]);
    else
      CuAssertIntEquals(tc, UINT8_MAX, bytes[i]);
  }

  // check it doesn't crash with out of range values
  mrt_memfill_range(chunk, size+20, 1, 0);
  mrt_memfill_range(chunk, 0, (size * 2), 0);
  mrt_memfill_range(chunk, 1, size, 0);
  mrt_memfill_range(chunk, 0, size+1, 0);

  mrt_free(chunk);
}

void test_mrt_memdup(CuTest *tc)
{
  void *chunk, *chunk2;
  uint8_t *bytes, *bytes2;
  size_t i, size = UINT8_MAX;

  // Passing NULL returns NULL
  CuAssertPtrNull(tc, mrt_memdup(NULL));

  chunk = mrt_malloc(size);
  CuAssertPtrNotNull(tc, chunk);
  CuAssertIntEquals(tc, size, mrt_memsize(chunk));
  bytes = chunk;

  mrt_memclear(chunk);

  // Fill it with pseudo random junk
  srand(time(NULL));
  for (i = 0; i < size; i++)
    bytes[i] = rand() % 256;

  chunk2 = mrt_memdup(chunk);
  CuAssertPtrNotNull(tc, chunk2);
  CuAssertIntEquals(tc, size, mrt_memsize(chunk2));
  bytes2 = chunk2;

  // Check it contains the same random junk
  for (i = 0; i < size; i++)
    CuAssertIntEquals(tc, bytes[i], bytes2[i]);

  mrt_free(chunk);
  mrt_free(chunk2);
}

CuSuite* mrt_memory_get_test_suite(void)
{
    static CuSuite suite;

    CuSuiteInit(&suite);

    SUITE_ADD_TEST(&suite, test_mrt_set_allocator_custom);
    SUITE_ADD_TEST(&suite, test_mrt_realloc);
    SUITE_ADD_TEST(&suite, test_mrt_memsize);
    SUITE_ADD_TEST(&suite, test_mrt_memfill_range);
    SUITE_ADD_TEST(&suite, test_mrt_memdup);

    return &suite;
}
