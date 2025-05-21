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
#include "Eyeball.h"
#include "MouseAttrs.h"
#include "graphics/SpriteList.h"

// SDL includes.
#include <SDL2/SDL.h>

namespace AbeEyes {

Eyeball::Eyeball() = default;

Eyeball::Eyeball(const SDL_Point& p_pos, int p_white_rad, int p_look_rad)
  : Eyeball()
{
    m_look_state.setPosition(p_pos);
    m_look_state.setRadii(p_white_rad, p_look_rad);
    m_blink_state.setPosition(p_pos);
}

Eyeball::~Eyeball() = default;

void
Eyeball::render() const
{
    m_look_state.render();

    if (m_state.empty())
        return;

    EyeState* state = m_state.top();
    if (state->isRenderLoopDone()) {
        state->reset();
        m_state.pop();
    } else {
        state->render();
    }
}

void
Eyeball::handleClick()
{
    if (m_state.empty())
        m_state.push(&m_blink_state);
}

/// @param p_mouse mouse wrt window.
void
Eyeball::lookAt(const MouseAttrs& p_mouse)
{
    m_look_state.update(p_mouse);
}

} // namespace AbeEyes