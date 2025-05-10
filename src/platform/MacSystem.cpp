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
#include "MacSystem.h"

// OS includes.
#include <CoreGraphics/CGEvent.h>

namespace ABE {

MacSystem::MacSystem()
{
    CGDirectDisplayID main_display_ID = CGMainDisplayID();
    m_desktop_area.w = CGDisplayPixelsWide(main_display_ID);
    m_desktop_area.h = CGDisplayPixelsHigh(main_display_ID);
}

MacSystem::~MacSystem() = default;

bool
MacSystem::getCursorPos(SDL_Window* p_sdl_window, MouseAttrs* p_mouse) const
{
    CGEventRef event = CGEventCreate(nullptr);
    CGPoint mouse_cursor = CGEventGetLocation(event);
    CFRelease(event);

    // Set the out parameter with screen coords.
    p_mouse->wrt_screen.x = mouse_cursor.x;
    p_mouse->wrt_screen.y = mouse_cursor.y;

    if (!p_sdl_window) {
        m_error_msg = "Mouse coordinates wrt window are unavailable\n";
        // Return false having only screen coords.
        return false;
    }

    // Get the window coordinates.
    SDL_Point window = { 0 };
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
