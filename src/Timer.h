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

// SDL includes.
#include <SDL_timer.h>

namespace AbeEyes {

/**
 * @brief A timer to control frame rate.
 * @date Jun-2025
 */
class Timer
{
  public:
    Timer() = delete;
    Timer(int fps);
    ~Timer();

    void start();
    Uint32 stop();
    Uint32 getDelay(Uint32 p_ticks) const;

    void setFrameRate(int fps) { m_frame_rate = fps; }

    // Attributes
  private:
    int m_frame_rate = 0; // frames per second
    double m_millis_per_frame = 0;
    Uint32 m_ticks = 0;
    bool m_started = false;
};

} // namespace AbeEyes
