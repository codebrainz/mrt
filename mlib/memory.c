/*
 * Copyright (c) 2013 Matthew Brush <mbrush@codebrainz.ca>
 *
 * Permission is hereby granted, free of charge, to any person
 * obtaining a copy of this software and associated documentation
 * files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be
 *   included in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <mlib/memory.h>
#include <stdlib.h>
#include <string.h>

// Undefine to disable memory sanity checks
#define MEM_CHECKS 1

// Undefine to not zero-out memory (not recommended)
#define ZERO_MEMORY 1

typedef struct
{
  MAllocatorReallocFunc realloc;
  MAllocationFreeFunc free;
}
MAllocator;

#define M_DEFAULT_REALLOC realloc
#define M_DEFAULT_FREE    free

static MAllocator m_allocator = {
  M_DEFAULT_REALLOC,
  M_DEFAULT_FREE
};

#define MEM_FLAG_NONE   0x00
#define MEM_FLAG_OBJECT 0x01

typedef struct MemHeader
{
  uint32_t size;
  uint16_t magic;
  uint8_t flags;
  uint8_t reserved_;
}
MemHeader;

#define MEM_TO_HDR(mem)    ((MemHeader*)(mem)-1)
#define HDR_TO_MEM(hdr)    ((void*)((MemHeader*)(hdr)+1))
#define MEM_HDR_SIZE(mem)  MEM_TO_HDR(mem)->size
#define MEM_HDR_FLAGS(mem) MEM_TO_HDR(mem)->flags
#define MEM_HDR_MAGIC      0xA55A
#define MEM_VALID(mem)     (MEM_TO_HDR(mem)->magic == MEM_HDR_MAGIC)
#define MEM_OVERHEAD       (sizeof(MemHeader))

#if defined(MEM_CHECKS)
# include <stdio.h>
# define MEM_CHECK(mem)                                             \
  do {                                                              \
    if (!MEM_VALID(mem)) {                                          \
      fprintf(stderr, __FILE__ ":%d: memory corruptiond detected, " \
              "aborting.\n", __LINE__);                             \
      abort();                                                      \
    }                                                               \
  } while(0)
#else
# define MEM_CHECK(mem) do { } while(0)
#endif

bool m_set_allocator(MAllocatorReallocFunc realloc_fn,
  MAllocationFreeFunc free_fn)
{
  if (!realloc_fn && !free_fn) {
    m_allocator.realloc = M_DEFAULT_REALLOC;
    m_allocator.free = M_DEFAULT_FREE;
    return true;
  } else if (realloc_fn && free_fn) {
    m_allocator.realloc = realloc_fn;
    m_allocator.free = free_fn;
    return true;
  } else {
#if 0
    fprintf(stderr,
           "Invalid arguments to `m_set_allocator()`, "
           "all arguments must either be `NULL' or they all "
           "must not be `NULL'. Not changing.\n");
#endif
    return false;
  }
}

void *m_realloc(void *ptr, size_t sz)
{
  size_t old_sz;
  void *temp;
  MemHeader *hdr;

  // Resize to 0 means free()
  if (sz == 0) {
    m_free(ptr);
    return NULL;
  }

  if (ptr != NULL) {
    MEM_CHECK(ptr);
    hdr = MEM_TO_HDR(ptr);
    old_sz = hdr->size;
  } else {
    hdr = NULL;
    old_sz = 0;
  }

  temp = m_allocator.realloc(hdr, sz + MEM_OVERHEAD);
  if (temp == NULL)
    return NULL;

  hdr = temp;
  hdr->size = sz;
  if (ptr == NULL)
    hdr->magic = MEM_HDR_MAGIC;
  ptr = HDR_TO_MEM(hdr);

#ifdef ZERO_MEMORY
  // Clear out additional bytes added, if any
  if (sz > old_sz)
    m_memclear_range(ptr, old_sz, (sz - old_sz));
#endif

  MEM_CHECK(ptr);

  return ptr;
}

void m_free(void *ptr)
{
  if (!ptr)
    return;

  MEM_CHECK(ptr);

#ifdef ZERO_MEMORY
  memset(MEM_TO_HDR(ptr), 0, MEM_HDR_SIZE(ptr) + MEM_OVERHEAD);
#endif

  m_allocator.free(MEM_TO_HDR(ptr));
}

size_t m_memsize(const void *ptr)
{
  if (!ptr)
    return 0;

  MEM_CHECK(ptr);

  return MEM_HDR_SIZE(ptr);
}

void m_memfill_range(void *ptr, size_t start, size_t len, uint8_t byte)
{
  size_t mem_size;
  if (!ptr)
    return;
  mem_size = MEM_HDR_SIZE(ptr);
  if (len == (size_t)-1)
    len = mem_size - start;
  // Safety bounds checks
  if ((start+len) > mem_size)
    return;
  memset(((uint8_t*)ptr) + start, byte, len);
}

void *m_memdup(const void *ptr)
{
  void *new_ptr;
  if (!ptr)
    return NULL;
  new_ptr = m_malloc(MEM_HDR_SIZE(ptr));
  if (new_ptr)
    memcpy((uint8_t*)new_ptr, (uint8_t*)ptr, MEM_HDR_SIZE(ptr));
  return new_ptr;
}

void *m_calloc(size_t n, size_t sz)
{
  size_t size = n * sz;
#if !defined(ZERO_MEMORY)
  void *ptr = m_malloc(size);
  memset(ptr, 0, size);
  return ptr;
#else
  return m_malloc(size);
#endif
}

void m_alloc_object(size_t sz)
{
  void *ptr = m_calloc(1, sz);
  if (ptr)
    MEM_HDR_FLAGS(ptr) |= MEM_FLAG_OBJECT;
}

bool m_mem_is_object(void *ptr)
{
  if (!ptr)
    return false;
  MEM_CHECK(ptr);
  return MEM_HDR_SIZE(ptr);
}

void m_mem_set_is_object(void *ptr, bool is_object)
{
  if (!ptr)
    return;
  MEM_CHECK(ptr);
  if (is_object)
    MEM_HDR_FLAGS(ptr) |= MEM_FLAG_OBJECT;
  else
    MEM_HDR_FLAGS(ptr) &= ~MEM_FLAG_OBJECT;
}
