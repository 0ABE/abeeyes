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
#include "states/BlinkState.h"
#include "states/LookState.h"

// Standard library includes.
#include <stack>

// Forward includes.
namespace AbeEyes {
class EyeState;
class MouseAttrs;
}
class SDL_Point;
class SDL_Rect;

namespace AbeEyes {

/**
 * @brief Represents an eye (to watch the mouse cursor.)
 * @date May-2025
 */
class Eyeball
{
  public:
    Eyeball();
    Eyeball(const SDL_Point& p_pos);
    ~Eyeball();

    void handleClick();
    void lookAt(const MouseAttrs& p_mouse);
    void render() const;

    void initPupilSizes(const SDL_Rect* p_rect);

  private:
    void setLookPos(const SDL_Point& p_pos);

    // Attributes
  private:
    mutable std::stack<EyeState*> m_state; // modified by handleClick() and render()
    LookState m_look_state;
    BlinkState m_blink_state;
    // SleepState m_sleep_state;
};

} // namespace AbeEyes
