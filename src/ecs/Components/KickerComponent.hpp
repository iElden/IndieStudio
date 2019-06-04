/*
** EPITECH PROJECT, 2019
** ECS
** File description:
** KickerComponent.hpp
*/

#ifndef KICKERCOMPONENT_HPP
#define KICKERCOMPONENT_HPP

#include "../Component.hpp"
#include "../Ressources.hpp"

namespace ECS
{
    class KickerComponent : public Component {
        public:
            KickerComponent();
            KickerComponent(const Ressources &ressources, std::istream &stream);
	    std::ostream &serialize(std::ostream &stream) const override;
    };
} // namespace ECS

#endif