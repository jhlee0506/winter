#include "winter_backend.h"
#include "winter_screen.h"


void*
load_module(const char* name, const char* entry)
{
    char *path = NULL;
    void *module = NULL, *point = NULL;

    module = dlopen(path, RTLD_NOW | RTLD_NOLOAD);
    if (module) {
        dlclose(module);
        return NULL;
    }

    module = dlopen(path, RTLD_NOW);
    if (!module) {
        return NULL;
    }

    point = dlsym(module, entry);
    if (!point) {
        dlclose(module);
        return NULL;
    }

    return point;
}

struct winter_backend*
winter_backend_load(enum winter_backend_integration integration,
                    int argc,
                    char* argv[])
{
    static const char* const _backend_map = {
        [WINTER_BACKEND_GM] =       "winter-gm-backend.so",
        [WINTER_BACKEND_WAYLAND] =  "winter-wayland-backend.so",
    };
    struct winter_backend* (*backend_create)();

    backend_create = load_module(integration, "winter_backend_create");
    return backend_create();
}

struct winter_screen*
winter_backend_load_screen(struct winter_backend backend,
                           int argc,
                           char* argv[])
{
    winter_screen
    return screen;
}