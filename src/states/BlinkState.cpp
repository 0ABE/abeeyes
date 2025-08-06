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

#include "BlinkState.h"

namespace AbeEyes {

BlinkState::BlinkState()
{
    Texture* spritesheet = Resources::getTexture();
    SDL_Point dest{ 64, 64 };

    // Add the blinking eyelids.
    SpriteList* blink = m_eyelid.addSpriteList({ spritesheet });
    int x = 64;
    auto nextX = [&]() { return x += 32; };
    blink->addSprite({ { x, 0, 32, 32 }, dest })
      ->addSprite({ { nextX(), 0, 32, 32 }, dest })
      ->addSprite({ { nextX(), 0, 32, 32 }, dest })
      ->addSprite({ { nextX(), 0, 32, 32 }, dest })
      ->addSprite({ { nextX(), 0, 32, 32 }, dest })
      ->addSprite({ { nextX(), 0, 32, 32 }, dest })
      ->addSprite({ { nextX(), 0, 32, 32 }, dest })
      ->addSprite({ { nextX(), 0, 32, 32 }, dest })
      ->setLoopType(AbeEyes::LoopType::PING_PONG)
      ->setLoopLimit(1);
}

BlinkState::~BlinkState() = default;

void
BlinkState::render() const
{
    m_eyelid.render();
}

bool
BlinkState::isRenderLoopDone() const
{
    return m_eyelid.isSpriteListDone();
}

void
BlinkState::reset()
{
    m_eyelid.reset();
}

void
BlinkState::setPosition(const SDL_Point& p_pos)
{
    m_eyelid.setPosition(p_pos);
}

} // namespace AbeEyes
