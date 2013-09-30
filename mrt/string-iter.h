#ifndef MRT_STRING_ITER_H
#define MRT_STRING_ITER_H

#include <mrt/sequence-iter.h>

MRT_BEGIN_CDECLS

#define MRT_STRING_ITER(v) ((MRT_StringIter*)(v))
#define MRT_IS_STRING_ITER(v) mrt_object_is_instance(mrt_string_iter_class(), MRT_OBJECT(v))

typedef struct MRT_StringIter MRT_StringIter;

const MRT_ObjectClass *mrt_string_iter_class(void);

MRT_END_CDECLS

#endif // MRT_STRING_ITER_H
