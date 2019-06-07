/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** Displayable.hpp
*/

#ifndef DISPLAYABLECOMPONENT_HPP
#define DISPLAYABLECOMPONENT_HPP

#include "../Component.hpp"
#include "../../irrlicht/Animations.hpp"
#include "../Ressources.hpp"

namespace ECS
{
	class DisplayableComponent : public Component {
	public:
		Irrlicht::Irrlicht	&screen;
		unsigned		entityId;
		std::string		spriteId;
		Irrlicht::Animations	animation;

		explicit DisplayableComponent(std::string &&striteId, Ressources &ressources);
		DisplayableComponent(Ressources &ressources, std::istream &stream);
		~DisplayableComponent();
		std::ostream &serialize(std::ostream &stream) const override;
	};
}

#endif