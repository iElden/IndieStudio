/*
** EPITECH PROJECT, 2019
** IndieStudio
** File description:
** SolidComponent.hpp
*/

#ifndef SOLIDCOMPONENT_HPP
#define SOLIDCOMPONENT_HPP

#include "../Component.hpp"
#include "../Entity.hpp"
#include <vector>

namespace ECS
{
    class CollisionComponent : public Component
    {
        public:
            unsigned int hardness;
            std::vector<Entity*> entitiesCollided = {};
            CollisionComponent(unsigned int hardness);
    };
} // namespace ECS

#endif