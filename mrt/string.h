#ifndef M_STRING_H
#define M_STRING_H

#include <mrt/sequence.h>

M_BEGIN_CDECLS

#define M_STRING(v) ((MString*)(v))
#define M_IS_STRING(v) m_object_is_instance(m_string_class(), M_OBJECT(v))

typedef struct MString MString;

const MObjectClass *m_string_class(void);

MObject *m_string_new(void);

char *m_string_to_utf8(MString *str);
void m_string_assign_utf8_length(MString *str, const char *s, size_t len);
void m_string_assign_utf8(MString *str, const char *s);

M_END_CDECLS

#endif // M_STRING_H
