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
#include "MacSystem.h"

// OS includes.
#include <CoreGraphics/CGEvent.h>

namespace AbeEyes {

MacSystem::MacSystem()
{
    // TODO: Determine if dock is visible and where.
    //       Adjust the desktop area accordingly.
    CGDirectDisplayID main_display_ID = CGMainDisplayID();
    m_desktop_area.x = 0;
    m_desktop_area.y = 0;
    m_desktop_area.w = CGDisplayPixelsWide(main_display_ID);
    m_desktop_area.h = CGDisplayPixelsHigh(main_display_ID);
}

MacSystem::~MacSystem() = default;

bool
MacSystem::systemMouse(SDL_Point& p_mouse) const
{
    CGEventRef event = CGEventCreate(nullptr);
    CGPoint mouse = CGEventGetLocation(event);
    CFRelease(event);

    p_mouse.x = mouse.x;
    p_mouse.y = mouse.y;

    return true;
}

} // namespace AbeEyes
