#include <mlib/strutils.h>
#include <mlib/memory.h>
#include <string.h>
#include <stdio.h>

// FIXME:
#include <iconv.h>

char *m_strdup(const char *s)
{
  if (!s)
    return NULL;
  return m_strndup(s, m_strlen(s));
}

char *m_strndup(const char *s, size_t len)
{
  char *buf;

  if (!s)
    return NULL;

  buf = m_malloc(len + 1);
  if (!buf)
    return NULL;

  memcpy(buf, s, len);
  buf[len] = '\0';

  return buf;
}

char *m_strdup_printf(const char *fmt, ...)
{
  char *buf;
  va_list ap;
  if (!fmt)
    return NULL;
  va_start(ap, fmt);
  buf = m_strdup_vprintf(fmt, ap);
  va_end(ap);
  return buf;
}

// Taken from vsnprintf(3) man page on Ubuntu/Debian
char *m_strdup_vprintf(const char *fmt, va_list ap_in)
{
  int n, size = 100; // Guess
  char *p, *np;
  va_list ap;

  if ((p = m_malloc(size)) == NULL)
    return NULL;

  while (true) {
    va_copy(ap, ap_in);
    n = vsnprintf(p, size, fmt, ap);
    va_end(ap);

    if (n > -1 && n < size)
      return p;

    if (n > -1)
      size = n + 1;
    else
      size *= 2;

    if ((np = m_realloc(p, size)) == NULL) {
      m_free(p);
      return NULL;
    } else {
      p = np;
    }
  }

  return NULL;
}

size_t m_strlen(const char *str)
{
  if (!str || !str[0])
    return 0;
  return strlen(str);
}

int m_strcmp(const char *str1, const char *str2)
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
