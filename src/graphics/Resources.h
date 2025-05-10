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
#include "Sprite.h"
#include "SpriteList.h"
#include "Texture.h"

// Standard library includes.
#include <map>

namespace ABE {

// Type definitions.
typedef std::vector<SpriteList> SpriteLists;

/**
 * @brief Holds Sprites, SpriteLists, and Textures.
 *        Textures are static to be available to all Sprites
 *        and SpriteLists.
 * @date May-2025
 */
class Resources
{
  public:
    Resources();
    ~Resources();

    Resources* addSprite(Sprite&& p_sprite);
    Resources* addSpriteList(SpriteList&& p_spritelist);

    Sprite* getSprite(size_t p_index);
    const Sprite* getSprite(size_t p_index) const;

    // bool getSprites(Sprites* p_sprites);

    SpriteList* getSpriteList(size_t p_index);
    const SpriteList* getSpriteList(size_t p_index) const;

    // bool getSpriteLists(SpriteLists* p_spritelists);

    static Texture* addTexture(Texture&& p_texture);
    static Texture* addTexture(const char* p_name, Texture&& p_texture);

    static Texture* getTexture();
    static Texture* getTexture(const char* p_name);

  private:
    Sprites m_sprites;
    SpriteLists m_spritelists;
};

} // namespace ABE