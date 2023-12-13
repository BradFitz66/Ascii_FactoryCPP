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

struct input
{
    std::function<void(const Uint8 * keys, entt::entity)> handler;
};

struct renderer{
    //Render function that takes the entity this component is attached to as a parameter.
    std::function<void(entt::entity)> render;
};
#endif