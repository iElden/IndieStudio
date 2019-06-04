/*
** EPITECH PROJECT, 2019
** bomberman
** File description:
** Entity.cpp
*/

#include <iostream>
#include "Entity.hpp"
#include "Exceptions.hpp"
#include "Factories/ComponentFactory.hpp"

namespace ECS
{
	Entity::Entity(unsigned id, std::string &&name, std::vector<Component *> &&components) :
		_destroy(false),
		_id(id),
		_name(name)
	{
		for (Component *comp : components)
			this->_components.emplace_back(comp);
	}

	std::string Entity::getName() const
	{
		return this->_name;
	}

	unsigned Entity::getId() const
	{
		return this->_id;
	}

	std::vector<std::unique_ptr<Component>> &Entity::getComponents()
	{
		return this->_components;
	}

	Component &Entity::getComponentByName(const std::string &name) const
	{
		for (auto &comp : this->_components)
			if (comp->getName() == name)
				return *comp;
		throw NoSuchComponentException(this->_name + " (id: " + std::to_string(this->_id) + ") has not " + name);
	}

	bool Entity::hasComponent(const std::string &name) const
	{
		try {
			this->getComponentByName(name);
		} catch (NoSuchComponentException &) {
			return false;
		}
		return true;
	}

	bool Entity::isDestroyed()
	{
		return this->_destroy;
	}

	void Entity::destroy()
	{
		this->_destroy = true;
	}

	Entity::Entity(const ECS::Ressources &ressources, std::istream &stream) :
		_destroy(false),
		_id(0),
		_name("")
	{
		ComponentFactory factory(ressources);
		std::string componentName;

		stream >> this->_id >> this->_name;
		for (stream >> componentName; componentName != "EndOfEntity"; stream >> componentName)
			this->_components.push_back(factory.build(componentName, stream));
	}

	std::ostream& Entity::serialize(std::ostream &stream) const
	{
		stream << this->_id << ' ' << this->_name << std::endl;
		for (auto &comp : this->_components)
			stream << '\t' << comp->getName() << ' ' << *comp << std::endl;
		return stream << "EndOfEntity";
	}
}

std::ostream	&operator<<(std::ostream &stream, const ECS::Entity &entity)
{
	return entity.serialize(stream);
}