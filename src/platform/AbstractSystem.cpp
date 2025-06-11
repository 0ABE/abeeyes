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
#include "AbstractSystem.h"
#include "../MouseAttrs.h"
#include "../graphics/AlignTypes.h"

#include <iostream>

namespace AbeEyes {

AbstractSystem::AbstractSystem()
{
    //    if (SDL_GetNumVideoDisplays() < 1) {
    //        m_error_msg = "Failure to find a video display: " + std::string{ *SDL_GetError() };
    //        return;
    //    }
    //
    //    SDL_DisplayMode display_mode;
    //    if (SDL_GetDesktopDisplayMode(0, &display_mode) < 0) {
    //        m_error_msg = "Failure to get the display mode: " + std::string{ *SDL_GetError() };
    //        return;
    //    }
    //
    //    m_desktop_area = { 0, 0, display_mode.w, display_mode.h };
}

AbstractSystem::~AbstractSystem() = default;

bool
AbstractSystem::updateMouse(SDL_Window* p_sdl_window, MouseAttrs* p_mouse) const
{
    SDL_Point mouse;
    if (!systemMouse(mouse))
        return false;

    // Set the mouse attributes with screen coords.
    p_mouse->pos_wrt_screen = mouse;

    // Set the mouse attributes with button press info.
    Uint32 buttons = SDL_GetGlobalMouseState(nullptr, nullptr);
    p_mouse->left_btn_down = (buttons & SDL_BUTTON(1));
    p_mouse->middle_btn_down = (buttons & SDL_BUTTON(2));
    p_mouse->right_btn_down = (buttons & SDL_BUTTON(3));

    if (!p_sdl_window) {
        m_error_msg = "Mouse coordinates wrt window are unavailable\n";
        // Return false having only screen coords.
        return false;
    }

    // Get the window coordinates.
    SDL_Point window;
    SDL_GetWindowPosition(p_sdl_window, &window.x, &window.y);

    // Calculate the mouse wrt window.
    if (p_mouse->pos_wrt_screen.x < window.x) {
        p_mouse->pos_wrt_window.x = -(window.x - p_mouse->pos_wrt_screen.x);
    } else {
        p_mouse->pos_wrt_window.x = p_mouse->pos_wrt_screen.x - window.x;
    }
    if (p_mouse->pos_wrt_screen.y < window.y) {
        p_mouse->pos_wrt_window.y = -(window.y - p_mouse->pos_wrt_screen.y);
    } else {
        p_mouse->pos_wrt_window.y = p_mouse->pos_wrt_screen.y - window.y;
    }

    return true;
}

/**
 * @brief Update the window position (x,y) based on the alignment parameters.
 * @date May-2025
 */
void
AbstractSystem::updateWindowRect(HAlign p_h, VAlign p_v, SDL_Rect& p_win_rect) const
{
    const SDL_Rect* desktop_area = getDesktopArea();
    switch (p_h) {
        case HAlign::NONE:
            break;
        case HAlign::LEFT:
            p_win_rect.x = desktop_area->x;
            break;
        case HAlign::RIGHT:
            p_win_rect.x = desktop_area->w - p_win_rect.w;
            break;
    }
    switch (p_v) {
        case VAlign::NONE:
            break;
        case VAlign::TOP:
            p_win_rect.y = desktop_area->y;
            break;
        case VAlign::BOTTOM:
            p_win_rect.y = desktop_area->h - p_win_rect.h;
            break;
    }
}

void
AbstractSystem::updateWindowRect(int p_h, int p_v, SDL_Rect& p_win_rect) const
{
    p_win_rect.x += p_h;
    p_win_rect.y += p_v;
}

} // namespace AbeEyes