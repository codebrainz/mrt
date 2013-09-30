#ifndef MRT_STRING_H
#define MRT_STRING_H

#include <mrt/sequence.h>

MRT_BEGIN_CDECLS

#define MRT_STRING(v) ((MRT_String*)(v))
#define MRT_IS_STRING(v) mrt_value_is_instance(mrt_string_class(), MRT_VALUE(v))

typedef struct MRT_String MRT_String;

const MRT_ValueClass *mrt_string_class(void);

MRT_Value *mrt_string_new(void);

char *mrt_string_to_utf8(MRT_String *str);
void mrt_string_assign_utf8_length(MRT_String *str, const char *s, size_t len);
void mrt_string_assign_utf8(MRT_String *str, const char *s);

MRT_END_CDECLS

#endif // MRT_STRING_H
