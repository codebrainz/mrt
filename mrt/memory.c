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
  MRT_AllocatorAllocFunc alloc;
  MRT_AllocatorReallocFunc realloc;
  MRT_AllocationFreeFunc free;
}
MRT_Allocator;

typedef size_t MRT_MemHeader;

#define PTR_TO_HDR(ptr) (((MRT_MemHeader*)(ptr)) - 1)
#define HDR_TO_PTR(hdr) ((void*)(((MRT_MemHeader*)(ptr)) + 1))

#define MRT_DEFAULT_ALLOC malloc
#define MRT_DEFAULT_REALLOC realloc
#define MRT_DEFAULT_FREE free

static MRT_Allocator mrt_allocator = {
  MRT_DEFAULT_ALLOC,
  MRT_DEFAULT_REALLOC,
  MRT_DEFAULT_FREE
};

void mrt_set_allocator(MRT_AllocatorAllocFunc alloc_fn,
  MRT_AllocatorReallocFunc realloc_fn, MRT_AllocationFreeFunc free_fn)
{
  if (!alloc_fn && !realloc_fn && !free_fn) {
    mrt_allocator.alloc = MRT_DEFAULT_ALLOC;
    mrt_allocator.realloc = MRT_DEFAULT_REALLOC;
    mrt_allocator.free = MRT_DEFAULT_FREE;
  } else if (alloc_fn && realloc_fn && free_fn) {
    mrt_allocator.alloc = alloc_fn;
    mrt_allocator.realloc = realloc_fn;
    mrt_allocator.free = free_fn;
  } else {
#ifndef NDEBUG
    fprintf(stderr,
           "Invalid arguments to `mrt_set_allocator()`, "
           "all arguments must either be `NULL' or they all "
           "must not be `NULL'. Not changing.\n");
#endif
  }
}

void *mrt_malloc(size_t sz)
{
  void *ptr;
  if (sz == 0)
    return NULL;
  ptr = mrt_allocator.alloc(sz + sizeof(MRT_MemHeader));
  if (ptr) {
    MRT_MemHeader *hdr = ptr;
    *hdr = sz;
    ptr = HDR_TO_PTR(hdr);
    mrt_memclear(ptr);
    printf("Allocated '%lu' bytes\n", sz);
    return ptr;
  }
  return NULL;
}

void *mrt_realloc(void *ptr, size_t sz)
{
  size_t old_sz;
  MRT_MemHeader *hdr;
  void *temp;
  if (!ptr)
    return mrt_malloc(sz);
  if (sz == 0) {
    mrt_free(ptr);
    return NULL;
  }
  hdr = PTR_TO_HDR(ptr);
  old_sz = *hdr;
  temp = mrt_allocator.realloc(hdr, sz + sizeof(MRT_MemHeader));
  if (!temp)
    return NULL;
  hdr = temp;
  *hdr = sz;
  ptr = HDR_TO_PTR(hdr);
  if (sz > old_sz)
    memset(ptr + old_sz, 0, sz - old_sz);
  printf("Reallocated '%lu' bytes to '%lu' bytes\n", old_sz, sz);
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

void mrt_zerofill(void *ptr, size_t start, size_t len)
{
  if (!ptr)
    return;
  if (len == (size_t)-1)
    len = *PTR_TO_HDR(ptr) - start;
  memset(ptr + start, 0, len);
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
