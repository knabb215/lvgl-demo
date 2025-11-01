/**
 * @file light_control.c
 * Light control UI components implementation
 */

#include "light_control.h"
#include "ha_api.h"
#include <stdio.h>
#include <string.h>

/* Structure to store light card data */
typedef struct {
    light_state_t *light;
    lv_obj_t *switch_btn;
    lv_obj_t *brightness_slider;
    lv_obj_t *brightness_label;
    lv_obj_t *color_picker;
    lv_obj_t *temp_slider;
    lv_obj_t *status_label;
} light_card_data_t;

/* Event handler for power switch */
static void switch_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *sw = lv_event_get_target(e);
    
    if (code == LV_EVENT_VALUE_CHANGED) {
        light_card_data_t *card_data = (light_card_data_t *)lv_event_get_user_data(e);
        bool is_on = lv_obj_has_state(sw, LV_STATE_CHECKED);
        
        card_data->light->is_on = is_on;
        ha_api_set_light_power(card_data->light->entity_id, is_on);
        
        /* Update status label */
        lv_label_set_text(card_data->status_label, is_on ? "ON" : "OFF");
    }
}

/* Event handler for brightness slider */
static void brightness_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *slider = lv_event_get_target(e);
    
    if (code == LV_EVENT_VALUE_CHANGED) {
        light_card_data_t *card_data = (light_card_data_t *)lv_event_get_user_data(e);
        int32_t value = lv_slider_get_value(slider);
        
        card_data->light->brightness = (uint8_t)value;
        
        /* Update brightness label */
        char buf[16];
        snprintf(buf, sizeof(buf), "%d%%", (int)(value * 100 / 255));
        lv_label_set_text(card_data->brightness_label, buf);
        
        ha_api_set_light_brightness(card_data->light->entity_id, (uint8_t)value);
    }
}

/* Event handler for color picker (color lights only) */
static void color_picker_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *picker = lv_event_get_target(e);
    
    if (code == LV_EVENT_VALUE_CHANGED) {
        light_card_data_t *card_data = (light_card_data_t *)lv_event_get_user_data(e);
        lv_color_t color = lv_colorwheel_get_rgb(picker);
        
        card_data->light->red = color.ch.red;
        card_data->light->green = color.ch.green;
        card_data->light->blue = color.ch.blue;
        
        ha_api_set_light_color(card_data->light->entity_id, 
                              card_data->light->red,
                              card_data->light->green,
                              card_data->light->blue);
    }
}

/* Event handler for color temperature slider (color lights only) */
static void temp_event_handler(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *slider = lv_event_get_target(e);
    
    if (code == LV_EVENT_VALUE_CHANGED) {
        light_card_data_t *card_data = (light_card_data_t *)lv_event_get_user_data(e);
        int32_t value = lv_slider_get_value(slider);
        
        card_data->light->color_temp = (uint16_t)value;
        ha_api_set_light_color_temp(card_data->light->entity_id, (uint16_t)value);
    }
}

/**
 * Create a light control card
 */
lv_obj_t* light_control_create_card(lv_obj_t *parent, light_state_t *light)
{
    /* Create card container */
    lv_obj_t *card = lv_obj_create(parent);
    lv_obj_set_size(card, 300, LV_SIZE_CONTENT);
    lv_obj_set_style_pad_all(card, 15, 0);
    lv_obj_set_style_bg_color(card, lv_color_hex(0x2C2C2C), 0);
    lv_obj_set_style_border_color(card, lv_color_hex(0x404040), 0);
    lv_obj_set_style_border_width(card, 2, 0);
    lv_obj_set_style_radius(card, 10, 0);
    
    /* Allocate card data */
    light_card_data_t *card_data = lv_mem_alloc(sizeof(light_card_data_t));
    memset(card_data, 0, sizeof(light_card_data_t));
    card_data->light = light;
    lv_obj_set_user_data(card, card_data);
    
    /* Create title label */
    lv_obj_t *title_label = lv_label_create(card);
    lv_label_set_text(title_label, light->name);
    lv_obj_set_style_text_font(title_label, &lv_font_montserrat_20, 0);
    lv_obj_set_style_text_color(title_label, lv_color_white(), 0);
    
    /* Create status label */
    card_data->status_label = lv_label_create(card);
    lv_label_set_text(card_data->status_label, light->is_on ? "ON" : "OFF");
    lv_obj_set_style_text_color(card_data->status_label, 
                                light->is_on ? lv_color_hex(0x00FF00) : lv_color_hex(0xFF0000), 0);
    lv_obj_align(card_data->status_label, LV_ALIGN_TOP_RIGHT, 0, 0);
    
    /* Create power switch */
    card_data->switch_btn = lv_switch_create(card);
    lv_obj_align(card_data->switch_btn, LV_ALIGN_TOP_LEFT, 0, 35);
    if (light->is_on) {
        lv_obj_add_state(card_data->switch_btn, LV_STATE_CHECKED);
    }
    lv_obj_add_event_cb(card_data->switch_btn, switch_event_handler, LV_EVENT_VALUE_CHANGED, card_data);
    
    /* Create brightness slider */
    lv_obj_t *brightness_title = lv_label_create(card);
    lv_label_set_text(brightness_title, "Brightness:");
    lv_obj_set_style_text_color(brightness_title, lv_color_white(), 0);
    lv_obj_align(brightness_title, LV_ALIGN_TOP_LEFT, 0, 75);
    
    card_data->brightness_slider = lv_slider_create(card);
    lv_obj_set_width(card_data->brightness_slider, 200);
    lv_obj_align(card_data->brightness_slider, LV_ALIGN_TOP_LEFT, 0, 100);
    lv_slider_set_range(card_data->brightness_slider, 0, 255);
    lv_slider_set_value(card_data->brightness_slider, light->brightness, LV_ANIM_OFF);
    lv_obj_add_event_cb(card_data->brightness_slider, brightness_event_handler, LV_EVENT_VALUE_CHANGED, card_data);
    
    card_data->brightness_label = lv_label_create(card);
    char buf[16];
    snprintf(buf, sizeof(buf), "%d%%", (int)(light->brightness * 100 / 255));
    lv_label_set_text(card_data->brightness_label, buf);
    lv_obj_set_style_text_color(card_data->brightness_label, lv_color_white(), 0);
    lv_obj_align(card_data->brightness_label, LV_ALIGN_TOP_RIGHT, 0, 100);
    
    /* For color lights, add color picker and temperature control */
    if (light->type == LIGHT_TYPE_COLOR) {
        /* Color picker */
        lv_obj_t *color_title = lv_label_create(card);
        lv_label_set_text(color_title, "Color:");
        lv_obj_set_style_text_color(color_title, lv_color_white(), 0);
        lv_obj_align(color_title, LV_ALIGN_TOP_LEFT, 0, 140);
        
        card_data->color_picker = lv_colorwheel_create(card, true);
        lv_obj_set_size(card_data->color_picker, 150, 150);
        lv_obj_align(card_data->color_picker, LV_ALIGN_TOP_LEFT, 0, 165);
        
        lv_color_t current_color = lv_color_make(light->red, light->green, light->blue);
        lv_colorwheel_set_rgb(card_data->color_picker, current_color);
        lv_obj_add_event_cb(card_data->color_picker, color_picker_event_handler, LV_EVENT_VALUE_CHANGED, card_data);
        
        /* Color temperature slider */
        lv_obj_t *temp_title = lv_label_create(card);
        lv_label_set_text(temp_title, "Temperature (K):");
        lv_obj_set_style_text_color(temp_title, lv_color_white(), 0);
        lv_obj_align(temp_title, LV_ALIGN_TOP_LEFT, 0, 325);
        
        card_data->temp_slider = lv_slider_create(card);
        lv_obj_set_width(card_data->temp_slider, 250);
        lv_obj_align(card_data->temp_slider, LV_ALIGN_TOP_LEFT, 0, 350);
        lv_slider_set_range(card_data->temp_slider, 2000, 6500); /* Common CCT range */
        lv_slider_set_value(card_data->temp_slider, light->color_temp, LV_ANIM_OFF);
        lv_obj_add_event_cb(card_data->temp_slider, temp_event_handler, LV_EVENT_VALUE_CHANGED, card_data);
    }
    
    return card;
}

/**
 * Update a light control card with new state
 */
void light_control_update_card(lv_obj_t *card, light_state_t *light)
{
    light_card_data_t *card_data = (light_card_data_t *)lv_obj_get_user_data(card);
    if (!card_data) return;
    
    /* Update power switch */
    if (light->is_on) {
        lv_obj_add_state(card_data->switch_btn, LV_STATE_CHECKED);
    } else {
        lv_obj_clear_state(card_data->switch_btn, LV_STATE_CHECKED);
    }
    
    /* Update status label */
    lv_label_set_text(card_data->status_label, light->is_on ? "ON" : "OFF");
    lv_obj_set_style_text_color(card_data->status_label,
                                light->is_on ? lv_color_hex(0x00FF00) : lv_color_hex(0xFF0000), 0);
    
    /* Update brightness */
    lv_slider_set_value(card_data->brightness_slider, light->brightness, LV_ANIM_OFF);
    char buf[16];
    snprintf(buf, sizeof(buf), "%d%%", (int)(light->brightness * 100 / 255));
    lv_label_set_text(card_data->brightness_label, buf);
    
    /* Update color controls if it's a color light */
    if (light->type == LIGHT_TYPE_COLOR && card_data->color_picker) {
        lv_color_t color = lv_color_make(light->red, light->green, light->blue);
        lv_colorwheel_set_rgb(card_data->color_picker, color);
        
        if (card_data->temp_slider) {
            lv_slider_set_value(card_data->temp_slider, light->color_temp, LV_ANIM_OFF);
        }
    }
    
    /* Update the stored light state */
    memcpy(card_data->light, light, sizeof(light_state_t));
}
