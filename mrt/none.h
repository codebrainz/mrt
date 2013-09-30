#ifndef MRT_NONE_H
#define MRT_NONE_H

#include <mrt/value.h>

MRT_BEGIN_CDECLS

#define MRT_NONE(v) ((MRT_None*)(v))
#define MRT_IS_NONE(v) mrt_value_is_instance(mrt_none_class(), MRT_VALUE(v))

typedef struct MRT_None MRT_None;

const MRT_ValueClass *mrt_none_class(void);

MRT_Value *mrt_none(void);

MRT_END_CDECLS

#endif // MRT_NONE_H
