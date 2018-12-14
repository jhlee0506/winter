#ifndef HELPERS_H
#define HELPERS_H

static inline bool
safe_strtoint(const char *str, int32_t *value)
{
    long ret;
    char *end;

    assert(str != NULL);
    assert(value != NULL);

    errno = 0;
    ret = strtol(str, &end, 10);
    if (errno != 0) {
        return false;
    } else if (end == str || *end != '\0') {
        errno = EINVAL;
        return false;
    }

    if ((long)((int32_t)ret) != ret) {
        errno = ERANGE;
        return false;
    }
    *value = (int32_t)ret;

    return true;
}

#endif /* HELPERS_H */