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
#include "../graphics/Grob.h"
#include "EyeState.h"

// Forward includes.
namespace AbeEyes {
class Eyeball;
class MouseAttrs;
}

namespace AbeEyes {

/**
 * @brief Represents the looking eye state.
 * @date May-2025
 */
class LookState : public EyeState
{
  public:
    enum class PupilSize
    {
        SMALL,
        MEDIUM,
        LARGE,
        XLARGE
    };

  private:
    typedef struct ScreenLimits
    {
        size_t m_small = 0;
        size_t m_medium = 0;
        size_t m_large = 0;
        size_t m_xlarge = 0;

        bool hasLimits()
        {
            return m_small > 0 && m_medium > 0 && m_large > 0 && m_xlarge > 0;
        }
    } ScreenLimits;

  public:
    LookState();
    ~LookState();

    // Interface.
    void render() const;

    void initScreenLimits(const SDL_Rect* p_rect);

    void setPosition(const SDL_Point& p_pos);
    void update(const MouseAttrs& p_mouse);

  private:
    void setLookPos(const SDL_Point& p_pos);
    void setPupilSize(PupilSize p_size);

    // Attributes
  private:
    Grob m_white{ { 32, 32 } }; // white of the eye
    Grob m_pupil;               // pupil of the eye

    size_t m_white_rad = 0;
    size_t m_pupil_rad = 0;

    ScreenLimits m_limits;
};

} // namespace AbeEyes
