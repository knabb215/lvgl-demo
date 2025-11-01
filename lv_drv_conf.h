/**
 * @file lv_drv_conf.h
 * Configuration file for lv_drivers
 */

#ifndef LV_DRV_CONF_H
#define LV_DRV_CONF_H

#include "lv_conf.h"

/*==================
 * SDL CONFIGURATION
 *==================*/

#ifndef USE_SDL
#define USE_SDL 1
#endif

#if USE_SDL
#define SDL_HOR_RES     1024
#define SDL_VER_RES     600
#define SDL_ZOOM        1
#define SDL_INCLUDE_PATH    <SDL2/SDL.h>
#endif

/*==================
 * FBDEV (Linux Framebuffer) CONFIGURATION
 *==================*/

#ifndef USE_FBDEV
#define USE_FBDEV 0
#endif

/*==================
 * OTHER DRIVERS
 *==================*/

#define USE_EVDEV       0
#define USE_LIBINPUT    0
#define USE_XKB         0
#define USE_WAYLAND     0
#define USE_MONITOR     1

#endif /* LV_DRV_CONF_H */
