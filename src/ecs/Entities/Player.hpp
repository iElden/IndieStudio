/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** Player.hpp
*/

#ifndef BOMBERMAN_PLAYER_HPP
#define BOMBERMAN_PLAYER_HPP


#include "../Entity.hpp"
#include "../Ressources.hpp"

namespace ECS
{
	class Player : public Entity {
	public:
		explicit Player(unsigned id, const Ressources &ressources);
	};
}


#endif //BOMBERMAN_PLAYER_HPP