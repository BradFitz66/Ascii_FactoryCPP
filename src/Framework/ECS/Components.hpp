#ifndef COMPONENTS_HPP
#define COMPONENTS_HPP
#include <functional>
#include <entt.hpp>

struct position
{
    float x;
    float y;
};

struct velocity
{
    float x;
    float y;
};

struct input{
    //Allows an entity to handle it's own input
    std::function<void(const Uint8 * keys, entt::entity)> handler;
};

struct renderer{
    //Allows the handling of rendering on a per entity basis
    std::function<void(entt::entity)> render;
};
#endif