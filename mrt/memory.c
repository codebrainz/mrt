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

#include <mrt/memory.h>
#include <stdlib.h>
#include <string.h>

#ifndef NDEBUG
# include <stdio.h>
#endif

typedef struct
{
  MRT_AllocatorReallocFunc realloc;
  MRT_AllocationFreeFunc free;
}
MRT_Allocator;

typedef size_t MRT_MemHeader;

#define PTR_TO_HDR(ptr) (((MRT_MemHeader*)(ptr)) - 1)
#define HDR_TO_PTR(hdr) ((void*)(((MRT_MemHeader*)(hdr)) + 1))

#define MRT_DEFAULT_REALLOC realloc
#define MRT_DEFAULT_FREE free

static MRT_Allocator mrt_allocator = {
  MRT_DEFAULT_REALLOC,
  MRT_DEFAULT_FREE
};

bool mrt_set_allocator(MRT_AllocatorReallocFunc realloc_fn,
  MRT_AllocationFreeFunc free_fn)
{
  if (!realloc_fn && !free_fn) {
    mrt_allocator.realloc = MRT_DEFAULT_REALLOC;
    mrt_allocator.free = MRT_DEFAULT_FREE;
    return true;
  } else if (realloc_fn && free_fn) {
    mrt_allocator.realloc = realloc_fn;
    mrt_allocator.free = free_fn;
    return true;
  } else {
#if 0
    fprintf(stderr,
           "Invalid arguments to `mrt_set_allocator()`, "
           "all arguments must either be `NULL' or they all "
           "must not be `NULL'. Not changing.\n");
#endif
    return false;
  }
}

void *mrt_realloc(void *ptr, size_t sz)
{
  size_t old_sz;
  MRT_MemHeader *hdr;
  void *temp;

  // Resize to 0 means free()
  if (sz == 0) {
    mrt_free(ptr);
    return NULL;
  }

  // If ptr is NULL it's just like malloc()
  if (ptr != NULL) {
    hdr = PTR_TO_HDR(ptr);
    old_sz = *hdr;
  } else {
    hdr = NULL;
    old_sz = 0;
  }

  // Bail out if can't allocate sz (plus header size)
  temp = mrt_allocator.realloc(hdr, sz + sizeof(MRT_MemHeader));
  if (temp == NULL)
    return NULL;

  hdr = temp;
  *hdr = sz;
  ptr = HDR_TO_PTR(hdr);

  // Clear out additional bytes added, if any
  if (sz > old_sz)
    mrt_memclear_range(ptr, old_sz, (sz - old_sz));

  //printf("Reallocated '%lu' bytes to '%lu' bytes\n", old_sz, sz);

  return ptr;
}

void mrt_free(void *ptr)
{
  if (ptr) {
    mrt_memclear(ptr);
    mrt_allocator.free(PTR_TO_HDR(ptr));
  }
}

size_t mrt_memsize(void *ptr)
{
  if (!ptr)
    return 0;
  return *PTR_TO_HDR(ptr);
}

void mrt_memfill_range(void *ptr, size_t start, size_t len, uint8_t byte)
{
  size_t mem_size;
  if (!ptr)
    return;
  mem_size = *PTR_TO_HDR(ptr);
  if (len == (size_t)-1)
    len = mem_size - start;
  // Safety bounds checks
  if ((start+len) > mem_size)
    return;
  memset(((uint8_t*)ptr) + start, byte, len);
}

void *mrt_memdup(void *ptr)
{
  void *new_ptr;
  if (!ptr)
    return NULL;
  new_ptr = mrt_malloc(*PTR_TO_HDR(ptr));
  if (new_ptr)
    memcpy(new_ptr, ptr, *PTR_TO_HDR(ptr));
  return new_ptr;
}
