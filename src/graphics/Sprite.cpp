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

Sprite::Sprite(const SDL_Rect& p_rect)
  : m_rect(p_rect)
  , m_dest(p_rect)
{
}

Sprite::Sprite(const SDL_Rect& p_rect, const SDL_Rect& p_dest)
  : m_rect(p_rect)
  , m_dest(p_dest)
{
}

Sprite::Sprite(const SDL_Rect& p_rect, const SDL_Rect& p_dest, const SDL_Point& p_origin, Texture* p_texture)
  : m_rect(p_rect)
  , m_dest(p_dest)
  , m_origin(p_origin)
  , mp_texture(p_texture)
{
}

Sprite::Sprite(const SDL_Rect& p_rect, const SDL_Rect& p_dest, Texture* p_texture)
  : m_rect(p_rect)
  , m_dest(p_dest)
  , mp_texture(p_texture)
{
}

Sprite::~Sprite() = default;

// void
// Sprite::setSize(const SDL_Point& p_size)
// {
//     m_rect.w = p_size.x;
//     m_rect.h = p_size.y;
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

    // Offset by the origin amount.
    m_dest.x = p_pos.x - m_origin.x;
    m_dest.y = p_pos.y - m_origin.y;

    mp_texture->render(m_rect, m_dest);
}

void
Sprite::setTexture(const Texture* p_texture)
{
    mp_texture = const_cast<Texture*>(p_texture);
}

} // namespace AbeEyes
