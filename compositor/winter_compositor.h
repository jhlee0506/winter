

struct wl_display*
winter_display_create();


struct winter_compositor {
    struct wl_display display;
    struct winter_backend backend;
    struct winter_renderer renderer;
};

struct winter_compositor*
winter_compositor_create(struct wl_display *display, void* user_data);

void
winter_compositor_destroy(struct winter_compositor* wc);

void*
winter_compositor_get_user_data(struct winter_compositor* wc);



int
winter_compositor_load_backend(struct winter_compositor* wc,
                               winter_compositor_backend backend);



struct winter_renderer {
    void (*attach)(struct winter_surface surface,
                   struct winter_buffer buffer);
    void (*flush)(struct winter_surface surface);
    void (*destroy)(struct winter_compositor *ec);

    struct wl_signal flushed_signal;
};

int
winter_backend_init(struct winter_compositor);

struct winter_screen {
    void (*resize)(unsigned int width, unsigned int height);
};



struct winter_surface {
    struct wl_signal destroy_signal;
};

struct winter_buffer {
    struct wl_signal destroy_signal;
};

struct winter_renderer {
    void (*destroy)(struct winter_compositor* wc);
    void (*flush)(struct surface);
};