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

// Library includes.
#include <SDL_rect.h>

// Forward declarations.
namespace AbeEyes {
class Texture;
}
class SDL_Renderer;

namespace AbeEyes {

/**
 * @brief Represents an optionally clipped region of a texture.
 * @date May-2025
 */
class Sprite
{
  public:
    Sprite() = delete;
    Sprite(const SDL_Rect& p_src_rect);
    Sprite(const SDL_Rect& p_src_rect, const SDL_Point& p_size);
    Sprite(const SDL_Rect& p_src_rect, const SDL_Point& p_size, Texture* p_texture);
    Sprite(const SDL_Rect& p_src_rect, const SDL_Point& p_size, const SDL_Point& p_origin, Texture* p_texture);
    ~Sprite();

    SDL_Rect getSrcRect() const { return m_src_rect; }

    bool isVisible() const { return m_visible; }
    void render(const SDL_Point& p_pos) const;

    void setOrigin(const SDL_Point& p_origin) { m_origin = p_origin; }
    // void setSize(const SDL_Point& p_size);

    void setSDLRenderer(SDL_Renderer* p_sdl_renderer) { mp_sdl_renderer = p_sdl_renderer; }
    void setTexture(const Texture* p_texture);

  private:
    Texture* mp_texture = nullptr;
    SDL_Renderer* mp_sdl_renderer = nullptr;
    SDL_Rect m_src_rect = { 0 };
    SDL_Point m_size = { 0 };
    SDL_Point m_origin = { 0 }; // origin offset
    bool m_visible = true;
};

} // namespace AbeEyes
