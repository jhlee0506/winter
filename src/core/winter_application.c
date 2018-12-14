#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "winter_application.h"
#include "winter_backend.h"
#include "winter_config.h"


static struct winter_backend*
load_backend(char *backend, int argc, char *argv[])
{
    size_t len = 0;
    enum winter_backend_integration integration = WINTER_BACKEND_GM;
    assert(backend);
    assert(argv);

    len = strlen(backend);
    if (!strncmp(backend, "gm", len))
        return winter_backend_load(WINTER_BACKEND_GM, argc, argv);
    else if (!strncmp(backend, "wayland", len))
        return winter_backend_load(WINTER_BACKEND_WAYLAND, argc, argv);
    else
        assert(0);
    return NULL;
}


struct winter_application*
winter_application_create(int argc,
                          char *argv[])
{
    struct winter_application app = {};
    assert(argv);

    char* backend = NULL;
    int debugging = 0;
    const struct winter_option core_options[] = {
		{ WINTER_OPTION_STRING, "backend", 'B', &backend },
		{ WINTER_OPTION_INTEGER, "debugger", 0, &debugging }
	};

    winter_arguments_parse(core_options,
                           ARRAY_LENGTH(core_options),
                           argc,
                           argv);

    if (debugging)
        winter_debugger_set_level(debugging);

    app.backend = load_backend(backend, argc, argv);
    assert(app.backend);
}

void
winter_application_destroy(struct winter_application *app)
{
    free(app->backend);
    free(app);
}