#ifndef M_NONE_H
#define M_NONE_H

#include <mlib/object.h>

M_BEGIN_CDECLS

#define M_NONE(v) ((MNone*)(v))
#define M_IS_NONE(v) m_object_is_instance(m_none_class(), M_OBJECT(v))

typedef struct MNone MNone;

const MObjectClass *m_none_class(void);

MObject *m_none(void);

M_END_CDECLS

#endif // M_NONE_H
