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

namespace AbeEyes {

// Type definitions.
typedef std::vector<Sprite> Sprites;

// Forward declarations.
class Texture;

/**
 * @brief A list of Sprites for animation.
 * @date May-2025
 */
class SpriteList
{
  public:
    SpriteList() = delete;
    explicit SpriteList(const char* p_name);
    SpriteList(const char* p_name, Texture* p_texture);
    ~SpriteList();

    SpriteList* addSprite(Sprite&& p_sprite);
    // void setFramerate(int p_rate) { m_framerate = p_rate; }
    void setTexture(const Texture* p_texture) { m_texture = const_cast<Texture*>(p_texture); }

    const Sprite& getNext() const;
    void setLoopType(LoopType p_loop_type);

    // void setSize(const SDL_Point& p_size);
    SDL_Rect getRect() const;

    size_t size() const { return m_list.size(); }

    void render(const SDL_Point& p_pos) const;

  private:
    const char* m_name;
    Texture* m_texture = nullptr;
    // int m_framerate = 0;

    mutable int m_current = 0;
    mutable int m_loop_dir = 1;

    Sprites m_list = {};
    LoopType m_loop_type = LoopType::FORWARD;
    bool m_visible = true;
};

} // namespace AbeEyes