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
#include "Resources.h"

namespace ABE {

// Static members.
static std::map<const char*, Texture> m_textures;

Resources::Resources() = default;

Resources::~Resources() = default;

Resources*
Resources::addSprite(Sprite&& p_sprite)
{
    m_sprites.emplace_back(std::move(p_sprite));
    return this;
}

Resources*
Resources::addSpriteList(SpriteList&& p_spritelist)
{
    m_spritelists.emplace_back(std::move(p_spritelist));
    return this;
}

Texture*
Resources::addTexture(Texture&& p_texture)
{
    return addTexture("default", std::move(p_texture));
}

Texture*
Resources::addTexture(const char* p_name, Texture&& p_texture)
{
    m_textures[p_name] = std::move(p_texture);
    if (m_textures.contains(p_name))
        return &m_textures[p_name];

    return nullptr;
}

Texture*
Resources::getTexture()
{
    return getTexture("default");
}

Sprite*
Resources::getSprite(size_t p_index)
{
    if (p_index >= m_sprites.size())
        return nullptr;

    return &m_sprites[p_index];
}

const Sprite*
Resources::getSprite(size_t p_index) const
{
    if (p_index >= m_sprites.size())
        return nullptr;

    return &m_sprites[p_index];
}

// bool
// Resources::getSprites(Sprites* p_sprites)
// {
//     if (m_sprites.empty())
//         return false;
//
//     p_sprites = &m_sprites;
//     return true;
// }

SpriteList*
Resources::getSpriteList(size_t p_index)
{
    if (p_index >= m_spritelists.size())
        return nullptr;

    return &m_spritelists[p_index];
}

const SpriteList*
Resources::getSpriteList(size_t p_index) const
{
    if (p_index >= m_spritelists.size())
        return nullptr;

    return &m_spritelists[p_index];
}

// bool
// Resources::getSpriteLists(SpriteLists* p_spritelists)
// {
//     if (m_spritelists.empty())
//         return false;
//
//     p_spritelists = &m_spritelists;
//     return true;
// }

Texture*
Resources::getTexture(const char* p_name)
{
    if (m_textures.contains(p_name))
        return &m_textures[p_name];

    return nullptr;
}

}; // namespace ABE
