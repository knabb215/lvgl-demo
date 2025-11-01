/**
 * @file dashboard.c
 * Dashboard UI components implementation
 */

#include "dashboard.h"
#include "light_control.h"
#include "ha_api.h"
#include <stdio.h>
#include <string.h>

/* Dashboard data */
static lv_obj_t *dashboard_screen = NULL;
static lv_obj_t *light_container = NULL;

/* Sample lights for demonstration */
static light_state_t lights[] = {
    {
        .name = "Living Room",
        .entity_id = "light.living_room",
        .type = LIGHT_TYPE_SWITCH,
        .is_on = false,
        .brightness = 128,
        .red = 0,
        .green = 0,
        .blue = 0,
        .color_temp = 0
    },
    {
        .name = "Bedroom",
        .entity_id = "light.bedroom",
        .type = LIGHT_TYPE_SWITCH,
        .is_on = true,
        .brightness = 200,
        .red = 0,
        .green = 0,
        .blue = 0,
        .color_temp = 0
    },
    {
        .name = "Kitchen RGB",
        .entity_id = "light.kitchen_rgb",
        .type = LIGHT_TYPE_COLOR,
        .is_on = true,
        .brightness = 255,
        .red = 255,
        .green = 100,
        .blue = 50,
        .color_temp = 4000
    },
    {
        .name = "Office Color",
        .entity_id = "light.office_color",
        .type = LIGHT_TYPE_COLOR,
        .is_on = false,
        .brightness = 150,
        .red = 50,
        .green = 150,
        .blue = 255,
        .color_temp = 5000
    }
};

static const int num_lights = sizeof(lights) / sizeof(lights[0]);

/**
 * Initialize the dashboard UI
 */
void dashboard_init(lv_obj_t *parent)
{
    if (!parent) {
        printf("Error: parent object is NULL\n");
        return;
    }
    
    dashboard_screen = parent;
    
    /* Create title */
    lv_obj_t *title = lv_label_create(parent);
    lv_label_set_text(title, "Home Assistant Light Dashboard");
    lv_obj_set_style_text_font(title, &lv_font_montserrat_28, 0);
    lv_obj_set_style_text_color(title, lv_color_white(), 0);
    lv_obj_align(title, LV_ALIGN_TOP_MID, 0, 20);
    
    /* Create container for lights */
    light_container = lv_obj_create(parent);
    lv_obj_set_size(light_container, LV_PCT(95), LV_PCT(85));
    lv_obj_align(light_container, LV_ALIGN_BOTTOM_MID, 0, -10);
    lv_obj_set_style_bg_color(light_container, lv_color_hex(0x1C1C1C), 0);
    lv_obj_set_style_border_width(light_container, 0, 0);
    lv_obj_set_flex_flow(light_container, LV_FLEX_FLOW_ROW_WRAP);
    lv_obj_set_flex_align(light_container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
    lv_obj_set_style_pad_all(light_container, 10, 0);
    lv_obj_set_style_pad_gap(light_container, 15, 0);
    
    /* Create light cards */
    for (int i = 0; i < num_lights; i++) {
        lv_obj_t *card = light_control_create_card(light_container, &lights[i]);
        if (!card) {
            printf("Error: Failed to create light card for %s\n", lights[i].name);
        }
    }
    
    printf("Dashboard initialized with %d lights\n", num_lights);
}

/**
 * Update dashboard with new data
 */
void dashboard_update(void)
{
    if (!dashboard_screen || !light_container) {
        return;
    }
    
    /* In a real application, this would:
     * 1. Fetch updated state from Home Assistant
     * 2. Update each light card with new state
     * 3. Handle any errors or disconnections
     */
    
    printf("Dashboard update requested\n");
}
