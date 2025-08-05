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

// SDL includes.
#include <SDL_blendmode.h>
#include <SDL_stdinc.h>

// Forward declarations.
class SDL_Color;
class SDL_Rect;
class SDL_Renderer;
class SDL_Surface;
class SDL_Texture;

namespace AbeEyes {

/**
 * @brief A piece of artwork. Can be used as a single piece,
 *        or as a sprite sheet.
 * @date May-2025
 */
class Texture
{
  public:
    Texture();
    Texture(SDL_Renderer* p_sdl_renderer);
    ~Texture();

    bool load(const char* p_file_path);
    bool load(const char* p_file_path, const SDL_Color& p_key);

    bool hasError() const { return m_error; }
    int getWidth() const;
    int getHeight() const;

    void setAlpha(Uint8 p_alpha);
    void setBlendMode(SDL_BlendMode p_blend_mode);
    bool setColorKey(const SDL_Color& p_key);

    void setSDLRenderer(SDL_Renderer* p_sdl_renderer) { m_sdl_renderer = p_sdl_renderer; }

    void render(const SDL_Rect& p_src_rect, const SDL_Rect& p_dest_rect) const;

  private:
    bool initSurface(const char* p_file_path);
    bool initTexture();
    bool isValidColorKey(const SDL_Color& p_key) const;

  private:
    bool m_error = false;
    SDL_Renderer* m_sdl_renderer = nullptr;
    SDL_Surface* m_sdl_surface = nullptr;
    SDL_Texture* m_sdl_texture = nullptr;
};

} // namespace AbeEyes
