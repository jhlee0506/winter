#include <stdio.h>

#include "logger.h"


static int
default_log_handler(const char *fmt, va_list ap);

static log_func_t log_handler = default_log_handler;

static int
default_log_handler(const char *fmt, va_list ap)
{
        fprintf(stderr, "log_set_handler() must be called before using of log().\n");
        abort();
}

void
log_set_handler(log_func_t log)
{
    log_handler = log;
}

int
log(const char *fmt, ...)
{
    int r = 0;
    va_list args;

    va_start(args, fmt);
    r = log_handler(fmt, args);
    va_end(args);

    return r;
}