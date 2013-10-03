#ifndef M_PROCESS_H
#define M_PROCESS_H

#include <mlib/object.h>
#include <mlib/string.h>

M_BEGIN_CDECLS

#define M_PROCESS(v) ((MProcess*)(v))
#define M_IS_PROCESS(v) m_object_is_instance(m_process_class(), M_OBJECT(v))

typedef struct MProcess MProcess;

typedef enum
{
  M_PROCESS_FLAG_NONE=0,
  M_PROCESS_FLAG_STDOUT_TO_DEVNULL,
  M_PROCESS_FLAG_STDERR_TO_DEVNULL,
}
MProcessFlag;

const MObjectClass *m_process_class(void);

MObject *m_process_new(const char *const *argv, int flags);

int m_process_run(MProcess *proc, const MString *in, MString *out,
  MString *err, int timeout);

int m_process_return_code(MProcess *proc);

M_END_CDECLS

#endif // M_PROCESS_H
