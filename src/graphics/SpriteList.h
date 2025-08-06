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
#include "LoopType.h"
#include "Sprite.h"

// Standard library includes.
#include <vector>

// Forward declarations.
namespace AbeEyes {
class Texture;
}

namespace AbeEyes {

// Type definitions.
typedef std::vector<Sprite> Sprites;

/**
 * @brief A list of Sprites for animation.
 * @date May-2025
 */
class SpriteList
{
  public:
    SpriteList() = delete;
    SpriteList(const SDL_Point& p_origin, Texture* p_texture);
    SpriteList(Texture* p_texture);
    ~SpriteList();

    SpriteList* addSprite(Sprite&& p_sprite);
    // void setFramerate(int p_rate) { m_framerate = p_rate; }
    void setTexture(const Texture* p_texture) { m_texture = const_cast<Texture*>(p_texture); }

    SpriteList* setLoopType(LoopType p_type);
    SpriteList* setLoopLimit(size_t p_limit);
    void resetLoop();

    bool isRenderLoopDone() const;

    // void setSize(const SDL_Point& p_size);
    SDL_Rect getSrcRect() const;

    size_t size() const { return m_list.size(); }

    void render(const SDL_Point& p_pos) const;

    void setOrigin(const SDL_Point& p_origin);

  private:
    const Sprite* getNext() const;
    bool hasCustomOrigin() const;
    void incrementCounts() const; // marked const to be called from render()

    // Attributes.
  private:
    Texture* m_texture = nullptr;
    // int m_framerate = 0;

    // The index for the current sprite to be rendered.
    mutable size_t m_current = 0;
    // Which direction should the next sprite come from in the list.
    mutable int m_loop_dir = 1;
    // Stop after looping this many times.
    size_t m_loop_limit = 0; // 0 means no limit
    // Keep track of the number of loops played.
    mutable size_t m_loop_count = 0;
    // Keep track of the number of sprites rendered.
    mutable size_t m_sprite_count = 0;

    Sprites m_list = {};
    LoopType m_loop_type = LoopType::FORWARD;

    mutable bool m_visible = true; // can be udpated by render()

    SDL_Point m_origin = { 0 }; // offset origin
};

} // namespace AbeEyes