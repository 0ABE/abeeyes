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
    m_white_rad = 32;

    // Add the pupils (S/M/L/XL)
    m_pupil.addSprite({ { 32, 0, 5, 5 }, { 0, 0, 10, 10 }, { 5, 5 }, spritesheet });
    m_pupil.addSprite({ { 48, 0, 8, 8 }, { 0, 0, 16, 16 }, { 8, 8 }, spritesheet });
    m_pupil.addSprite({ { 32, 16, 12, 12 }, { 0, 0, 24, 24 }, { 12, 12 }, spritesheet });
    m_pupil.addSprite({ { 48, 16, 16, 16 }, { 0, 0, 32, 32 }, { 16, 16 }, spritesheet });
    m_pupil.setPosition({ 0, 0 });

    // Set a medium pupil by default.
    setPupilSize(PupilSize::MEDIUM);
}

LookState::~LookState() = default;

void
LookState::render() const
{
    m_white.render();
    m_pupil.render();
}

void
LookState::initScreenLimits(const SDL_Rect* p_rect)
{
    long diag = sqrt(std::pow(p_rect->h, 2) + std::pow(p_rect->w, 2));
    long inc = diag / 4;
    m_limits.m_xlarge = 64;
    m_limits.m_large = inc;
    m_limits.m_medium = inc * 3;
    m_limits.m_small = inc * 4;
}

void
LookState::setPupilSize(PupilSize p_size)
{
    switch (p_size) {
        case PupilSize::SMALL:
            m_pupil.setCurrentSprite(0);
            m_pupil_rad = 6;
            break;
        case PupilSize::MEDIUM:
            m_pupil.setCurrentSprite(1);
            m_pupil_rad = 10;
            break;
        case PupilSize::LARGE:
            m_pupil.setCurrentSprite(2);
            m_pupil_rad = 14;
            break;
        case PupilSize::XLARGE:
            m_pupil.setCurrentSprite(3);
            m_pupil_rad = 18;
            break;
    }
}

void
LookState::setPosition(const SDL_Point& p_pos)
{
    m_white.setPosition(p_pos);
    m_pupil.setPosition(p_pos);
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

    if (m_limits.hasLimits()) {
        // Update the pupil size based on mouse distance.
        if (mouse_dist < m_limits.m_xlarge)
            setPupilSize(PupilSize::XLARGE);
        else if (mouse_dist < m_limits.m_large)
            setPupilSize(PupilSize::LARGE);
        else if (mouse_dist < m_limits.m_medium)
            setPupilSize(PupilSize::MEDIUM);
        else
            setPupilSize(PupilSize::SMALL);
    }

    // Calculate the max deviation of the pupil based on its size.
    const int max_look_rad = m_white_rad - m_pupil_rad;

    // Set the pupil position.
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
