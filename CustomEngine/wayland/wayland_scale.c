#include "wayland_scale.h"

#ifdef _WIN32

int wl_get_output_scale(void) {
  return 1;
}

#else

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wayland-client.h>

static int global_scale = 1;

static void output_scale(void *data, struct wl_output *wl_output,
                         int32_t factor) {
  global_scale = factor;
  // printf("[WAYLAND] Output scale = %d (→ %d%%)\n", factor, factor * 100);
}

static void output_geometry(void *data, struct wl_output *wl_output, int32_t x,
                            int32_t y, int32_t physical_width,
                            int32_t physical_height, int32_t subpixel,
                            const char *make, const char *model,
                            int32_t transform) {
  // Non usato, ma richiesto dall'interfaccia
}

static void output_mode(void *data, struct wl_output *wl_output, uint32_t flags,
                        int32_t width, int32_t height, int32_t refresh) {
  // Non usato
}

static void output_done(void *data, struct wl_output *wl_output) {
  // Non usato
}

static const struct wl_output_listener output_listener = {
    .geometry = output_geometry,
    .mode = output_mode,
    .done = output_done,
    .scale = output_scale};

static void registry_add(void *data, struct wl_registry *registry, uint32_t id,
                         const char *interface, uint32_t version) {
  if (strcmp(interface, "wl_output") == 0) {
    struct wl_output *output = (struct wl_output *)wl_registry_bind(
        registry, id, &wl_output_interface, 2);

    wl_output_add_listener(output, &output_listener, NULL);
  }
}

static void registry_remove(void *data, struct wl_registry *registry,
                            uint32_t id) {
  // Non usato
}

static const struct wl_registry_listener registry_listener = {
    .global = registry_add, .global_remove = registry_remove};

int wl_get_output_scale(void) {

  struct wl_display *display = wl_display_connect(NULL);
  if (!display) {
    return 1;
  }

  struct wl_registry *registry = wl_display_get_registry(display);
  wl_registry_add_listener(registry, &registry_listener, NULL);

  // Due roundtrip per assicurare che tutti gli eventi arrivino
  wl_display_roundtrip(display);
  wl_display_roundtrip(display);

  // printf("Scale finale riportato = %d (→ %d%%)\n", global_scale, global_scale * 100);

  wl_display_disconnect(display);
  return global_scale;
}

#endif
