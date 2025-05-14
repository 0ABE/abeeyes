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
#include "SpriteList.h"

// Standard library includes.
#include <cassert>

namespace AbeEyes {
SpriteList::SpriteList(const SDL_Point& p_origin, Texture* p_texture)
  : m_origin(p_origin)
  , m_texture(p_texture)
{
}

SpriteList::SpriteList(Texture* p_texture)
  : m_texture(p_texture)
{
}

SpriteList::~SpriteList() = default;

SpriteList*
SpriteList::addSprite(Sprite&& p_sprite)
{
    if (hasCustomOrigin())
        p_sprite.setOrigin(m_origin);

    if (m_texture)
        p_sprite.setTexture(m_texture);

    m_list.push_back(std::move(p_sprite));

    return this;
}

const Sprite*
SpriteList::getNext() const
{
    assert(m_current >= 0);

    LoopType loop = m_loop_type;
    if (m_loop_type == LoopType::FWD_REV) {
        if (m_loop_dir > 0)
            loop = LoopType::FORWARD;
        else if (m_loop_dir < 0)
            loop = LoopType::REVERSE;
    }

    if (loop == LoopType::FORWARD) {
        m_loop_dir = 1;
        if (m_current >= size()) {
            if (m_loop_type == LoopType::FWD_REV) {
                m_loop_dir = -1;
                m_current = size() - 1;
                return &m_list[m_current];
            } else {
                m_current = 0;
            }
        }
        return &m_list[m_current++];
    }

    if (loop == LoopType::REVERSE) {
        m_loop_dir = -1;
        if (m_current <= 1) {
            if (m_loop_type == LoopType::FWD_REV) {
                m_loop_dir = 1;
                m_current = 0;
                return &m_list[m_current];
            } else {
                m_current = size() - 1;
            }
        }
        return &m_list[m_current--];
    }

    // LoopType::NONE
    m_current = 0;
    return &m_list[m_current];
}

void
SpriteList::setLoopType(LoopType p_loop_type)
{
    m_loop_type = p_loop_type;
    switch (m_loop_type) {
        case LoopType::NONE:
            m_loop_dir = 0;
            break;
        case LoopType::FORWARD:
            [[fallthrough]];
        case LoopType::FWD_REV:
            m_loop_dir = 1;
            break;
        case LoopType::REVERSE:
            m_loop_dir = -1;
            break;
    }
}

// void
// SpriteList::setSize(const SDL_Point& p_size)
// {
//     for (Sprite& s : m_list)
//         s.setSize(p_size);
// }

SDL_Rect
SpriteList::getRect() const
{
    if (m_list.empty())
        return { 0, 0, 0, 0 };

    // Return the current sprite rect.
    return m_list[m_current].getRect();
}

void
SpriteList::render(const SDL_Point& p_pos) const
{
    if (!m_visible)
        return;

    const Sprite* s = getNext();
    if (!s->isVisible()) {
        // If an invisible sprite is found, set the whole list as invisible.
        m_visible = false;
        // Avoid rendering.
        return;
    }
    s->render(p_pos);
}

bool
SpriteList::hasCustomOrigin() const
{
    return (m_origin.x != 0) && (m_origin.y != 0);
}

void
SpriteList::setOrigin(const SDL_Point& p_origin)
{
    m_origin = p_origin;
    for (auto& s : m_list)
        s.setOrigin(p_origin);
}

} // namespace AbeEyes
