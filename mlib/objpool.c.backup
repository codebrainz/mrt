#include <mrt/objpool.h>
#include <limits.h>
#include <assert.h>
#include <stdlib.h>

//
// FREE OBJECT LISTS
//

struct ObjFreeLink
{
  struct ObjFreeLink *next;
};

struct ObjFreeBucket
{
  const size_t size_class;
  size_t n_elements;
  struct ObjFreeLink *head;
};

static ObjFreeBucket free_buckets[] = {
  { 16,   0, NULL },
  { 32,   0, NULL },
  { 64,   0, NULL },
  { 128,  0, NULL },
  { 256,  0, NULL },
  { 512,  0, NULL },
  { 1024, 0, NULL },
  { 2048, 0, NULL },
  { 4096, 0, NULL },
};

// Source: http://graphics.stanford.edu/~seander/bithacks.html#RoundUpPowerOf2
static inline unsigned int next_power_of_two(unsigned int v)
{
  if (v == 0) return 0;
  v--;
  v |= v >> 1;
  v |= v >> 2;
  v |= v >> 4;
  v |= v >> 8;
  v |= v >> 16;
  v++;
  return v;
}

static inline unsigned int bucket_num(unsigned int size)
{
  switch (size) {
    case 16:   return 0;
    case 32:   return 1;
    case 64:   return 2;
    case 128:  return 3;
    case 256:  return 4;
    case 512:  return 5;
    case 1024: return 6;
    case 2048: return 7;
    case 4096: return 8;
    default:   return UINT_MAX;
  }
}

MObject *m_obj_mem_alloc(MObjectClass *cls)
{
  size_t bucket, bucket_size;
  MObject *obj;

  if (cls == NULL)
    return NULL;

  if (cls->size < sizeof(MObject))
    return NULL;

  if (cls->size > 4096)
    return m_alloc_object(cls->size);

  bucket_size = next_power_of_two(cls->size);
  if (bucket_size < sizeof(MObject))
    return NULL;

  bucket = bucket_num(bucket_size);

  if (free_links[bucket].n_elements == 0)
    return m_alloc_object(cls->size);

  obj = (MObject*) free_links[bucket].head;
  free_links[bucket].head = free_links[bucket].head->next;
  free_links[bucket].n_elements--;

  m_mem_set_is_object(obj, true);

  return obj;
}

void m_obj_mem_free(MObject *obj)
{
  size_t bucket, bucket_size;
  ObjFreeLink *link;

  if (obj == NULL)
    return;

  if (!m_mem_is_object(obj) ||
      (m_memsize(obj) < sizeof(MObject)) ||
      (m_memsize(obj) > 4096) ||
      (obj->class_->size < sizeof(MObject)) ||
      (obj->class_->size > 4096))
  {
    m_free(obj);
    return;
  }

  bucket_size = next_power_of_two(obj->class_->size);
  memset(obj, 0, bucket_size);
  m_mem_set_is_object(obj, false);
  bucket = bucket_num();

  link = (ObjFreeLink*) obj;
  link->next = free_links[bucket].head;
  free_links[bucket] = link;
  free_links[bucket].n_elements++;
}

//
// ALLOCATED OBJECT TRACKER
//

#define DEF_NUM_BUCKETS 4096
#define MAX_LOAD_FACTOR 0.8
#define MIN_LOAD_FACTOR 0.2

struct ObjHashLink
{
  MObject *obj;
  struct ObjHashLink *next;
};

struct ObjHashBucket
{
  size_t n_elements;
  struct ObjHashLink *head;
};

struct ObjHash
{
  size_t n_buckets;
  size_t n_elements;
  struct ObjHashBucket **buckets;
};

static struct ObjHash object_hash = { 0, 0, NULL };
static bool object_hash_init = false;

static void m_object_mem_deinit(void)
{
  size_t i;

  if (!object_hash_init)
    return;

  for (i = 0; i < object_hash.n_buckets; i++) {
    ObjHashLink *link = object_hash.buckets[i];
    while (link) {
      ObjHashLink *next = link->next;
      m_free(link);
      link = next;
    }
    m_free(object_hash.buckets[i]);
  }

  m_free(object_hash.buckets);
  object_hash.buckets = NULL;
  object_hash.n_buckets = 0;
  object_hash.n_elements = 0;

  object_hash_init = false;
}

static void m_object_mem_init(void)
{
  if (object_hash_init)
    return;

  object_hash.n_buckets = DEF_NUM_BUCKETS;
  object_hash.n_elements = 0;
  object_hash.buckets = m_calloc(DEF_NUM_BUCKETS, sizeof(struct ObjHashBucket*));
  object_hash_init = true;

  atexit(m_object_mem_deinit);
}

static inline double m_object_mem_load_factor(void)
{
  return ((double) object_hash.n_elements / (double) object_hash.n_buckets);
}

static inline void m_object_mem_delete_buckets(struct ObjHashBucket **buckets, size_t n_buckets)
{
  size_t i;

  for (i = 0; i < n_buckets; i++) {
    struct ObjHashLink *link = buckets[i];
    while (link) {
      struct ObjHashLink *next = link->next;
      m_free(link);
      link = next;
    }
    m_free(buckets[i]);
  }

  m_free(buckets);
}

static void m_object_mem_rehash(void)
{
  double load_factor;
  size_t i;
  size_t new_n_buckets;
  size_t temp_n_buckets, temp_n_elements;
  struct ObjHashBucket **temp_buckets;

  m_object_mem_init();

  // Don't rehash when we have small/default num buckets
  if (object_hash.n_buckets <= DEF_NUM_BUCKETS)
    return;

  // Don't rehash when the load factor is within expected range
  load_factor = m_object_mem_load_factor();
  if ((load_factor <= MAX_LOAD_FACTOR) && (load_factor >= MIN_LOAD_FACTOR))
    return;

#ifndef NDEBUG
  fprintf(stderr, "Re-hashing object tracker...");
#endif

  // Save backup of old values and clear out global hash table
  temp_n_buckets = object_hash.n_buckets;
  temp_n_elements = object_hash.n_elements;
  temp_buckets = object_hash.buckets;
  memset(&object_hash, 0, sizeof(ObjHash));

  // Double on grow, halve on shrink
  if (load_factor > MAX_LOAD_FACTOR)
    new_n_buckets = object_hash.n_buckets * 2;
  else
    new_n_buckets = object_hash.n_buckets / 2;

  // Try and allocate the new buckets
  object_hash.buckets = m_calloc(new_n_buckets, sizeof(struct ObjHashBucket*));

  // If out of memory, rollback and return
  if (object_hash.buckets == NULL) {
    object_hash.buckets = temp_buckets;
    object_hash.n_buckets = temp_n_buckets;
    object_hash.n_elements = temp_n_elements;
#ifndef NDEBUG
    fprintf(stderr, "cancelled due to out of memory condition\n");
#endif
    return;
  } else {
    object_hash.n_buckets = new_n_buckets;
  }

  // Setup the new buckets
  for (i = 0; i < new_n_buckets; i++)
    object_hash.buckets[i] = m_calloc(1, sizeof(struct ObjHashBucket));

  // Re-hash old elements into new table
  for (i = 0; i < temp_n_buckets; i++) {
    struct ObjHashLink *link;
    for (link = temp_buckets[i]; link != NULL; link = link->next) {
      size_t hash = link->obj % new_n_buckets; // checkme
      struct ObjHashLink *new_link;
      assert(hash < new_n_buckets);
      new_link = m_calloc(1, sizeof(struct ObjHashLink));
      if (new_link) {
        new_link->obj = link->obj;
        new_link->next = object_hash.buckets[hash]->head;
        object_hash.buckets[hash]->head = new_link;
        object_hash.buckets[hash]->n_elements++;
        object_hash.n_elements++;
      }
    }
  }

  // If not all elements were hashed (ie. OOM), rollback and return
  if (object_hash.n_elements != temp_n_elements) {
    m_object_mem_delete_buckets(object_hash.buckets, object_hash.n_buckets);
    object_hash.n_buckets = temp_n_buckets;
    object_hash.n_elements = temp_n_elements;
    object_hash.buckets = temp_buckets;
#ifndef NDEBUG
    fprintf(stderr, "cancelled due to out of memory condition\n");
#endif
    return;
  }

  // Free the temporary backup hash
  m_object_mem_delete_hash(temp_buckets, temp_n_buckets);

#ifndef NDEBUG
  fprintf(stderr, "complete\n");
#endif
}

static inline bool m_object_register(MObject *obj)
{
  size_t hash;
  struct ObjHashLink *link;

  m_object_mem_rehash();

  hash = obj % object_hash.n_buckets;
  assert(hash < object_hash.n_buckets);

  for (link = object_hash.buckets[hash]; link != NULL; link = link->next) {
    if (link->obj == obj)
      return false;
  }

  link = m_calloc(1, sizeof(struct ObjHashLink));
  link->obj = obj;
  link->next = object_hash.buckets[hash].head;
  object_hash.buckets[hash].head = link;
  object_hash.buckets[hash].n_elements++;
  object_hash.n_elements++;

  return true;
}

static inline bool m_object_unregister(MObject *obj)
{
  uint32_t hash = obj % object_hash.n_buckets; // checkme

  assert(hash < object_hash.n_buckets);


}

static void *m_object_allocate(MObjectClass *cls)
{
  MObject *obj;

  m_object_init();

  obj = m_obj_mem_alloc(cls);
  if (!obj)
    return NULL;

  if (!m_object_register(obj)) {
    m_obj_mem_free(obj);
    return NULL;
  }

  return obj;
}

bool m_obj_mem_exists(MObject *obj)
{
  if (obj == NULL)
    return false;
  if (!m_mem_is_object(obj))
    return false;
  // TODO: lookup in pool
  return false;
}
