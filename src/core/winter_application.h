#ifndef WINTER_APPLICATION_H
#define WINTER_APPLICATION_H

#ifdef  __cplusplus
extern "C" {
#endif

#ifndef ARRAY_LENGTH
#define ARRAY_LENGTH(a) (sizeof (a) / sizeof (a)[0])
#endif


struct winter_window;
struct winter_backend;


struct winter_application {
    struct winter_window *foreground_window;
    struct winter_backend *backend;
};

struct winter_application*
winter_application_create(int argc,
                          char *argv[]);

void
winter_application_destroy(struct winter_application *app);

#ifdef  __cplusplus
}
#endif

#endif /* WINTER_APPLICATION_H */