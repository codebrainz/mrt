#ifndef M_BOOLEAN_H
#define M_BOOLEAN_H

#include <mlib/number.h>

M_BEGIN_CDECLS

#define M_BOOLEAN(v) ((MBoolean*)(v))
#define M_IS_BOOLEAN(v) m_object_is_instance(m_boolean_class(), M_OBJECT(v))

typedef struct MBoolean MBoolean;

const MObjectClass *m_boolean_class(void);

MObject *m_boolean_true(void);
MObject *m_boolean_false(void);

MObject *m_boolean_new(bool val);

bool m_boolean_get(MBoolean *b);

#define m_boolean_is_true(b) m_boolean_get(M_BOOLEAN(b))
#define m_boolean_is_false(b) (!m_boolean_get(M_BOOLEAN(b)))

M_END_CDECLS

#endif // M_BOOLEAN_H
