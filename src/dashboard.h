/**
 * @file dashboard.h
 * Dashboard UI components
 */

#ifndef DASHBOARD_H
#define DASHBOARD_H

#include "lvgl/lvgl.h"

/**
 * Initialize the dashboard UI
 * @param parent Parent object to create the dashboard in
 */
void dashboard_init(lv_obj_t *parent);

/**
 * Update dashboard with new data
 */
void dashboard_update(void);

#endif /* DASHBOARD_H */
