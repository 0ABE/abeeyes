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

// SDL library includes.
#include <SDL2/SDL.h>

namespace ABE {

/**
 * @brief A data structure to hold mouse coordinates and button clicks.
 * @date May-2025
 */
typedef struct MouseAttrs
{
    // Mouse position in the desktop/screen coordinate system.
    SDL_Point pos_wrt_screen = { 0 };
    // Mouse position in the application/window coordinate system.
    SDL_Point pos_wrt_window = { 0 };
    // Left button is down.
    bool left_btn_down = false;
    // Middle button is down.
    bool middle_btn_down = false;
    // Right button is down.
    bool right_btn_down = false;
} MouseAttrs;

} // namespace ABE