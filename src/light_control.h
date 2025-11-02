/**
 * @file light_control.h
 * Light control UI components for switch and color lights
 */

#ifndef LIGHT_CONTROL_H
#define LIGHT_CONTROL_H

#include "lvgl/lvgl.h"
#include <stdbool.h>

/* Light types */
typedef enum {
    LIGHT_TYPE_SWITCH,  /* Simple on/off with brightness */
    LIGHT_TYPE_COLOR    /* RGB with CCT support */
} light_type_t;

/* Light state structure */
typedef struct {
    char name[64];
    char entity_id[64];
    light_type_t type;
    bool is_on;
    uint8_t brightness;  /* 0-255 */
    uint8_t red;         /* 0-255, for color lights */
    uint8_t green;       /* 0-255, for color lights */
    uint8_t blue;        /* 0-255, for color lights */
    uint16_t color_temp; /* Kelvin, for color lights with CCT */
} light_state_t;

/**
 * Create a light control card
 * @param parent Parent object
 * @param light Light state data
 * @return Created light card object
 */
lv_obj_t* light_control_create_card(lv_obj_t *parent, light_state_t *light);

/**
 * Update a light control card with new state
 * @param card Light card object
 * @param light New light state
 */
void light_control_update_card(lv_obj_t *card, light_state_t *light);

#endif /* LIGHT_CONTROL_H */
