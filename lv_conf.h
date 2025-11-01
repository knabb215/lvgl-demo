/**
 * @file lv_conf.h
 * Configuration file for LVGL
 */

#ifndef LV_CONF_H
#define LV_CONF_H

#include <stdint.h>

/*====================
   COLOR SETTINGS
 *====================*/

/* Color depth: 1 (1 byte per pixel), 8 (RGB332), 16 (RGB565), 32 (ARGB8888) */
#define LV_COLOR_DEPTH 32

/*=========================
   MEMORY SETTINGS
 *=========================*/

/* Size of the memory available for `lv_mem_alloc()` in bytes */
#define LV_MEM_SIZE (64U * 1024U)

/*====================
   HAL SETTINGS
 *====================*/

/* Default display refresh period. LVG will redraw changed areas with this period time */
#define LV_DISP_DEF_REFR_PERIOD 30

/* DPI of the display */
#define LV_DPI_DEF 130

/*====================
   DRAW ENGINE SETTINGS
 *====================*/

/* Disable ARM Helium SIMD (not supported on x86/x64) */
#define LV_USE_DRAW_SW_ASM 0

/*=================
   FONT USAGE
 *=================*/

/* Montserrat fonts with various sizes */
#define LV_FONT_MONTSERRAT_12 1
#define LV_FONT_MONTSERRAT_14 1
#define LV_FONT_MONTSERRAT_16 1
#define LV_FONT_MONTSERRAT_18 1
#define LV_FONT_MONTSERRAT_20 1
#define LV_FONT_MONTSERRAT_22 1
#define LV_FONT_MONTSERRAT_24 1
#define LV_FONT_MONTSERRAT_26 1
#define LV_FONT_MONTSERRAT_28 1

/* Default font */
#define LV_FONT_DEFAULT &lv_font_montserrat_16

/*====================
 * LV_USE_LOG
 *==================*/

/* Enable the log module */
#define LV_USE_LOG 1
#if LV_USE_LOG

/* How important log should be added */
#define LV_LOG_LEVEL LV_LOG_LEVEL_WARN

/* Use printf for log output */
#define LV_LOG_PRINTF 1

#endif  /*LV_USE_LOG*/

/*====================
 * FEATURE CONFIGURATION
 *====================*/

/* Enable SDL support */
#define LV_USE_SDL 1

/*====================
 * WIDGETS
 *====================*/

/* Enable all widgets by default */
#define LV_USE_ARC        1
#define LV_USE_BAR        1
#define LV_USE_BTN        1
#define LV_USE_BTNMATRIX  1
#define LV_USE_CANVAS     1
#define LV_USE_CHECKBOX   1
#define LV_USE_DROPDOWN   1
#define LV_USE_IMG        1
#define LV_USE_LABEL      1
#define LV_USE_LINE       1
#define LV_USE_ROLLER     1
#define LV_USE_SLIDER     1
#define LV_USE_SWITCH     1
#define LV_USE_TEXTAREA   1
#define LV_USE_TABLE      1

/* Colorwheel widget for color picker */
#define LV_USE_COLORWHEEL 1

#endif /*LV_CONF_H*/
