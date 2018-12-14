#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include "winter_config.h"


static bool
handle_option(const struct winter_option *option, char *value)
{
    char* p;

    assert(option != NULL);
    assert(value != NULL);

    switch (option->type) {
    case WINTER_OPTION_INTEGER:
        if (!safe_strtoint(value, option->data))
            return false;
        return true;
    case WINTER_OPTION_UNSIGNED_INTEGER:
        errno = 0;
        * (uint32_t *) option->data = strtoul(value, &p, 10);
        if (errno != 0 || p == value || *p != '\0')
            return false;
        return true;
    case WINTER_OPTION_STRING:
        * (char **) option->data = strdup(value);
        return true;
    default:
        assert(0);
    }
}

static bool
long_option(struct winter_option* option,
            uint32_t length,
            char* argv)
{
    int i = 0, len = 0;

    assert(option != NULL);
    assert(argv != NULL);

    for (i = 0; i < length; i++) {
        if (!option[i].name)
            continue;

        len = strlen(option[i].name);
        if (strncmp(option[i].name, argv + 2, len))
            continue;

        if (option[i].type == WINTER_OPTION_BOOLEAN) {
            if (!argv[len + 2]) {
                * (int32_t *) option[i].data = 1;
                return true;
            }
        } else if (argv[len + 2] == '=') {
            return handle_option(option + i, argv + len + 3);
        }
    }

    return true;
}

static bool
long_option_with_arg(struct winter_option* option,
                     uint32_t length,
                     char* key, char* value)
{
    int i = 0, len = 0;

    assert(option != NULL);
    assert(key != NULL);
    assert(value != NULL);

    for (i = 0; i < length; i++) {
        if (!option[i].name)
            continue;

        len = strlen(option[i].name);
        if (strncmp(option[i].name, key + 2, len))
            continue;

        assert(option[i].type != WINTER_OPTION_BOOLEAN);
        return handle_option(option + i, value);
    }

    return true;
}

static bool
short_option(struct winter_option* option,
             uint32_t length,
             char* argv)
{
    int i = 0;

    assert(option != NULL);
    assert(argv != NULL);

    for (i = 0; i < length; i++) {
        if (option[i].short_name != argv[1])
            continue;

        if (option[i].type == WINTER_OPTION_BOOLEAN) {
            if (!argv[2]) {
                * (int32_t *) option[i].data = 1;
                return true;
            }
        } else if (argv[2]) {
            return handle_option(option + i, argv + 2);
        } else {
            return false;
        }
    }

    return true;
}

static bool
short_option_with_arg(struct winter_option* option,
                      uint32_t length,
                      char* key, char* value)
{
    int i = 0;

    assert(option != NULL);
    assert(key != NULL);
    assert(value != NULL);

    for (i = 0; i < length; i++) {
        if (option[i].short_name != key[1])
            continue;

        assert(option[i].type != WINTER_OPTION_BOOLEAN);
        return handle_option(option + i, value);
    }

    return true;
}

void
winter_arguments_parse(struct winter_option* option,
                       uint32_t length,
                       int argc,
                       char* argv[])
{
    int i = 0;

    for (i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            if (argv[i][1] == '-') {
                // '--foo=boo' case
                if (long_option(option, length, argv[i]))
                    continue;
                // '--foo boo' case
                if (i+1 < argc &&
                    long_option_with_arg(option, length, argv[i], argv[i+1])) {
                    i++;
                    continue;
                }
            } else {
                // '-fboo' case
                if (short_option(option, length, argv[i]))
                    continue;
                // '-f boo' case
                if (i+1 < argc &&
                    short_option_with_arg(option, length, argv[i], argv[i+1])) {
                        i++;
                        continue;
                }
            }
        }
    }
}