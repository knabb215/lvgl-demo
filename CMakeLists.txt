cmake_minimum_required(VERSION 3.10)
project(lvgl_dashboard VERSION 1.0.0 LANGUAGES C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Find SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# LVGL configuration
set(LV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lv_conf.h CACHE STRING "" FORCE)

# Add LVGL library
add_subdirectory(lvgl)

# lv_drivers configuration
set(LV_DRV_CONF_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lv_drv_conf.h CACHE STRING "" FORCE)

# Create lv_drivers library manually
file(GLOB_RECURSE LV_DRIVER_SOURCES "lv_drivers/*.c")
add_library(lv_drivers ${LV_DRIVER_SOURCES})

target_include_directories(lv_drivers PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/lv_drivers
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(lv_drivers PUBLIC lvgl ${SDL2_LIBRARIES})
target_compile_definitions(lv_drivers PUBLIC USE_SDL=1)

# Main application
add_executable(lvgl_dashboard
    src/main.c
    src/dashboard.c
    src/light_control.c
    src/ha_api.c
)

target_include_directories(lvgl_dashboard PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/lv_drivers
    ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(lvgl_dashboard PRIVATE 
    lvgl 
    lv_drivers
    ${SDL2_LIBRARIES}
    m
    pthread
)

target_compile_definitions(lvgl_dashboard PRIVATE 
    LV_USE_SDL=1
    USE_SDL=1
)
