# LVGL Dashboard for Home Assistant

A basic LVGL dashboard for controlling lights via Home Assistant. Supports both switch lights (white with brightness control) and color lights (RGB bulbs with CCT).

## Features

- **Switch Lights**: Simple on/off control with brightness slider
- **Color Lights**: Full RGB color picker with color temperature (CCT) control
- **Modern UI**: Clean, dark-themed interface built with LVGL
- **Home Assistant Integration**: Ready for REST API integration

## Light Types Supported

### Switch Lights
- Power on/off
- Brightness control (0-255)
- Visual status indicator

### Color Lights
- Power on/off
- Brightness control (0-255)
- RGB color picker (color wheel interface)
- Color temperature control (2000K - 6500K)
- Visual status indicator

## Building

### Prerequisites

- CMake 3.10 or higher
- SDL2 development libraries
- GCC or Clang compiler

#### Ubuntu/Debian
```bash
sudo apt-get install build-essential cmake libsdl2-dev
```

#### macOS
```bash
brew install cmake sdl2
```

### Build Steps

```bash
# Clone the repository with submodules
git clone --recursive https://github.com/knabb215/lvgl-demo.git
cd lvgl-demo

# Create build directory
mkdir build
cd build

# Configure and build
cmake ..
make

# Run the application
./lvgl_dashboard
```

## Configuration

To connect to your Home Assistant instance, edit `src/main.c` and update:

```c
#define HA_URL "http://your-homeassistant:8123"
#define HA_TOKEN "your_long_lived_access_token_here"
```

### Getting a Home Assistant Token

1. Log into your Home Assistant instance
2. Go to your profile (click your username in the sidebar)
3. Scroll down to "Long-Lived Access Tokens"
4. Click "Create Token"
5. Give it a name (e.g., "LVGL Dashboard")
6. Copy the token and paste it in the configuration

## Project Structure

```
lvgl-demo/
├── CMakeLists.txt          # Build configuration
├── lv_conf.h               # LVGL configuration
├── lv_drv_conf.h           # LVGL drivers configuration
├── src/
│   ├── main.c              # Application entry point
│   ├── dashboard.c/h       # Dashboard UI
│   ├── light_control.c/h   # Light control widgets
│   └── ha_api.c/h          # Home Assistant API integration
├── lvgl/                   # LVGL library (submodule)
└── lv_drivers/             # LVGL drivers (submodule)
```

## Current Implementation

The dashboard currently displays 4 sample lights:
- 2 switch lights (Living Room, Bedroom)
- 2 color lights (Kitchen RGB, Office Color)

See `SCREENSHOT_INFO.md` for a detailed description of the UI, or view `dashboard_screenshot.png` for a visual preview.

The Home Assistant API integration is currently stubbed out with logging. To enable actual control:

1. Implement HTTP requests in `src/ha_api.c` using a library like libcurl
2. Parse JSON responses from Home Assistant REST API
3. Handle authentication with the long-lived access token

## License

This project uses LVGL which is licensed under the MIT license.
