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

// Library includes.
#include <SDL2/SDL.h>
#include <string>

// Forward declarations.
namespace AbeEyes {
class MouseAttrs;
enum class HAlign;
enum class VAlign;
}

namespace AbeEyes {

/**
 * @brief Provides mouse coordinates in the screen/desktop coordinate system.
 * @date May-2025
 */
class AbstractSystem
{
  public:
    AbstractSystem();
    ~AbstractSystem();

    virtual bool updateMouse(SDL_Window* p_sdl_window, MouseAttrs* p_mouse) const;
    virtual void updateWindowRect(HAlign p_h, VAlign p_v, SDL_Rect& p_win_rect) const;

    virtual bool error() const { return !m_error_msg.empty(); }
    virtual const std::string* getErrorMsg() const { return &m_error_msg; }

    virtual const SDL_Rect* getDesktopArea() const { return &m_desktop_area; }

  protected:
    virtual bool systemMouse(SDL_Point& p_mouse) const = 0;

    // Attributes.
  protected:
    SDL_Rect m_desktop_area = { 0 };
    mutable std::string m_error_msg = {}; // possibly changed in updateMouse()
};

} // namespace AbeEyes
