#include <mlib/process-impl.h>

static void m_process_ctor(MObject *obj, va_list ap)
{
  const char *const *argv = va_arg(ap, const char *const *);
  int flags = va_arg(ap, int);
  (void)obj;
  (void)argv;
  (void)flags;
}

static void m_process_dtor(MObject *obj)
{
  (void)obj;
}

MObject *m_process_new(const char *const *argv, int flags)
{
  return m_object_construct(m_process_class(), NULL, argv, flags);
}

int m_process_run(MProcess *proc, const MString *in, MString *out,
  MString *err, int timeout)
{
  (void)proc;
  (void)in;
  (void)out;
  (void)err;
  (void)timeout;
  return -1;
}

int m_process_return_code(MProcess *proc)
{
  m_return_val_if_fail(M_IS_PROCESS(proc), -1);
  return proc->return_code;
}

M_BEGIN_CLASS_DEF(MProcess, process, m_object_class())
{
  M_SET_FIELD(MObjectClass, ctor, m_process_ctor);
  M_SET_FIELD(MObjectClass, dtor, m_process_dtor);
}
M_END_CLASS_DEF
