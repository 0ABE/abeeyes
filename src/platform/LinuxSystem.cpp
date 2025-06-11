/**
 *        d8888 888               8888888888
 *       d88888 888               888
 *      d88P888 888               888
 *     d88P 888 88888b.   .d88b.  8888888   888  888  .d88b.  .d8888b
 *    d88P  888 888 "88b d8P  Y8b 888       888  888 d8P  Y8b 88K
 *   d88P   888 888  888 88888888 888       888  888 88888888 "Y8888b.
 *  d8888888888 888 d88P Y8b.     888       Y88b 888 Y8b.          X88
 * d88P     888 88888P"   "Y8888  8888888888 "Y88888  "Y8888   88888P'
 *                                               888
 * Somebody's watching me 8-)               Y8b d88P
 *                                           "Y88P"
 * Copyright (c) 2025, Abe Mishler
 * Licensed under the Universal Permissive License v 1.0
 * as shown at https://oss.oracle.com/licenses/upl/.
 */

// Project includes.
#include "LinuxSystem.h"

// #include <iostream>

namespace AbeEyes {

LinuxSystem::LinuxSystem()
{
    size_t screen_count = 0;
    const char* display_name = getenv("DISPLAY");
    mp_x11_display = XOpenDisplay(display_name);
    if (mp_x11_display) {
        screen_count = XScreenCount(mp_x11_display);
        m_x11_desktop = DefaultRootWindow(mp_x11_display);
        XWindowAttributes xw_attr;
        XGetWindowAttributes(mp_x11_display, m_x11_desktop, &xw_attr);
        m_desktop_area.x = xw_attr.x;
        m_desktop_area.y = xw_attr.y;
        m_desktop_area.w = xw_attr.width;
        m_desktop_area.h = xw_attr.height;
    } else {
        m_error_msg = "Failure to open X display\n";
    }

    // std::cout << "screen count: " << screen_count << "\n";
    // std::cout << "desktop: " << m_desktop_area.x << ", " << m_desktop_area.y << ", "
    //           << m_desktop_area.w << ", " << m_desktop_area.h << "\n";
}

LinuxSystem::~LinuxSystem() = default;

bool
LinuxSystem::systemMouse(SDL_Point& p_mouse) const
{
    SDL_Point window;
    unsigned int mask;
    Window child;
    if (!XQueryPointer(mp_x11_display, m_x11_desktop, &child, &child, &p_mouse.x, &p_mouse.y, &window.x, &window.y, &mask)) {
        m_error_msg = "Failure to query pointer position\n";
        return false;
    }

    return true;
}

} // namespace AbeEyes