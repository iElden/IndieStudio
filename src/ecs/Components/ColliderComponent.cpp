/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** ColliderComponent.cpp
*/

#include <iostream>
#include "ColliderComponent.hpp"
#include "../Exceptions.hpp"

ECS::ColliderComponent::ColliderComponent(unsigned hardness) :
	Component("Collider"),
	hardness(hardness)
{

}

std::ostream& ECS::ColliderComponent::serialize(std::ostream &stream) const
{
	return stream << hardness << " EndOfComponent";
}

ECS::ColliderComponent::ColliderComponent(const ECS::Ressources &, std::istream &stream) :
	Component("Blocked"),
	hardness(0)
{
	std::string terminator;

	stream >> this->hardness;
	stream >> terminator;
	if (terminator != "EndOfComponent")
		throw InvalidSerializedStringException("The component terminator was not found");
}