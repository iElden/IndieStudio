/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** BlockedSystem.cpp
*/
#include <cmath>
#include "../Exceptions.hpp"
#include "BlockedSystem.hpp"
#include "../Components/CollisionComponent.hpp"
#include "../Components/PositionComponent.hpp"
#include "../Components/MovableComponent.hpp"
#include "../../config.hpp"
#include "../Components/ColliderComponent.hpp"

ECS::BlockedSystem::BlockedSystem(ECS::ECSCore &core):
    System("Blocked", core)
{
    this->_dependencies = {"Collision", "Position"};
}

void ECS::BlockedSystem::updateEntity(ECS::Entity &entity)
{
    auto &entity_hitbox = reinterpret_cast<CollisionComponent &>(entity.getComponentByName("Collision"));

    for (auto &wall : entity_hitbox.entitiesCollided) {
        auto &entity_pos = reinterpret_cast<PositionComponent &>(entity.getComponentByName("Position"));
        auto &entity_mov = reinterpret_cast<MovableComponent &>(entity.getComponentByName("Movable"));
        auto &wall_hitbox = reinterpret_cast<ColliderComponent &>(wall->getComponentByName("Collider"));
        auto &wall_pos = reinterpret_cast<PositionComponent &>(wall->getComponentByName("Position"));

        if (wall_hitbox.hardness <= entity_hitbox.passThrough)
            continue;

        double relative_x = entity_pos.pos.x - wall_pos.pos.x;
        double relative_y = entity_pos.pos.y - wall_pos.pos.y;
        if (relative_x < -28.f || relative_x >= 32.f || relative_y < -28.f || relative_y >= 32.f)
            continue;
        char block_id = (static_cast<int>((4*(relative_y - -PLAYERSIZE) / (TILESIZE - -PLAYERSIZE))) << 2)
                        + (static_cast<int>((4*(relative_x - -PLAYERSIZE) / (TILESIZE - -PLAYERSIZE))));
        switch (block_id) {
        case 0:
        case 5: // UP LEFT
            entity_pos.pos.y -= MIN(relative_x + PLAYERSIZE, relative_y + PLAYERSIZE) + .1; // rup
            entity_pos.pos.x -= MIN(relative_x + PLAYERSIZE, relative_y + PLAYERSIZE) + .1; // rleft
            break;
        case 1:
        case 2: // UP
            entity_pos.pos.y = wall_pos.pos.y - PLAYERSIZE - .1;
            break;
        case 3:
        case 6: // UP RIGHT
            entity_pos.pos.y -= MIN(relative_x + PLAYERSIZE, relative_y + PLAYERSIZE) + .1; // rup
            entity_pos.pos.x += MIN(TILESIZE - relative_x, TILESIZE - relative_y) + .1; // rright
            break;
        case 4:
        case 8: // LEFT
            entity_pos.pos.x = wall_pos.pos.x - wall_pos.size.x - .1;
            break;
        case 7:
        case 11: // RIGHT
            entity_pos.pos.x = wall_pos.pos.x + wall_pos.size.x + .1;
            break;
        case 9:
        case 12: // DOWN LEFT
            entity_pos.pos.y += MIN(TILESIZE - relative_x, TILESIZE - relative_y) + .1; // rdown
            entity_pos.pos.x -= MIN(relative_x + PLAYERSIZE, relative_y + PLAYERSIZE) + .1; // rleft
            break;
        case 13:
        case 14: // DOWN
            entity_pos.pos.y = wall_pos.pos.y + wall_pos.size.y + .1;
            break;
        case 10:
        case 15: // DOWN RIGHT
            entity_pos.pos.y += MIN(TILESIZE - relative_x, TILESIZE - relative_y) + .1; // rdown
            entity_pos.pos.x += MIN(TILESIZE - relative_x, TILESIZE - relative_y) + .1; // rright
            break;
        }
    }
}