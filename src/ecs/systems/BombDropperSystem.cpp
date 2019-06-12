/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** BombDropperSystem.cpp
*/
#include "BombDropperSystem.hpp"
#include "../ECSCore.hpp"
#include "../components/HealthComponent.hpp"
#include "../components/PositionComponent.hpp"
#include "../components/EphemeralComponent.hpp"
#include "../components/ExplodeComponent.hpp"
#include "../Exceptions.hpp"
#include "../components/BlockedComponent.hpp"

ECS::BombDropperSystem::BombDropperSystem(ECS::ECSCore &core):
		System("BombDropper", core)
{}

void ECS::BombDropperSystem::updateEntity(ECS::Entity &entity)
{
	ECS::BombDropperComponent &bomb = reinterpret_cast<ECS::BombDropperComponent &>(entity.getComponentByName("BombDropper"));

	for (int i = 0; i < (int)bomb.bombs.size(); i++) {
		try {
			this->_core.getEntityById(bomb.bombs[i]);
		} catch (NoSuchEntityException &) {
			bomb.bombs.erase(bomb.bombs.begin() + i);
			i--;
		}
	}
	if (!bomb.dropBomb)
		return;
	if (bomb.bombs.size() >= bomb.max)
		return;

	auto &player_pos = reinterpret_cast<ECS::PositionComponent &>(entity.getComponentByName("Position"));
	Point pos = {
		static_cast<double>(lround(player_pos.pos.x / TILESIZE) * TILESIZE) + TILESIZE / 16,
		static_cast<double>(lround(player_pos.pos.y / TILESIZE) * TILESIZE) + TILESIZE / 16
	};

	for (Entity *ent : this->_core.getEntitiesByComponent("Collider")) {
		auto &pos2 = reinterpret_cast<ECS::PositionComponent &>(ent->getComponentByName("Position"));

		if (pos2.pos.x == pos.x && pos2.pos.y == pos.y)
			return;
	}

	auto &newBomb = this->_core.makeEntity("Bomb");
	auto &bomb_pos = reinterpret_cast<ECS::PositionComponent &>(newBomb.getComponentByName("Position"));
	auto &bomb_explode = reinterpret_cast<ECS::ExplodeComponent &>(newBomb.getComponentByName("Explode"));

	bomb_pos.pos = pos;
	bomb_explode.range = bomb.range;
	bomb.bombs.push_back(newBomb.getId());
	bomb.soundSystem.playSound("bip");
	bomb.dropBomb = false;

	auto &bc = reinterpret_cast<BlockedComponent &>(entity.getComponentByName("Blocked"));
	bc._whitelistId.push_back(&newBomb);

}