/**
 * @file main.c
 * Main entry point for LVGL dashboard application
 */

#include "lvgl/lvgl.h"
#include "dashboard.h"
#include "ha_api.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

/* Display and input device configuration */
#define DISPLAY_WIDTH  1024
#define DISPLAY_HEIGHT 600

/* Home Assistant configuration - replace with your values */
#define HA_URL "http://homeassistant.local:8123"
#define HA_TOKEN "your_long_lived_access_token_here"

/* Global flag for graceful shutdown */
static volatile bool running = true;

/**
 * Signal handler for graceful shutdown
 */
static void signal_handler(int sig)
{
    (void)sig;
    running = false;
}

/**
 * Main application entry point
 */
int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    
    printf("LVGL Dashboard Starting...\n");
    
    /* Set up signal handlers for graceful shutdown */
    signal(SIGINT, signal_handler);
    signal(SIGTERM, signal_handler);
    
    /* Initialize LVGL */
    lv_init();
    
    /* Initialize SDL display and create window */
    lv_display_t *disp = lv_sdl_window_create(DISPLAY_WIDTH, DISPLAY_HEIGHT);
    
    /* Create mouse input device */
    lv_indev_t *mouse = lv_sdl_mouse_create();
    
    /* Create keyboard input device */
    lv_indev_t *keyboard = lv_sdl_keyboard_create();
    
    /* Create mousewheel input device */
    lv_indev_t *mousewheel = lv_sdl_mousewheel_create();
    
    /* Initialize Home Assistant API */
    if (!ha_api_init(HA_URL, HA_TOKEN)) {
        fprintf(stderr, "Warning: Failed to initialize Home Assistant API\n");
        fprintf(stderr, "Please update HA_URL and HA_TOKEN in main.c\n");
    }
    
    /* Create main screen */
    lv_obj_t *screen = lv_screen_active();
    lv_obj_set_style_bg_color(screen, lv_color_hex(0x0A0A0A), 0);
    
    /* Initialize dashboard */
    dashboard_init(screen);
    
    printf("Dashboard initialized successfully\n");
    printf("Press Ctrl+C to exit\n");
    
    /* Main event loop */
    while (running) {
        /* Handle LVGL tasks */
        uint32_t time_till_next = lv_timer_handler();
        
        /* Sleep for a bit */
        usleep(time_till_next * 1000);
    }
    
    printf("\nShutting down gracefully...\n");
    return 0;
}
