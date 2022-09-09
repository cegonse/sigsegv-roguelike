#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>
#include <engine/log.h>

static char *buildFormat(char *severity, char *fmt) {
  time_t t;
  struct tm *tm;
  struct timeval tv;
  char *new_fmt;

  new_fmt = calloc(1, strlen(fmt) + 2048);
  t = time(NULL);
  tm = localtime(&t);
  gettimeofday(&tv, NULL);

  sprintf(new_fmt,
          "[%04d-%02d-%02d %02d:%02d:%02d:%d][%s] %s\n",
          tm->tm_year + 1900,
          tm->tm_mon + 1,
          tm->tm_mday,
          tm->tm_hour,
          tm->tm_min,
          tm->tm_sec,
          tv.tv_usec / 1000,
          severity,
          fmt);

  return new_fmt;
}

void Log_Info(char *fmt, ...) {
  va_list ap;
  char *new_format;

  new_format = buildFormat("INFO", fmt);
  va_start(ap, fmt);
  vprintf(new_format, ap);
  va_end(ap);

  free(new_format);
}

void Log_Error(char *fmt, ...) {
  va_list ap;
  char *new_format;

  new_format = buildFormat("ERROR", fmt);
  va_start(ap, fmt);
  vprintf(new_format, ap);
  va_end(ap);

  free(new_format);
}

void Log_Hex(void *data, size_t size) {
  char message[512];
  char *new_format;

  sprintf(message, "Hex dump of %p (%zu bytes)", data, size);
  new_format = buildFormat("INFO", message);
  
  printf("%s", new_format);

  for (int i=0; i<size; ++i) {
    printf("%02X ", ((uint8_t *)data)[i]);

    if (i % 16 == 0 && i != 0) {
      printf("\n");
    }
  }

  printf("\n");
}
