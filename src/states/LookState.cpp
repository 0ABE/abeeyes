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

#include "LookState.h"

#include "../MouseAttrs.h"

namespace AbeEyes {

LookState::LookState()
{
    Texture* spritesheet = Resources::getTexture();
    SDL_Rect dest_rect{ 0, 0, 64, 64 };

    // Add the white of the eye (and background.)
    m_white.addSprite({ { 0, 0, 32, 32 }, dest_rect, spritesheet });
    m_white.setPosition({ 0, 0 });

    // Add the pupil.
    m_pupil.addSprite({ { 32, 0, 7, 9 }, { 0, 0, 14, 18 }, { 7, 9 }, spritesheet });
    m_pupil.setPosition({ 0, 0 });
}

LookState::~LookState() = default;

void
LookState::render() const
{
    m_white.render();
    m_pupil.render();
}

void
LookState::setPosition(const SDL_Point& p_pos)
{
    m_white.setPosition(p_pos);
    m_pupil.setPosition(p_pos);
}

void
LookState::setRadii(int p_white_rad, int p_pupil_rad)
{
    m_white_rad = p_white_rad;
    m_pupil_rad = p_pupil_rad;
}

/// @param p_mouse mouse wrt window.
void
LookState::update(const MouseAttrs& p_mouse)
{
    // X & Y deltas.
    const SDL_Point white_pos = m_white.getPosition();
    const int x_diff = p_mouse.pos_wrt_window.x - white_pos.x;
    const int y_diff = p_mouse.pos_wrt_window.y - white_pos.y;
    // Protect against zeros.
    if ((x_diff == 0) || (y_diff == 0))
        return;

    const int mouse_dist = (int)sqrt((x_diff * x_diff) + (y_diff * y_diff));
    const double slope = (x_diff == 0 || y_diff == 0 ? 0 : (double)y_diff / x_diff);
    const double angle = atan(slope);
    const double cos_angle = (x_diff == 0 ? 0. : cos(angle));
    const double sin_angle = (y_diff == 0 ? 0. : sin(angle));
    const double sin_n_angle = (y_diff == 0 ? 0. : sin(-angle));
    const int max_look_rad = m_white_rad - m_pupil_rad;

    if (mouse_dist < max_look_rad) {
        setLookPos(p_mouse.pos_wrt_window);
    } else {
        int x, y;
        // bottom right
        if (x_diff > 0 && y_diff > 0) {
            x = white_pos.x + (max_look_rad * cos_angle);
            y = white_pos.y + (max_look_rad * sin_angle);
        }
        // top right
        else if (x_diff > 0 && y_diff < 0) {
            x = white_pos.x + (max_look_rad * cos_angle);
            y = white_pos.y - (max_look_rad * sin_n_angle);
        }
        // top left
        else if (x_diff < 0 && y_diff < 0) {
            x = white_pos.x - (max_look_rad * cos_angle);
            y = white_pos.y - (max_look_rad * sin_angle);
        }
        // bottom left
        else if (x_diff < 0 && y_diff > 0) {
            x = white_pos.x - (max_look_rad * cos_angle);
            y = white_pos.y + (max_look_rad * sin_n_angle);
        }
        setLookPos({ x, y });
    }
}

void
LookState::setLookPos(const SDL_Point& p_pos)
{
    m_pupil.setPosition(p_pos);
}

} // namespace AbeEyes
