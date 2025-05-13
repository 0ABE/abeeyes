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
#if defined(__APPLE__)
#include "platform/MacSystem.h"
#elif defined(__linux__)
#include "platform/LinuxSystem.h"
#endif
#include "Eyeball.h"
#include "MouseAttrs.h"
#include "graphics/AlignTypes.h"
#include "graphics/Grob.h"
#include "graphics/LoopType.h"
#include "graphics/Resources.h"
#include "graphics/Sprite.h"
#include "graphics/SpriteList.h"
#include "graphics/Texture.h"

// SDL includes.
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_video.h>

// Standard library includes.
#include <iostream>
#include <map>
#include <memory>

// Globals.
SDL_Rect g_win_rect{ 0, 0, 128, 64 };
#if defined(__APPLE__)
AbeEyes::MacSystem g_system;
#elif defined(__linux__)
AbeEyes::LinuxSystem g_system;
#endif
SDL_Window* gp_sdl_window = nullptr;
SDL_Renderer* gp_sdl_renderer = nullptr;
AbeEyes::MouseAttrs g_mouse;
// A "layer" for eyeball rendering.
std::map<std::string, AbeEyes::Eyeball> g_eyeball_layer;

// Function prototypes.
// Shut down SDL and free resources.
void
close();
// Init resources used by the App.
bool
initResources();
// Start up SDL and create a window.
bool
initSDL(const char*);
// The main loop, where the action happens.
void
mainLoop();
// Draw.
void
render();
// The more things change... the more things need to change.
void
update();

int
main(int argc, char* argv[])
{
    // Check if there was an error initializing the desktop area.
    if (g_system.error()) {
        std::cerr << g_system.getErrorMsg() << "\n";
        return EXIT_FAILURE;
    }

    const char* win_title = "AbeEyes";
    if (!initSDL(win_title))
        return EXIT_FAILURE;

    if (!initResources())
        return EXIT_FAILURE;

    // Process the action.
    mainLoop();

    // After the main loop is done, make a successful exit.
    return EXIT_SUCCESS;
}

void
mainLoop()
{
    bool running = true;
    while (running) {
        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (SDL_QUIT == e.type) {
                running = false;
                break;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                        running = false;
                        break;
                    case SDLK_UP:
                        g_system.updateWindowRect(AbeEyes::HAlign::NONE, AbeEyes::VAlign::TOP, g_win_rect);
                        break;
                    case SDLK_DOWN:
                        g_system.updateWindowRect(AbeEyes::HAlign::NONE, AbeEyes::VAlign::BOTTOM, g_win_rect);
                        break;
                    case SDLK_LEFT:
                        g_system.updateWindowRect(AbeEyes::HAlign::LEFT, AbeEyes::VAlign::NONE, g_win_rect);
                        break;
                    case SDLK_RIGHT:
                        g_system.updateWindowRect(AbeEyes::HAlign::RIGHT, AbeEyes::VAlign::NONE, g_win_rect);
                        break;
                }
                SDL_SetWindowPosition(gp_sdl_window, g_win_rect.x, g_win_rect.y);
                // Update the win rect with the actual position in case desktop furniture got in the way.
                SDL_GetWindowPosition(gp_sdl_window, &g_win_rect.x, &g_win_rect.y);
            }
        }
        if (running) {
            update();
            render();
        }
    }
    // Exiting the main loop.
}

void
close()
{
    // Free resources.
    SDL_DestroyRenderer(gp_sdl_renderer);
    SDL_DestroyWindow(gp_sdl_window);

    // Quit SDL subsystems.
    IMG_Quit();
    SDL_Quit();
}

bool
initResources()
{
    // Load the spritesheet as a texture for clipping into Sprites.
    AbeEyes::Texture* spritesheet = AbeEyes::Resources::addTexture({ gp_sdl_renderer });
    const char* file_path = "../rsrc/blink_sheet.png";
    if (!spritesheet->load(file_path, { 0xD7, 0x7B, 0xBA, SDL_ALPHA_OPAQUE })) {
        return false;
    }

    // Create the eyes.
    AbeEyes::Eyeball
      left_eye({ 32, 32 }, 32, 12),
      right_eye({ 96, 32 }, 32, 12);

    // Copy the eyes to their layer for rendering.
    g_eyeball_layer["left_eye"] = left_eye;
    g_eyeball_layer["right_eye"] = right_eye;

    return true;
}

bool
initSDL(const char* p_win_title)
{
    // Init SDL subsystems.
    const Uint32 sdl_flags = SDL_INIT_VIDEO | SDL_INIT_EVENTS;
    if (SDL_Init(sdl_flags) < 0) {
        std::cerr << "Failure to initialize SDL: " << SDL_GetError() << "\n";
        close();
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"))
        std::cout << "Failure to enable linear texture filtering\n";

    // Make a borderless window and place it in the lower right corner.
    const Uint32 win_flags = /*| SDL_WINDOW_UTILITY */ SDL_WINDOW_BORDERLESS;
    g_system.updateWindowRect(AbeEyes::HAlign::RIGHT, AbeEyes::VAlign::BOTTOM, g_win_rect);
    gp_sdl_window = SDL_CreateWindow(p_win_title, g_win_rect.x, g_win_rect.y, g_win_rect.w, g_win_rect.h, win_flags);
    if (!gp_sdl_window) {
        std::cerr << "Failure to create SDL Window: " << SDL_GetError() << "\n";
        close();
        return false;
    }

    // Update the actual window position into the window rect.
    // It might not have been created in the actual location specified
    // above due to other system furniture like a dock or taskbar.
    SDL_GetWindowPosition(gp_sdl_window, &g_win_rect.x, &g_win_rect.y);

    const Uint32 renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    gp_sdl_renderer = SDL_CreateRenderer(gp_sdl_window, -1, renderer_flags);
    if (!gp_sdl_renderer) {
        std::cerr << "Failure to create SDL Renderer: " << SDL_GetError() << "\n";
        close();
        return false;
    }

    // Set the render color to white.
    SDL_SetRenderDrawColor(gp_sdl_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);

    const int img_flags = IMG_INIT_PNG;
    if (!(IMG_Init(img_flags))) {
        std::cerr << "Failure to initialize image loading: " << IMG_GetError() << "\n";
        close();
        return false;
    }

    SDL_RendererInfo info;
    if (SDL_GetRendererInfo(gp_sdl_renderer, &info) < 0) {
        std::cerr << "Failure to get information about the rendering context: " << SDL_GetError() << "\n";
        close();
        return false;
    }

    return true;
}

void
update()
{
    // Get the current mouse/cursor position and button presses...
    g_system.updateMouse(gp_sdl_window, &g_mouse);
    // and use it to update where the eyeballs look.
    for (auto& it : g_eyeball_layer)
        it.second.update(g_mouse.pos_wrt_window);
}

void
render()
{
    SDL_SetRenderDrawColor(gp_sdl_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gp_sdl_renderer);

    // Render the eyeballs.
    for (const auto& it : g_eyeball_layer)
        it.second.render();

    SDL_RenderPresent(gp_sdl_renderer);
}
