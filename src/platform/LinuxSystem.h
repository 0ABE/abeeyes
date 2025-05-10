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

#pragma once

// Project includes.
#include "MouseAttrs.h"

// OS includes.
#include <X11/Xlib.h>

// Library includes.
#include <SDL2/SDL.h>
#include <string>

namespace ABE {

/**
 * @brief Interacts with OS-specific libraries to provide
 *        mouse coordinates in the screen/desktop coordinate system.
 * @date May-2025
 */
class LinuxSystem
{
  public:
    LinuxSystem();
    ~LinuxSystem();

    bool getCursorPos(SDL_Window* p_sdl_window, MouseAttrs* p_mouse) const;

    const SDL_Rect* getDesktopArea() const { return &m_desktop_area; }

    bool error() const { return !m_error_msg.empty(); }
    const std::string* getErrorMsg() const { return &m_error_msg; }

  private:
    Display* mp_x11_display = nullptr;
    Window m_x11_desktop;
    SDL_Rect m_desktop_area;
    MouseAttrs m_mouse;

    mutable std::string m_error_msg = {}; // possibly changed in getCursorPos()
};

} // namespace ABE
