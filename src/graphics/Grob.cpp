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
#include "Grob.h"

namespace AbeEyes {

Grob::Grob() = default;

Grob::Grob(const SDL_Point& p_origin)
  : m_origin(p_origin)
{
}

Grob::~Grob() = default;

Sprite*
Grob::addSprite(Sprite&& p_sprite)
{
    if (hasCustomOrigin())
        p_sprite.setOrigin(m_origin);

    return m_resources.addSprite(std::move(p_sprite));
}

SpriteList*
Grob::addSpriteList(SpriteList&& p_spritelist)
{
    if (hasCustomOrigin())
        p_spritelist.setOrigin(m_origin);

    return m_resources.addSpriteList(std::move(p_spritelist));
}

void
Grob::move(const SDL_Point& p_point)
{
    m_pos.x += p_point.x;
    m_pos.y += p_point.y;
}

void
Grob::render() const
{
    // Render the current sprite.
    renderSprite(m_current_sprite_idx);
    // Render the current spritelist.
    renderSpriteList(m_current_spritelist_idx);
}

void
Grob::renderSprite(size_t p_idx) const
{
    if (const Sprite* s = m_resources.getSprite(p_idx))
        s->render(m_pos);
}

void
Grob::renderSpriteList(size_t p_idx) const
{
    if (const SpriteList* ss = m_resources.getSpriteList(p_idx))
        ss->render(m_pos);
}

bool
Grob::hasCustomOrigin() const
{
    return (m_origin.x != 0) && (m_origin.y != 0);
}

}; // namespace AbeEyes
