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
#include "Texture.h"

// Library includes.
#include <SDL2/SDL_pixels.h>
#include <SDL2/SDL_surface.h>

// Standard library includes.
#include <iostream>

namespace ABE {

Texture::Texture() = default;

Texture::Texture(SDL_Renderer* p_sdl_renderer)
  : m_sdl_renderer(p_sdl_renderer)
{
}

Texture::~Texture()
{
    SDL_FreeSurface(m_sdl_surface);
    SDL_DestroyTexture(m_sdl_texture);
}

bool
Texture::load(const char* p_file_path)
{
    if (initSurface(p_file_path)) {
        return initTexture();
    }
    return false;
}

bool
Texture::load(const char* p_file_path, const SDL_Color& p_key)
{
    if (initSurface(p_file_path))
        if (isValidColorKey(p_key) && setColorKey(p_key))
            return initTexture();

    return false;
}

int
Texture::getWidth() const
{
    if (m_sdl_surface)
        return m_sdl_surface->w;
    return 0;
}

int
Texture::getHeight() const
{
    if (m_sdl_surface)
        return m_sdl_surface->h;
    return 0;
}

bool
// A valid color key is not black and has no alpha set.
Texture::isValidColorKey(const SDL_Color& key) const
{
    return (key.r > 0x00 && key.g > 0x00 && key.b > 0x00 && key.a == SDL_ALPHA_OPAQUE);
}

bool
Texture::setColorKey(const SDL_Color& p_key)
{
    const Uint32 mapped_key = SDL_MapRGB(m_sdl_surface->format, p_key.r, p_key.g, p_key.b);
    int result = SDL_SetColorKey(m_sdl_surface, SDL_TRUE, mapped_key);
    if (result < 0) {
        std::cerr << "Failure to set transparent color key\n";
        std::cerr << SDL_GetError() << "\n";
        return false;
    }
    return true;
}

void
Texture::setAlpha(Uint8 p_alpha)
{
    SDL_SetTextureAlphaMod(m_sdl_texture, p_alpha);
}

void
Texture::setBlendMode(SDL_BlendMode p_blend_mode)
{
    SDL_SetTextureBlendMode(m_sdl_texture, p_blend_mode);
}

void
Texture::render(const SDL_Rect& p_src_rect, const SDL_Rect& p_dest_rect) const
{
    if (!m_sdl_texture) {
        std::cerr << "Failure to render sprite (missing texture)\n";
        return;
    }

    SDL_RenderCopy(m_sdl_renderer, m_sdl_texture, &p_src_rect, &p_dest_rect);
}

bool
Texture::initSurface(const char* p_file_path)
{
    SDL_Surface* surface{ IMG_Load(p_file_path) };
    if (!surface) {
        std::cerr << "Failure to load file: " << p_file_path << "\n";
        std::cerr << IMG_GetError() << "\n";
        m_error = true;
        return false;
    }

    m_sdl_surface = SDL_ConvertSurfaceFormat(surface, surface->format->format, 0);
    if (!m_sdl_surface) {
        std::cerr << "Failure to convert image to display format\n";
        std::cerr << SDL_GetError() << "\n";
        m_error = true;
        return false;
    }

    SDL_FreeSurface(surface);

    return true;
}

bool
Texture::initTexture()
{
    m_sdl_texture = SDL_CreateTextureFromSurface(m_sdl_renderer, m_sdl_surface);
    if (!m_sdl_texture) {
        std::cerr << "Failure to create texture\n";
        std::cerr << SDL_GetError() << "\n";
        m_error = true;
        return false;
    }
    return true;
}

} // namespace ABE