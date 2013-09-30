#ifndef MRT_INTEGER_H
#define MRT_INTEGER_H

#include <mrt/number.h>

MRT_BEGIN_CDECLS

#define MRT_INTEGER(v) ((MRT_Integer*)(v))
#define MRT_IS_INTEGER(v) mrt_object_is_instance(mrt_integer_class(), MRT_OBJECT(v))

typedef struct MRT_Integer MRT_Integer;

const MRT_ObjectClass *mrt_integer_class(void);

MRT_Object *mrt_integer_new(int64_t val);
int64_t mrt_integer_get(MRT_Integer *i);
void mrt_integer_set(MRT_Integer *i, int64_t val);

MRT_END_CDECLS

#endif // MRT_INTEGER_H
