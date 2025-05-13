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
#include "Resources.h"

// Library includes.
#include <SDL2/SDL.h>

namespace AbeEyes {

/**
 * @brief A grob represents a graphical object with a position,
 *        and the ability to appear in different ways: with one
 *        or more sprites, and one or more spritelists.
 * @date May-2025
 */
class Grob
{
  public:
    Grob();
    ~Grob();

    Resources* addSprite(Sprite&& p_sprite);

    void move(const SDL_Point& p_move);
    void setPosition(const SDL_Point& p_pos) { m_pos = p_pos; }
    SDL_Point getPosition() const { return m_pos; }

    void render() const;
    void renderSprite(size_t p_idx) const;
    void renderSpriteList(size_t p_idx) const;

  private:
    SDL_Point m_pos = { 0, 0 }; // position
    Resources m_resources;
    size_t m_current_sprite_idx = 0;     // index to the current sprite to render
    size_t m_current_spritelist_idx = 0; // index to the current spritelist to render
};

} // namespace AbeEyes