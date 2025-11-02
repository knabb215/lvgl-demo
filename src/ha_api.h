/**
 * @file ha_api.h
 * Home Assistant API integration
 */

#ifndef HA_API_H
#define HA_API_H

#include "light_control.h"
#include <stdbool.h>

/**
 * Initialize Home Assistant API connection
 * @param url Home Assistant URL
 * @param token Long-lived access token
 * @return true if successful
 */
bool ha_api_init(const char *url, const char *token);

/**
 * Get light state from Home Assistant
 * @param entity_id Light entity ID
 * @param state Output light state
 * @return true if successful
 */
bool ha_api_get_light_state(const char *entity_id, light_state_t *state);

/**
 * Set light state in Home Assistant
 * @param entity_id Light entity ID
 * @param state Light state to set
 * @return true if successful
 */
bool ha_api_set_light_state(const char *entity_id, const light_state_t *state);

/**
 * Turn light on/off
 * @param entity_id Light entity ID
 * @param on true to turn on, false to turn off
 * @return true if successful
 */
bool ha_api_set_light_power(const char *entity_id, bool on);

/**
 * Set light brightness
 * @param entity_id Light entity ID
 * @param brightness Brightness value (0-255)
 * @return true if successful
 */
bool ha_api_set_light_brightness(const char *entity_id, uint8_t brightness);

/**
 * Set light color (RGB)
 * @param entity_id Light entity ID
 * @param red Red component (0-255)
 * @param green Green component (0-255)
 * @param blue Blue component (0-255)
 * @return true if successful
 */
bool ha_api_set_light_color(const char *entity_id, uint8_t red, uint8_t green, uint8_t blue);

/**
 * Set light color temperature
 * @param entity_id Light entity ID
 * @param color_temp Color temperature in Kelvin
 * @return true if successful
 */
bool ha_api_set_light_color_temp(const char *entity_id, uint16_t color_temp);

#endif /* HA_API_H */
