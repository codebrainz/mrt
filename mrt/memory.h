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

/**
 * @file mrt/memory.h
 * @brief Memory-related functions.
 * @copyright 2013 Matthew Brush <mbrush@codebrainz.ca>
 *
 * These functions provide usual allocation routines but all of the
 * memory allocated has a special header (size of `sizeof(size_t)`)
 * that holds the size of the allocated memory. This allows some
 * helpful functionality in terms of zeroing out the memory and
 * providing a certain amount of safety, independent of the actual
 * allocator used.
 *
 * @note All MRT functions that return or release allocated memory
 * will use these functions internally.
 *
 * @warning The functions passed to and returned from the memory
 * functions are always the chunk of memory usable by the user, and
 * just before them is the header containing the allocation size.
 * It's *SUPER* important that you don't mix and match memory chunks
 * allocated by these functions and those allocated by other functions
 * (for ex. stdlib malloc/free/strdup/etc). The trade-off is ~8 bytes
 * of overhead per allocation for the header in exchange for a certain
 * amount of safety and convenience.
 */

#ifndef MRT_MEMORY_H
#define MRT_MEMORY_H

#include <mrt/macros.h>
#include <mrt/basictypes.h>

MRT_BEGIN_CDECLS

/** One higher than the maximum amount of memory that can be allocated.
 * used as a special obj where size_t is passed/returned. */
#define MRT_SIZE_MAX ((size_t)-1)

/**
 * Memory resizing function.
 *
 * Must allocate new memory when @a ptr is @c NULL.
 *
 * @param ptr The memory to resize or @c NULL to allocate new memory.
 * @param sz The new size.
 * @return The resized memory.
 */
typedef void* (*MRT_AllocatorReallocFunc) (void *ptr, size_t sz);

/**
 * Memory releasing function.
 *
 * @param ptr The memory to free.
 */
typedef void (*MRT_AllocationFreeFunc) (void *ptr);

/**
 * Set the allocation, reallocation and deallocation functions.
 *
 * @warning You must either set *all* of these functions or set them
 * all to @c NULL for the default allocator. Not setting all of the
 * functions results in undefined behaviour. No mix-and-match
 * allocation functions will be infered.
 *
 * @param alloc_fn The function that allocates a given number of bytes
 * and zero-fills it. It must return @c NULL when no more memory is
 * available.
 * @param realloc_fn The function that re-allocates a given pointer
 * to a given number of bytes and zero-fills any additonal memory
 * added. It must return @c NULL when no more memory is available.
 * @param free_fn The function that frees/release the given pointer
 * after zeroing-out it's memory. It must do nothing when @c NULL is
 * passed to it.
 * @return @c true if the allocator functions were set, @c false
 * otherwise.
 */
bool mrt_set_allocator(MRT_AllocatorReallocFunc realloc_fn,
  MRT_AllocationFreeFunc free_fn);

/**
 * Allocate @a sz bytes of memory.
 *
 * @note The memory will be zero-filled.
 * @warning The return pointer has before it a special header that
 * MRT uses to track the size of the memory allocation. You *MUST*
 * free this memory using the special mrt_free() function and never
 * with any other free function (ie. stdlib free()).
 *
 * @param sz The size of the memory to allocate.
 * @return A pointer to the newly allocated memory which *MUST* be
 * released when no longer needed using the mrt_free() function. If
 * no more memory can be allocated, @c NULL will be returned.
 */
#define mrt_malloc(sz) mrt_realloc(NULL, (sz))

/**
 * Resize @a ptr to @a sz.
 *
 * @note If the new size is larger than the old size, the addition
 * memory will be zero-filled.
 * @warning The return pointer has before it a special header that
 * MRT uses to track the size of the memory allocation. You *MUST*
 * free this memory using the special mrt_free() function and never
 * with any other free function (ie. stdlib free()).
 *
 * @param ptr The pointer to the memory to resize.
 * @param sz The new size of the memory.
 * @return A pointer to the resized memory or @c NULL of not enough
 * memory is available.
 */
void *mrt_realloc(void *ptr, size_t sz);

/**
 * Release allocated memory at @a ptr.
 *
 * @note You can pass @a ptr as @c NULL to this function and it will
 * do nothing, but why would you?
 * @warning The pointer must point to memory allocated with one of
 * the `mrt_*()` memory allocation functions since it contains a
 * special header that holds the size of the allocation. *DO NOT* pass
 * pointers to this function that were not allocated with the
 * `mrt_*()` allocation functions.
 *
 * @param ptr The memory to release.
 */
void mrt_free(void *ptr);

/**
 * Return the size of an allocated memory chunk.
 *
 * @param ptr Pointer to a chunk of memory allocated with one of the
 * `mrt_*()` memory allocation functions.
 * @return The size of the memory chunk or @c NULL if @a ptr is @c NULL.
 */
size_t mrt_memsize(const void *ptr);

/**
 * Fill a range of a chunk of memory with a specific byte.
 *
 * @param ptr Pointer to the chunk of memory allocated with one of the
 * `mrt_*()` memory allocation functions.
 * @param start The start address to zero-fill.
 * @param len The number of bytes to zero-fill. If @a len is equal
 * to @c SIZE_MAX (ie. ((size_t)-1)) then all of the memory from the
 * @a start to the end of the memory will be zero-filled.
 * @param byte The byte to put into each byte of the range of the memory.
 */
void mrt_memfill_range(void *ptr, size_t start, size_t len, uint8_t byte);

/**
 * Fill a chunk of memory with a specific byte.
 *
 * @param ptr Pointer to the chunk of memory allocated with one of the
 * `mrt_*()` memory allocation functions.
 * @param byte The byte to put into each byte of the memory.
 */
#define mrt_memfill(ptr, byte) mrt_memfill_range((ptr), 0, (size_t)-1, (byte))

/**
 * Zero-fill a range of a chunk of memory.
 *
 * @param ptr Pointer to the chunk of memory allocated with one of the
 * `mrt_*()` memory allocation functions.
 * @param start The start address to zero-fill.
 * @param len The number of bytes to zero-fill. If @a len is equal
 * to @c SIZE_MAX (ie. ((size_t)-1)) then all of the memory from the
 * @a start to the end of the memory will be zero-filled.
 */
#define mrt_memclear_range(ptr, start, len) mrt_memfill_range((ptr), (start), (len), 0)

/**
 * Zero-fill a chunk of memory.
 *
 * @param ptr Pointer to a chunk of memory alloacted with one of the
 * `mrt_*()` memory allocation functions.
 */
#define mrt_memclear(ptr) mrt_memfill(ptr, 0)

/**
 * Alias of mrt_malloc() for allocating arrays.
 *
 * @note This is equivalent to `mrt_malloc((n)*(sz))`.
 * @warning The return pointer has before it a special header that
 * MRT uses to track the size of the memory allocation. You *MUST*
 * free this memory using the special mrt_free() function and never
 * with any other free function (ie. stdlib free()).
 *
 * @param n The number of elements.
 * @param sz The size of each element.
 * @return The newly allocated memory that must be freed with
 * mrt_free() when no longer needed or @c NULL if no more memory
 * is available.
 */
#define mrt_calloc(n, sz) mrt_malloc((n)*(sz))

/**
 * Alias of mrt_malloc() for allocating a type.
 *
 * @note This is equivalent to `mrt_malloc(sizeof(T))`.
 *
 * @param T The type of the "object" to allocate.
 * @return The newly allocated memory that must be free with
 * mrt_free() when no longer needed or @c NULL if no more memory
 * is available.
 */
#define mrt_new(T) mrt_malloc(sizeof(T))

/**
 * Duplicates a chunk of memory.
 *
 * @param prt The chunk of memory to duplicate.
 * @return The newly allocated duplicate memory that should be freed
 * with mrt_free() when no longer needed.
 */
void *mrt_memdup(const void *ptr);

MRT_END_CDECLS

#endif // MRT_MEMORY_H
