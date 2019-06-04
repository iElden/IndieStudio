/*
** EPITECH PROJECT, 2019
** ECS
** File description:
** SolidComponent.cpp
*/

#include <iostream>
#include "CollisionComponent.hpp"
#include "../Exceptions.hpp"

namespace ECS
{
    CollisionComponent::CollisionComponent(unsigned int pass):
    	Component("Collision"),
        passThrough(pass)
    {
    }

    std::ostream& CollisionComponent::serialize(std::ostream &stream) const
    {
    	return stream << passThrough << " EndOfComponent";
    }

    CollisionComponent::CollisionComponent(const ECS::Ressources &, std::istream &stream) :
	    Component("Blocked"),
	    passThrough(0)
    {
	    std::string terminator;

	    stream >> this->passThrough;
	    stream >> terminator;
	    if (terminator != "EndOfComponent")
		    throw InvalidSerializedStringException("The component terminator was not found");
    }
}