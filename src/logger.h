#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>

typedef int (*log_func_t)(const char *fmt, va_list ap);

void
log_set_handler(log_func_t log);

int
log(const char *fmt, ...) __attribute__ ((format (printf, 1, 2)));

#endif /* LOGGER_H */