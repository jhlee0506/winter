#include <unistd.h>
#include <stdarg.h>
#include <sys/time.h>

#include "winter_debugger.h"
#include "logger.h"


static struct winter_debugger {
    int level;
} debugger = {0, };

static int
winter_debugger_log(char* fmt, va_list args)
{
    if (winter_debugger_is_enabled()) {
        char ts[128], msg[128];

        debugger_timestamp(ts, sizeof ts);
        debugger_log(msg, sizeof msg);

        printf("%s %s", ts, log);
    }

    return 1;
}

static void
debugger_level_changed() {
    switch (debugger.level) {
    case 1:
        log_set_handler(winter_debugger_log);
        break;
    }
}

static char*
debugger_timestamp(char *buf, size_t length)
{
    struct timeval tv;
    struct tm *bdt;
    char str[128];
    size_t ret = 0;

    gettimeofday(&tv, NULL);

    bdt = localtime(&tv.tv_sec);
    if (bdt)
        ret = strftime(str, sizeof str,
                       "%Y-%m-%d %H:%M:%S", bdt);

    if (ret > 0) {
        snprintf(buf,
                 length,
                 "[%s.%03ld]",
                 str,
                 tv.tv_usec / 1000);
    } else {
        snprintf(buf,
                 length,
                 "[?]");
    }
}

static char*
debugger_log(char* fmt, va_list args)
{
    static const char oom[] = "Out of memory";
    char *str = NULL;
    int len = 0;

    len = vasprintf(&str, fmt, args);
    if (len >= 0)
        return str;

    return strdup(oom);
}

void
winter_debugger_set_level(int level)
{
    if (level != debugger.level) {
        debugger.level = level;
        debugger_level_changed();
    }
}

bool
winter_debugger_is_enabled()
{
    if (debugger.level > 0)
        return true;
    return false;
}