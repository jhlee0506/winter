#ifndef WINTER_BACKEND_H
#define WINTER_BACKEND_H


struct winter_backend {
    void (*destroy)(struct winter_compositor* wc);
    void (*flush)(struct winter_compositor* wc,
                  void* flush_data);
};

enum winter_backend_integration {
    WINTER_BACKEND_GM,
    WINTER_BACKEND_WAYLAND,
};

struct winter_backend*
winter_backend_load(enum winter_backend_integration integration,
                    int argc,
                    char* argv[]);

struct winter_screen*
winter_backend_load_screen(struct winter_backend backend,
                           int argc,
                           char* argv[]);

#endif /* WINTER_BACKEND_H */