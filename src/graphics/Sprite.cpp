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
#include "Sprite.h"
#include "Texture.h"

// Standard library includes.
#include <iostream>

namespace AbeEyes {

Sprite::Sprite(const SDL_Rect& p_src_rect)
  : m_src_rect(p_src_rect)
  , m_size{ p_src_rect.w, p_src_rect.h }
{
}

Sprite::Sprite(const SDL_Rect& p_src_rect, const SDL_Point& p_size)
  : m_src_rect(p_src_rect)
  , m_size(p_size)
{
}

Sprite::Sprite(const SDL_Rect& p_src_rect, const SDL_Point& p_size, const SDL_Point& p_origin, Texture* p_texture)
  : m_src_rect(p_src_rect)
  , m_size(p_size)
  , m_origin(p_origin)
  , mp_texture(p_texture)
{
}

Sprite::Sprite(const SDL_Rect& p_src_rect, const SDL_Point& p_size, Texture* p_texture)
  : m_src_rect(p_src_rect)
  , m_size(p_size)
  , mp_texture(p_texture)
{
}

Sprite::~Sprite() = default;

// void
// Sprite::setSize(const SDL_Point& p_size)
// {
//     m_src_rect.w = p_size.x;
//     m_src_rect.h = p_size.y;
// }

void
Sprite::render(const SDL_Point& p_pos) const
{
    if (!m_visible)
        return;

    if (!mp_texture) {
        std::cerr << "Failure to render sprite (missing texture)\n";
        return;
    }

    // Create the destination rectangle based on the position and size.
    SDL_Rect dest_rect{ p_pos.x, p_pos.y, m_size.x, m_size.y };
    // Offset the position by the origin amount.
    dest_rect.x -= m_origin.x;
    dest_rect.y -= m_origin.y;

    // Render the texture using the source rectangle and destination rectangle.
    mp_texture->render(m_src_rect, dest_rect);
}

void
Sprite::setTexture(const Texture* p_texture)
{
    mp_texture = const_cast<Texture*>(p_texture);
}

} // namespace AbeEyes
