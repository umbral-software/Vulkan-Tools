/*
 * Copyright (c) 2024 The Khronos Group Inc.
 * Copyright (c) 2024 Valve Corporation
 * Copyright (c) 2024 LunarG, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * Author: Charles Giessen <charles@lunarg.com>
 */

#pragma once

#include <stdbool.h>
#include <stdlib.h>
#include <dlfcn.h>

#include <wayland-client-core.h>

typedef struct wl_display *(*PFN_wl_display_connect)(const char *name);
typedef int (*PFN_wl_display_flush)(struct wl_display *display);
typedef int (*PFN_wl_display_dispatch)(struct wl_display *display);
typedef int (*PFN_wl_display_prepare_read)(struct wl_display *display);
typedef int (*PFN_wl_display_dispatch_pending)(struct wl_display *display);
typedef int (*PFN_wl_display_read_events)(struct wl_display *display);
typedef void (*PFN_wl_proxy_marshal)(struct wl_proxy *p, uint32_t opcode, ...);
typedef struct wl_proxy *(*PFN_wl_proxy_marshal_constructor)(struct wl_proxy *proxy, uint32_t opcode,
                                                             const struct wl_interface *interface, ...);
typedef struct wl_proxy *(*PFN_wl_proxy_marshal_constructor_versioned)(struct wl_proxy *proxy, uint32_t opcode,
                                                                       const struct wl_interface *interface, uint32_t version, ...);
typedef struct wl_proxy *(*PFN_wl_proxy_marshal_flags)(struct wl_proxy *proxy, uint32_t opcode,
                                                       const struct wl_interface *interface, uint32_t version, uint32_t flags, ...);
typedef uint32_t (*PFN_wl_proxy_get_version)(struct wl_proxy *proxy);
typedef int (*PFN_wl_proxy_add_listener)(struct wl_proxy *proxy, void (**implementation)(void), void *data);
typedef void (*PFN_wl_proxy_destroy)(struct wl_proxy *proxy);
typedef int (*PFN_wl_display_roundtrip)(struct wl_display *display);
typedef void (*PFN_wl_display_disconnect)(struct wl_display *display);

static PFN_wl_display_connect cube_wl_display_connect = NULL;
static PFN_wl_display_flush cube_wl_display_flush = NULL;
static PFN_wl_display_dispatch cube_wl_display_dispatch = NULL;
static PFN_wl_display_prepare_read cube_wl_display_prepare_read = NULL;
static PFN_wl_display_dispatch_pending cube_wl_display_dispatch_pending = NULL;
static PFN_wl_display_read_events cube_wl_display_read_events = NULL;
static PFN_wl_proxy_marshal cube_wl_proxy_marshal = NULL;
static PFN_wl_proxy_marshal_constructor cube_wl_proxy_marshal_constructor = NULL;
static PFN_wl_proxy_marshal_constructor_versioned cube_wl_proxy_marshal_constructor_versioned = NULL;
static PFN_wl_proxy_marshal_flags cube_wl_proxy_marshal_flags = NULL;
static PFN_wl_proxy_get_version cube_wl_proxy_get_version = NULL;
static PFN_wl_proxy_add_listener cube_wl_proxy_add_listener = NULL;
static PFN_wl_proxy_destroy cube_wl_proxy_destroy = NULL;
static PFN_wl_display_roundtrip cube_wl_display_roundtrip = NULL;
static PFN_wl_display_disconnect cube_wl_display_disconnect = NULL;

// Use macro's to redefine the PFN's as the functions in client code
#define wl_display_connect cube_wl_display_connect
#define wl_display_flush cube_wl_display_flush
#define wl_display_dispatch cube_wl_display_dispatch
#define wl_display_prepare_read cube_wl_display_prepare_read
#define wl_display_dispatch_pending cube_wl_display_dispatch_pending
#define wl_display_read_events cube_wl_display_read_events
#define wl_proxy_marshal cube_wl_proxy_marshal
#define wl_proxy_marshal_constructor cube_wl_proxy_marshal_constructor
#define wl_proxy_marshal_constructor_versioned cube_wl_proxy_marshal_constructor_versioned
#define wl_proxy_marshal_flags cube_wl_proxy_marshal_flags
#define wl_proxy_get_version cube_wl_proxy_get_version
#define wl_proxy_add_listener cube_wl_proxy_add_listener
#define wl_proxy_destroy cube_wl_proxy_destroy
#define wl_display_roundtrip cube_wl_display_roundtrip
#define wl_display_disconnect cube_wl_display_disconnect

static inline void *initialize_wayland() {
    void *wayland_library = NULL;
#if defined(WAYLAND_LIBRARY)
    wayland_library = dlopen(WAYLAND_LIBRARY, RTLD_NOW | RTLD_LOCAL);
#endif
    if (NULL == wayland_library) {
        wayland_library = dlopen("libwayland-client.so.0", RTLD_NOW | RTLD_LOCAL);
    }
    if (NULL == wayland_library) {
        wayland_library = dlopen("libwayland-client.so", RTLD_NOW | RTLD_LOCAL);
    }
    if (NULL == wayland_library) {
        return NULL;
    }

#ifdef __cplusplus
#define TYPE_CONVERSION(type) reinterpret_cast<type>
#else
#define TYPE_CONVERSION(type)
#endif
    cube_wl_display_connect = TYPE_CONVERSION(PFN_wl_display_connect)(dlsym(wayland_library, "wl_display_connect"));
    cube_wl_display_flush = TYPE_CONVERSION(PFN_wl_display_flush)(dlsym(wayland_library, "wl_display_flush"));
    cube_wl_display_dispatch = TYPE_CONVERSION(PFN_wl_display_dispatch)(dlsym(wayland_library, "wl_display_dispatch"));
    cube_wl_display_prepare_read = TYPE_CONVERSION(PFN_wl_display_prepare_read)(dlsym(wayland_library, "wl_display_prepare_read"));
    cube_wl_display_dispatch_pending =
        TYPE_CONVERSION(PFN_wl_display_dispatch_pending)(dlsym(wayland_library, "wl_display_dispatch_pending"));
    cube_wl_display_read_events = TYPE_CONVERSION(PFN_wl_display_read_events)(dlsym(wayland_library, "wl_display_read_events"));
    cube_wl_proxy_marshal = TYPE_CONVERSION(PFN_wl_proxy_marshal)(dlsym(wayland_library, "wl_proxy_marshal"));
    cube_wl_proxy_marshal_constructor =
        TYPE_CONVERSION(PFN_wl_proxy_marshal_constructor)(dlsym(wayland_library, "wl_proxy_marshal_constructor"));
    cube_wl_proxy_marshal_constructor_versioned = TYPE_CONVERSION(PFN_wl_proxy_marshal_constructor_versioned)(
        dlsym(wayland_library, "wl_proxy_marshal_constructor_versioned"));
    cube_wl_proxy_marshal_flags = TYPE_CONVERSION(PFN_wl_proxy_marshal_flags)(dlsym(wayland_library, "wl_proxy_marshal_flags"));
    cube_wl_proxy_get_version = TYPE_CONVERSION(PFN_wl_proxy_get_version)(dlsym(wayland_library, "wl_proxy_get_version"));
    cube_wl_proxy_add_listener = TYPE_CONVERSION(PFN_wl_proxy_add_listener)(dlsym(wayland_library, "wl_proxy_add_listener"));
    cube_wl_proxy_destroy = TYPE_CONVERSION(PFN_wl_proxy_destroy)(dlsym(wayland_library, "wl_proxy_destroy"));
    cube_wl_display_roundtrip = TYPE_CONVERSION(PFN_wl_display_roundtrip)(dlsym(wayland_library, "wl_display_roundtrip"));
    cube_wl_display_disconnect = TYPE_CONVERSION(PFN_wl_display_disconnect)(dlsym(wayland_library, "wl_display_disconnect"));

    return wayland_library;
}

#include <libdecor-0/libdecor.h>

typedef bool (*PFN_libdecor_configuration_get_content_size)(struct libdecor_configuration *configuration, struct libdecor_frame *frame, int *width, int *height);
typedef struct libdecor_frame *(*PFN_libdecor_decorate)(struct libdecor *context, struct wl_surface *surface, struct libdecor_frame_interface *iface, void *user_data);
typedef void(*PFN_libdecor_frame_commit)(struct libdecor_frame *frame, struct libdecor_state *state, struct libdecor_configuration *configuration);
typedef struct xdg_toplevel *(*PFN_libdecor_frame_get_xdg_toplevel)(struct libdecor_frame *frame);
typedef void (*PFN_libdecor_frame_set_title)(struct libdecor_frame *frame, const char *title);
typedef void (*PFN_libdecor_frame_move)(struct libdecor_frame *frame, struct wl_seat *seat, uint32_t serial);
typedef void (*PFN_libdecor_frame_unref)(struct libdecor_frame *frame);
typedef struct libdecor *(*PFN_libdecor_new)(struct wl_display *display, struct libdecor_interface *iface);
typedef void (*PFN_libdecor_state_free)(struct libdecor_state *state);
typedef struct libdecor_state *(*PFN_libdecor_state_new)(int width, int height);
typedef void (*PFN_libdecor_unref)(struct libdecor *context);

static PFN_libdecor_configuration_get_content_size cube_libdecor_configuration_get_content_size = NULL;
static PFN_libdecor_decorate cube_libdecor_decorate = NULL;
static PFN_libdecor_frame_commit cube_libdecor_frame_commit = NULL;
static PFN_libdecor_frame_get_xdg_toplevel cube_libdecor_frame_get_xdg_toplevel = NULL;
static PFN_libdecor_frame_move cube_libdecor_frame_move = NULL;
static PFN_libdecor_frame_set_title cube_libdecor_frame_set_title = NULL;
static PFN_libdecor_frame_unref cube_libdecor_frame_unref = NULL;
static PFN_libdecor_new cube_libdecor_new = NULL;
static PFN_libdecor_state_free cube_libdecor_state_free = NULL;
static PFN_libdecor_state_new cube_libdecor_state_new = NULL;
static PFN_libdecor_unref cube_libdecor_unref = NULL;

#define libdecor_configuration_get_content_size cube_libdecor_configuration_get_content_size
#define libdecor_decorate cube_libdecor_decorate
#define libdecor_frame_commit cube_libdecor_frame_commit
#define libdecor_frame_get_xdg_toplevel cube_libdecor_frame_get_xdg_toplevel
#define libdecor_frame_move cube_libdecor_frame_move
#define libdecor_frame_set_title cube_libdecor_frame_set_title
#define libdecor_frame_unref cube_libdecor_frame_unref
#define libdecor_new cube_libdecor_new
#define libdecor_state_free cube_libdecor_state_free
#define libdecor_state_new cube_libdecor_state_new
#define libdecor_unref cube_libdecor_unref

static inline void *initialize_libdecor() {
    void *libdecor_library = NULL;
#if defined(LIBDECOR_LIBRARY)
    libdecor_library = dlopen(LIBDECOR_LIBRARY, RTLD_NOW | RTLD_LOCAL);
#endif
    if (NULL == libdecor_library) {
        libdecor_library = dlopen("libdecor-0.so.0", RTLD_NOW | RTLD_LOCAL);
    }
    if (NULL == libdecor_library) {
        libdecor_library = dlopen("libdecor-0.so", RTLD_NOW | RTLD_LOCAL);
    }
    if (NULL == libdecor_library) {
        return NULL;
    }

#ifdef __cplusplus
#define TYPE_CONVERSION(type) reinterpret_cast<type>
#else
#define TYPE_CONVERSION(type)
#endif
    cube_libdecor_configuration_get_content_size = TYPE_CONVERSION(PFN_libdecor_configuration_get_content_size)(dlsym(libdecor_library, "libdecor_configuration_get_content_size"));
    cube_libdecor_decorate = TYPE_CONVERSION(PFN_libdecor_decorate)(dlsym(libdecor_library, "libdecor_decorate"));
    cube_libdecor_frame_commit = TYPE_CONVERSION(PFN_libdecor_frame_commit)(dlsym(libdecor_library, "libdecor_frame_commit"));
    cube_libdecor_frame_get_xdg_toplevel = TYPE_CONVERSION(PFN_libdecor_frame_get_xdg_toplevel)(dlsym(libdecor_library, "libdecor_frame_get_xdg_toplevel"));
    cube_libdecor_frame_set_title = TYPE_CONVERSION(PFN_libdecor_frame_set_title)(dlsym(libdecor_library, "libdecor_frame_set_title"));
    cube_libdecor_frame_move = TYPE_CONVERSION(PFN_libdecor_frame_move)(dlsym(libdecor_library, "libdecor_frame_move"));
    cube_libdecor_frame_unref = TYPE_CONVERSION(PFN_libdecor_frame_unref)(dlsym(libdecor_library, "libdecor_frame_unref"));
    cube_libdecor_new = TYPE_CONVERSION(PFN_libdecor_new)(dlsym(libdecor_library, "libdecor_new"));
    cube_libdecor_state_free = TYPE_CONVERSION(PFN_libdecor_state_free)(dlsym(libdecor_library, "libdecor_state_free"));
    cube_libdecor_state_new = TYPE_CONVERSION(PFN_libdecor_state_new)(dlsym(libdecor_library, "libdecor_state_new"));    
    cube_libdecor_unref = TYPE_CONVERSION(PFN_libdecor_unref)(dlsym(libdecor_library, "libdecor_unref"));
    
    return libdecor_library;
}
