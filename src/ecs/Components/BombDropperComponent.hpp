/*
** EPITECH PROJECT, 2019
** ECS
** File description:
** BombDropperComponent.hpp
*/

#ifndef BOMBDROPpERCOMPONENT_HPP
#define BOMBDROPpERCOMPONENT_HPP

#include <vector>
#include "../Component.hpp"
#include "../Entity.hpp"
#include "../Ressources.hpp"

namespace ECS
{
	class BombDropperComponent : public Component {
	public:
		std::vector<Entity> bombs;
		unsigned int max;
		float timeToExplode;
		unsigned int range;

		explicit BombDropperComponent(unsigned max = 1, float timeToExplode = 5, unsigned range = 1);
		BombDropperComponent(const Ressources &ressources, std::istream &stream);
		std::ostream &serialize(std::ostream &stream) const override;
	};
} // namespace ECS

#endif