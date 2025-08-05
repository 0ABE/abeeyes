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
#include "Timer.h"

// SDL includes.
#include <SDL_timer.h>

namespace AbeEyes {

Timer::Timer(int fps)
  : m_frame_rate(fps)
  , m_millis_per_frame(1000. / fps)
{
    // 60 fps = 16.666667 ms / frame
    // 30 fps = 33.333333 ms / frame
    // std::cout << "ms/frame: " << m_millis_per_frame << "\n";
}

Timer::~Timer() = default;

void
Timer::start()
{
    m_ticks = SDL_GetTicks();
    m_started = true;
}

Uint32
Timer::stop()
{
    if (!m_started)
        return 0;

    m_started = false;
    return SDL_GetTicks64() - m_ticks;
}

/// @brief Get the amount of time to delay based on the number of ticks that have elapsed.
/// @param p_ticks The number of ticks that have elapsed.
/// @return The number of ticks to delay to achieve the wanted frame rate.
Uint32
Timer::getDelay(Uint32 p_ticks) const
{
    const Uint32 sleep_time = m_millis_per_frame - p_ticks;
    if (sleep_time > 0 && sleep_time < m_millis_per_frame)
        return sleep_time;

    return 0;
}

} // namespace AbeEyes
