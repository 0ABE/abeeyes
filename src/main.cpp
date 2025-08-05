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
#elif defined(_WIN32) || defined(_WIN64)
#include "platform/WinSystem.h"
#endif
#include "AbeEyesConfig.h"
#include "Eyeball.h"
#include "MouseAttrs.h"
#include "Timer.h"
#include "graphics/AlignTypes.h"
#include "graphics/Resources.h"
#include "graphics/Texture.h"

// AbeArgs includes.
#include "abeargs.h"

// SDL includes.
#include <SDL.h>
#include <SDL_image.h>

// Standard library includes.
#include <iostream>
#include <map>

// Globals.
const char* g_app_name = "AbeEyes";
SDL_Rect g_win_rect{ -1, -1, 128, 64 };
#if defined(__APPLE__)
AbeEyes::MacSystem g_system;
#elif defined(__linux__)
AbeEyes::LinuxSystem g_system;
#elif defined(_WIN32) || defined(_WIN64)
AbeEyes::WinSystem g_system;
#endif
SDL_Window* gp_sdl_window = nullptr;
SDL_Renderer* gp_sdl_renderer = nullptr;
AbeEyes::MouseAttrs g_mouse;
AbeEyes::Timer g_refresh_timer{ 60 };
// A "layer" for eyeball rendering.
std::map<std::string, AbeEyes::Eyeball> g_eyeball_layer;

// Function prototypes.
// Parse any command line arguments.
bool
parseCommandLineArgs(int argc, char* argv[], bool* err);
// Shut down SDL and free resources.
void
close();
// An info dialog.
void
showAboutGUI();
void
showVersion();
void
showHelp(const AbeArgs::Parser& parser);
// Detect if a click event occurred.
bool
detectClickEvent();
// Init resources used by the App.
bool
initResources();
// Start up SDL and create a window.
bool
initSDL();
// The main loop, where the action happens.
void
mainLoop();
// Draw.
void
render();
// The more things change... the more things need to change.
void
update();

bool
parseCommandLineArgs(int argc, char* argv[], bool* err)
{
    using namespace AbeArgs;
    const int X_POS_ID = 1;
    const int Y_POS_ID = 2;
    const int VERSION_ID = 3;
    const int HELP_ID = 4;
    Parser parser;
    parser.addArgument({ OPTIONAL, X_POS_ID, "x", "x_pos", "The window's x position.", INTEGER_TYPE });
    parser.addArgument({ OPTIONAL, Y_POS_ID, "y", "y_pos", "The window's y position.", INTEGER_TYPE });
    parser.addArgument({ X_SWITCH, VERSION_ID, "v", "version", "Show version information and exit." });
    parser.addArgument({ X_SWITCH, HELP_ID, "h", "help", "Show this help information and exit." });

    ParsedArguments_t results = parser.exec(argc, argv);
    if (parser.error()) {
        std::cerr << parser.getErrorMsg() << "\n";
        *err = true;
        return false;
    }

    for (const auto& r : results)
        switch (r.first) {
            case X_POS_ID:
                g_win_rect.x = std::get<int>(r.second);
                break;
            case Y_POS_ID:
                g_win_rect.y = std::get<int>(r.second);
                break;
            case VERSION_ID:
                showVersion();
                return false;
            case HELP_ID:
                showHelp(parser);
                return false;
        }

    return true;
}

int
main(int argc, char* argv[])
{
    // Check if there was an error initializing the desktop area.
    if (g_system.error()) {
        std::cerr << g_system.getErrorMsg() << "\n";
        return EXIT_FAILURE;
    }

    if (argc > 1) {
        bool err = false;
        const bool ok = parseCommandLineArgs(argc, argv, &err);
        if (err)
            return EXIT_FAILURE;
        if (!ok)
            return EXIT_SUCCESS;
    }

    if (!initSDL())
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
        // Start recording the time taken by this frame.
        g_refresh_timer.start();

        SDL_Event e;
        while (SDL_PollEvent(&e)) {
            if (SDL_QUIT == e.type) {
                running = false;
                break;
            } else if (e.type == SDL_KEYDOWN) {
                const bool with_lshift = e.key.keysym.mod & KMOD_LSHIFT;
                const bool with_rshift = e.key.keysym.mod & KMOD_RSHIFT;
                // Left shift moves the window by 1px.
                // Right shift moves the window by 10px.
                int d_xy = (with_lshift ? 1 : (with_rshift ? 10 : 0));
                switch (e.key.keysym.sym) {
                    case SDLK_a:
                        showAboutGUI();
                        break;
                    case SDLK_q:
                        running = false;
                        break;
                    case SDLK_UP:
                        if (d_xy > 0)
                            g_system.updateWindowRect(0, -d_xy, g_win_rect);
                        else
                            g_system.updateWindowRect(AbeEyes::HAlign::NONE, AbeEyes::VAlign::TOP, g_win_rect);
                        break;
                    case SDLK_DOWN:
                        if (d_xy > 0)
                            g_system.updateWindowRect(0, d_xy, g_win_rect);
                        else
                            g_system.updateWindowRect(AbeEyes::HAlign::NONE, AbeEyes::VAlign::BOTTOM, g_win_rect);
                        break;
                    case SDLK_LEFT:
                        if (d_xy > 0)
                            g_system.updateWindowRect(-d_xy, 0, g_win_rect);
                        else
                            g_system.updateWindowRect(AbeEyes::HAlign::LEFT, AbeEyes::VAlign::NONE, g_win_rect);
                        break;
                    case SDLK_RIGHT:
                        if (d_xy > 0)
                            g_system.updateWindowRect(d_xy, 0, g_win_rect);
                        else
                            g_system.updateWindowRect(AbeEyes::HAlign::RIGHT, AbeEyes::VAlign::NONE, g_win_rect);
                        break;
                }
                SDL_SetWindowPosition(gp_sdl_window, g_win_rect.x, g_win_rect.y);
                // Update the win rect with the actual position in case desktop furniture got in the way.
                SDL_GetWindowPosition(gp_sdl_window, &g_win_rect.x, &g_win_rect.y);
            }
        } // end while poll event

        if (running) {
            update();
            render();

            // Stop recording, and save the frame duration.
            const Uint32 dt = g_refresh_timer.stop();
            // Calculate the time to sleep based on the frame duration and desired frame rate.
            const Uint32 sleep_millis = g_refresh_timer.getDelay(dt);
            if (sleep_millis > 0) {
                // Sleep to control the frame rate.
                SDL_Delay(sleep_millis);
            }
        }
    } // end while running
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

void
showAboutGUI()
{
    const std::string title = "About " + std::string{ g_app_name };
    const std::string msg = "Googly eyes for your desktop.\nCopyright (c) 2025, Abe Mishler.\n\nv" + std::string{ ABEEYES_VERSION };
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(), msg.c_str(), nullptr);
}

void
showVersion()
{
    printf("%s v%s\nGoogly eyes for your desktop.\n", g_app_name, ABEEYES_VERSION);
}

void
showHelp(const AbeArgs::Parser& parser)
{
    showVersion();
    printf("\nHelp:\n");

    AbeArgs::ArgumentList_t list = parser.getArguments();
    for (size_t i = 0, n = list.size(); i < n; ++i) {
        std::cout << list[i].toString();
        printf("\n");

        if (i < n - 0 && list[i].hasDefaultValue())
            printf("\n");
    }
    printf("\n");
}

bool
detectClickEvent()
{
    AbeEyes::MouseAttrs prev_mouse = g_mouse;
    g_system.updateMouse(gp_sdl_window, &g_mouse);
    return !prev_mouse.isClicked() && g_mouse.isClicked();
}

bool
initResources()
{
    using namespace AbeEyes;
    // Load the spritesheet as a texture for clipping into Sprites.
    Texture* spritesheet = Resources::addTexture({ gp_sdl_renderer });
    const char* file_path = "../rsrc/blink_sheet.png";
    if (!spritesheet->load(file_path, { 0xD7, 0x7B, 0xBA, SDL_ALPHA_OPAQUE })) {
        return false;
    }

    // Create the eyes.
    Eyeball
      left_eye({ 32, 32 }),
      right_eye({ 96, 32 });

    // Enable pupil resizing based on screen dimensions and mouse distance.
    left_eye.initPupilSizes(g_system.getDesktopArea());
    right_eye.initPupilSizes(g_system.getDesktopArea());

    // Copy the eyes to their layer for rendering.
    g_eyeball_layer["left_eye"] = left_eye;
    g_eyeball_layer["right_eye"] = right_eye;

    return true;
}

bool
initSDL()
{
    // Init SDL subsystems.
    const Uint32 sdl_flags = SDL_INIT_VIDEO | SDL_INIT_EVENTS;
    if (SDL_Init(sdl_flags) < 0) {
        std::cerr << "Failure to initialize SDL: " << SDL_GetError() << "\n";
        close();
        return false;
    }

    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"))
        std::cerr << "Failure to enable linear texture filtering\n";

    if (g_win_rect.x < 0 && g_win_rect.y < 0)
        // Align the window to the screen edge if x and y haven't been set.
        g_system.updateWindowRect(AbeEyes::HAlign::RIGHT, AbeEyes::VAlign::BOTTOM, g_win_rect);

    // Make a borderless window and place it in the lower right corner.
    const Uint32 win_flags = /*| SDL_WINDOW_UTILITY */ SDL_WINDOW_BORDERLESS;
    gp_sdl_window = SDL_CreateWindow(g_app_name, g_win_rect.x, g_win_rect.y, g_win_rect.w, g_win_rect.h, win_flags);
    if (!gp_sdl_window) {
        std::cerr << "Failure to create SDL Window: " << SDL_GetError() << "\n";
        close();
        return false;
    }

    // Update the actual window position into the window rect.
    // It might not have been created in the actual location specified
    // above due to other system furniture like a dock or taskbar.
    SDL_GetWindowPosition(gp_sdl_window, &g_win_rect.x, &g_win_rect.y);

    // SDL_RENDERER_PRESENTVSYNC matches the frame rate to the monitor refresh rate.
    const Uint32 renderer_flags = SDL_RENDERER_ACCELERATED; // | SDL_RENDERER_PRESENTVSYNC;
    gp_sdl_renderer = SDL_CreateRenderer(gp_sdl_window, -1, renderer_flags);
    if (!gp_sdl_renderer) {
        std::cerr << "Failure to create SDL Renderer: " << SDL_GetError() << "\n";
        close();
        return false;
    }

    SDL_DisplayMode sdl_display_mode;
    if (SDL_GetDesktopDisplayMode(0, &sdl_display_mode) < 0) {
        std::cerr << "Failure to get SDL Desktop Display Mode: " << SDL_GetError() << "\n";
        // Go with the default frame rate set into the constructor.
    } else {
        // std::cout << "Setting fps: " << sdl_display_mode.refresh_rate << "\n";
        // Update the frame rate based on the current detected display mode.
        g_refresh_timer.setFrameRate(sdl_display_mode.refresh_rate);
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
    // Update the mouse position and button state.
    const bool click_event = detectClickEvent();
    for (auto& it : g_eyeball_layer) {
        if (click_event)
            it.second.handleClick();
        it.second.lookAt(g_mouse);
    }
}

void
render()
{
    // Clear the renderer with the current draw color.
    SDL_SetRenderDrawColor(gp_sdl_renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(gp_sdl_renderer);

    // Render the eyeballs.
    for (const auto& it : g_eyeball_layer)
        it.second.render();

    SDL_RenderPresent(gp_sdl_renderer);
}
