#ifndef M_CHAR_H
#define M_CHAR_H

#include <mrt/number.h>

M_BEGIN_CDECLS

#define M_CHAR(v) ((MChar*)(v))
#define M_IS_CHAR(v) m_object_is_instance(m_char_class(), M_OBJECT(v))

typedef struct MChar MChar;

const MObjectClass *m_char_class(void);

MObject *m_char_new(uint32_t ch);
uint32_t m_char_get(MChar *c);
void m_char_set(MChar *c, uint32_t ch);

M_END_CDECLS

#endif // M_CHAR_H
