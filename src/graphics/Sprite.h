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
#include <SDL2/SDL_rect.h>

// Forward declarations.
class SDL_Renderer;
namespace ABE {
class Texture;
}

namespace ABE {

/**
 * @brief Represents an optionally clipped region of a texture.
 * @date May-2025
 */
class Sprite
{
  public:
    Sprite() = delete;
    Sprite(const SDL_Rect& p_rect);
    Sprite(const SDL_Rect& p_rect, const SDL_Rect& p_dest, Texture* p_texture);
    Sprite(const SDL_Rect& p_rect, const SDL_Rect& p_dest, const SDL_Point& p_origin, Texture* p_texture);
    ~Sprite();

    SDL_Rect getRect() const { return m_rect; }

    void render(const SDL_Point& p_pos) const;

    // void setSize(const SDL_Point& p_size);

    void setSDLRenderer(SDL_Renderer* p_sdl_renderer) { mp_sdl_renderer = p_sdl_renderer; }
    void setTexture(const Texture* p_texture);

  private:
    Texture* mp_texture = nullptr;
    SDL_Renderer* mp_sdl_renderer = nullptr;
    SDL_Rect m_rect = { 0 };
    mutable SDL_Rect m_dest = { 0 }; // updated by render()
    SDL_Point m_origin = { 0, 0 };   // origin offset
    bool m_visible = true;
};

} // namespace ABE
