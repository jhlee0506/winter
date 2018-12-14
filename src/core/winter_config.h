#ifndef WINTER_CONFIG_H
#define WINTER_CONFIG_H

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


enum winter_option_type {
    WINTER_OPTION_INTEGER,
    WINTER_OPTION_UNSIGNED_INTEGER,
    WINTER_OPTION_STRING,
    WINTER_OPTION_BOOLEAN
};

struct winter_option {
    enum winter_option_type type;
    const char *name;
    char short_name;
    void *data;
};

void
winter_arguments_parse(struct winter_option* option,
                       uint32_t length,
                       int argc,
                       char* argv[]);

#ifdef  __cplusplus
}
#endif

#endif /* WINTER_CONFIG_H */