/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** BombDropperSystem.cpp
*/
#include "BombDropperSystem.hpp"
#include "../ECSCore.hpp"

ECS::BombDropperSystem::BombDropperSystem(ECS::ECSCore &core):
    System("BombDropper", core)
{}

void ECS::BombDropperSystem::updateEntity(ECS::Entity &entity)
{
    if (1) { // TODO: get input
      //  this->_core.makeEntity("Bomb");

    }
}