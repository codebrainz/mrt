#include <mrt/strutils.h>
#include <mrt/memory.h>
#include <string.h>

char *mrt_strdup(const char *s)
{
  if (!s)
    return NULL;
  return mrt_strndup(s, strlen(s));
}

char *mrt_strndup(const char *s, size_t len)
{
  char *buf;

  if (!s)
    return NULL;

  buf = mrt_malloc(len + 1);
  if (!buf)
    return NULL;

  memcpy(buf, s, len);
  buf[len] = '\0';

  return buf;
}

char *mrt_strdup_printf(const char *fmt, ...)
{
  char *buf;
  va_list ap;
  if (!fmt)
    return NULL;
  va_start(ap, fmt);
  buf = mrt_strdup_vprintf(fmt, ap);
  va_end(ap);
  return buf;
}

char *mrt_strdup_vprintf(const char *fmt, va_list ap)
{
  (void)fmt;
  (void)ap;
  return NULL;
}

size_t mrt_strlen(const char *str)
{
  if (!str)
    return 0;
  return strlen(str);
}

int mrt_strcmp(const char *str1, const char *str2)
{
  if (!str1 && !str2)
    return 0;
  else if (str1 && !str2)
    return 1;
  else if (!str1 && str2)
    return -1;
  else
    return strcmp(str1, str2);
}
