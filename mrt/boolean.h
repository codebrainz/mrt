#ifndef MRT_BOOLEAN_H
#define MRT_BOOLEAN_H

#include <mrt/number.h>

MRT_BEGIN_CDECLS

#define MRT_BOOLEAN(v) ((MRT_Boolean*)(v))
#define MRT_IS_BOOLEAN(v) mrt_object_is_instance(mrt_boolean_class(), MRT_OBJECT(v))

typedef struct MRT_Boolean MRT_Boolean;

const MRT_ObjectClass *mrt_boolean_class(void);

MRT_Object *mrt_boolean_true(void);
MRT_Object *mrt_boolean_false(void);

MRT_Object *mrt_boolean_new(bool val);

bool mrt_boolean_get(MRT_Boolean *b);

#define mrt_boolean_is_true(b) mrt_boolean_get(MRT_BOOLEAN(b))
#define mrt_boolean_is_false(b) (!mrt_boolean_get(MRT_BOOLEAN(b)))

MRT_END_CDECLS

#endif // MRT_BOOLEAN_H
