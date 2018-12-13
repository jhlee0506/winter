struct winter_compositor {
    struct wl_display display;
    struct winter_backend backend;
};

struct winter_compositor*
winter_compositor_create(struct wl_display* disp, void* user_data);

void
winter_compositor_destroy(struct winter_compositor* wc);


struct winter_backend {

};

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
    struct wl_surface surface;
};

struct winter_buffer {
    struct wl_buffer buffer;
};
