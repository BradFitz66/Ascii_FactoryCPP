// Based off of https://github.com/HexDecimal/libtcod-vcpkg-template/tree/main

#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <numeric>

#include <SDL.h>
#include <FastNoise/FastNoise.h>
#include <libtcod.hpp>
#include <entt.hpp>

#include "Framework/Miscellaneous/Utils.hpp"
#include "Framework/ECS/Components.hpp"

#if defined(_MSC_VER)
#pragma warning(disable : 4297) // Allow "throw" in main().  Letting the compiler handle termination.
#endif

static constexpr auto WHITE = tcod::ColorRGB{255, 255, 255};

static tcod::Console g_console; // The global console object.
static tcod::Context g_context; // The global libtcod context.



struct map{
    std::vector<float> data = {};
    int width;
    int height;
};

double dt = 0.0;
double last = 0.0;
double fps = 0.0;
float in_x = 0;
float in_y = 0;

/// Game loop.
void main_loop(entt::registry &registry)
{
    auto entities = registry.view<position, velocity, renderer>();
    auto m = registry.view<map, renderer>();
    auto input_entities = registry.view<input>();

    Uint64 start = SDL_GetPerformanceCounter();

    g_console.clear();

    for (auto [entity, input] : input_entities.each())
    {
        input.handler(SDL_GetKeyboardState(nullptr), entity);
    }

    for (auto [entity, position, velocity, renderer] : entities.each())
    {
        position.x += velocity.x * dt;
        position.y += velocity.y * dt;
        renderer.render(entity);
    }

    for (auto [entity, map, map_render] : m.each())
    {
        map_render.render(entity);
    }


    //Clamp the FPS to no decimals.
    float no_decimals = floor(fps);
    tcod::print(g_console, {0, 0}, "FPS: " + std::to_string((int)fps), WHITE, std::nullopt);

    g_context.present(g_console);

    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            exit(0);
        }
    }

    Uint64 end = SDL_GetPerformanceCounter();
    dt = (end - start) / static_cast<float>(SDL_GetPerformanceFrequency());
    fps = 1.0f / dt;
}

/// Main program entry point.
int main(int argc, char **argv)
{
    try
    {
        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");
        auto params = TCOD_ContextParams{};
        params.tcod_version = TCOD_COMPILEDVERSION;
        params.argc = argc;
        params.argv = argv;
        params.renderer_type = TCOD_RENDERER_SDL2;
        params.vsync = 0;
        params.sdl_window_flags = SDL_WINDOW_RESIZABLE;
        params.window_title = "Libtcod Template Project";
        //Set default SDL texture interpolation method

        auto tileset = tcod::load_tilesheet(get_data_dir() / "terminal8x8_gs_ro.png", {16, 16}, default_charmap);
        params.tileset = tileset.get();

        g_console = tcod::Console{80, 40};
        params.console = g_console.get();

        g_context = tcod::Context(params);
        entt::registry registry;
        
        auto player = registry.create();
        registry.emplace<position>(player, 10.0f, 10.0f);
        registry.emplace<velocity>(player, 0.0f, 0.0f);

        //This seems kinda ugly.
        registry.emplace<input>(player, [&](const Uint8 * keys, entt::entity e){
            velocity& vel = registry.get<velocity>(e);
            int x_negative = SDL_GetKeyboardState(NULL)[SDL_SCANCODE_LEFT]!=0 ? 1 : 0;
            int x_positive = SDL_GetKeyboardState(NULL)[SDL_SCANCODE_RIGHT]!=0 ? 1 : 0;

            int y_negative = SDL_GetKeyboardState(NULL)[SDL_SCANCODE_UP]!=0 ? 1 : 0;
            int y_positive = SDL_GetKeyboardState(NULL)[SDL_SCANCODE_DOWN]!=0 ? 1 : 0;


            vel.x = (float)(x_positive - x_negative) * 3.0f;
            vel.y = (float)(y_positive - y_negative) * 3.0f;

        });
        registry.emplace<renderer>(player, [&](entt::entity e){
            auto pos = registry.get<position>(e);
            tcod::print(g_console, {(int)pos.x, (int)pos.y}, "X", WHITE, std::nullopt);
        });

        auto world = registry.create();
        std::vector<float> data = std::vector<float>(80 * 40, 0.0f);
        auto fnPerlin = FastNoise::New<FastNoise::Perlin>();
        fnPerlin->GenUniformGrid2D(data.data(), 0, 0, 80, 40, 0.2f, 1337);


        registry.emplace<map>(world,data, 80, 40);
        registry.emplace<renderer>(world, [&](entt::entity e){
            auto m = registry.get<map>(e);
            for (int y = 0; y < m.height; y++)
            {
                for (int x = 0; x < m.width; x++)
                {
                    if (m.data[y * m.width + x] >= 0.5f && m.data[y * m.width + x] <= 0.75f)
                    {
                        tcod::print(g_console, {x, y}, "0", WHITE, std::nullopt);
                    }
                    else if (m.data[y * m.width + x] >= 0.25f && m.data[y * m.width + x] <= 0.5f)
                    {
                        tcod::print(g_console, {x, y}, "1", WHITE, std::nullopt);
                    }
                }
            }
        });

        while (true)
            main_loop(registry);
    }
    catch (const std::exception &exc)
    {
        std::cerr << exc.what() << "\n";
        throw;
    }
}
