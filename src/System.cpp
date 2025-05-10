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
#include "System.h"

namespace ABE {

System::System()
{
    mp_x11_display = XOpenDisplay(getenv("DISPLAY"));
    if (mp_x11_display) {
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
}

System::~System() = default;

bool
System::getCursorPos(SDL_Window* p_sdl_window, MouseAttrs* p_mouse) const
{
    SDL_Point mouse, window;
    unsigned int mask;
    Window child;
    if (!XQueryPointer(mp_x11_display, m_x11_desktop, &child, &child, &mouse.x, &mouse.y, &window.x, &window.y, &mask)) {
        m_error_msg = "Failure to query pointer position\n";
        return false;
    }

    // Set the out parameter with screen coords.
    p_mouse->wrt_screen = mouse;

    if (!p_sdl_window) {
        m_error_msg = "Mouse coordinates wrt window are unavailable\n";
        // Return false having only screen coords.
        return false;
    }

    // Get the window coordinates.
    SDL_GetWindowPosition(p_sdl_window, &window.x, &window.y);

    // Calculate the mouse wrt window.
    if (p_mouse->wrt_screen.x < window.x) {
        p_mouse->wrt_window.x = -(window.x - p_mouse->wrt_screen.x);
    } else {
        p_mouse->wrt_window.x = p_mouse->wrt_screen.x - window.x;
    }
    if (p_mouse->wrt_screen.y < window.y) {
        p_mouse->wrt_window.y = -(window.y - p_mouse->wrt_screen.y);
    } else {
        p_mouse->wrt_window.y = p_mouse->wrt_screen.y - window.y;
    }

    return true;
}

} // namespace ABE