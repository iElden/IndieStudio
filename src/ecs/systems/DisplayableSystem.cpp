/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** DisplayableSystem.cpp
*/

#include "DisplayableSystem.hpp"
#include "../components/DisplayableComponent.hpp"
#include "../components/PositionComponent.hpp"


ECS::DisplayableSystem::DisplayableSystem(ECS::ECSCore &core):
    System("Displayable", core)
{}

void ECS::DisplayableSystem::updateEntity(ECS::Entity &entity)
{
	DisplayableComponent	&disp = reinterpret_cast<DisplayableComponent &>(entity.getComponentByName("Displayable"));
	PositionComponent	&pos = reinterpret_cast<PositionComponent &>(entity.getComponentByName("Position"));

	disp.gameScene.setSize(disp.entityId, pos.size.x, pos.size.y);
	disp.gameScene.setPosition(disp.entityId, pos.pos.x, pos.pos.y);
	disp.gameScene.setAnimation(disp.entityId, disp.animation);
}