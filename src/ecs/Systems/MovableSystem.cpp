/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** MovableSystem.cpp
*/
#include "MovableSystem.hpp"
#include "../Components/MovableComponent.hpp"
#include "../Components/PositionComponent.hpp"
#include "../data/Directions.hpp"

ECS::MovableSystem::MovableSystem(ECS::ECSCore &core):
    System("Movable", core)
{
    this->_dependencies = {"Position"};
}

void ECS::MovableSystem::updateEntity(ECS::Entity &entity)
{
    auto mc = reinterpret_cast<MovableComponent&>(entity.getComponentByName("Movable"));
    auto pc = reinterpret_cast<PositionComponent&>(entity.getComponentByName("Position"));

    if (mc.speed > 0) {
        mc.speed += mc.maxSpeed;
        mc.speed = mc.speed <= mc.maxSpeed ?: mc.maxSpeed;
        if (mc.dir & ECS::Directions::RIGHT)
            pc.pos.x += mc.speed;
        if (mc.dir & ECS::Directions::LEFT)
            pc.pos.x -= mc.speed;
        if (mc.dir & ECS::Directions::UP)
            pc.pos.y += mc.speed;
        if (mc.dir & ECS::Directions::DOWN)
            pc.pos.y -= mc.speed;
    }
}